//https://leetcode.cn/problems/ones-and-zeroes/
//在给定的数组中选择出所有满足条件的字符串，构成最大的子集
//条件： 0的数量<m ,1的数量<n

#include<iostream>
#include<vector>
using namespace std;
//尝试模型： 从左到右，index位置的字符串到底要还是不要
//strs[index...]自由选择，选出0<zero,1<one的字符串，最多能选出几个
class Solution1 
{
public:
    int findMaxForm(vector<string>& strs, int m, int n) 
    {
        return dfs(strs, 0, m, n);
    }

    int zeros, ones;
    void count(string& str)
    {
        zeros = 0, ones = 0;
        for (auto ch : str)
        {
            if (ch == '1')
                ones++;
            else
                zeros++;
        }
    }
    int dfs(vector<string>& strs, int index, int zeroLimit, int oneLimit)
    {
        if (index == strs.size())
            return 0;
        //不选择当前字符串
        int p1 = dfs(strs, index + 1, zeroLimit, oneLimit);
        //选择当前字符串
        int p2 = 0;
        count(strs[index]);
        if (zeros < zeroLimit && ones < oneLimit)
            p2 = 1 + dfs(strs, index + 1, zeroLimit - zeros, oneLimit - ones);
        return max(p1, p2);
    }
};
//分析：有多种选择到达index位置时，查询后续有多少种满足的情况
//为了避免重复情况的计算，可以升级为记忆化搜索
class Solution2
{
    vector<vector<vector<int>>> memo;
public:
    int findMaxForm(vector<string>& strs, int m, int n)
    {
        int sz = strs.size();
        memo = vector<vector<vector<int>>>(sz, vector<vector<int>>(m+1, vector<int>(n+1, -1)));
        return dfs(strs, 0, m, n);
    }
    //zero,one
    pair<int, int>count(string& str)
    {
        int zero = 0, one = 0;
        for (auto ch : str)
        {
            if (ch == '0')
                zero++;
            else
                one++;
        }
        return { zero,one };
    }
    int dfs(vector<string>& strs, int index, int zero, int one)
    {
        if (index == strs.size())
            return 0;
        if (memo[index][zero][one] != -1)
            return memo[index][zero][one];
        int p1 = dfs(strs, index + 1, zero, one);
        int p2 = 0;
        pair<int,int>ret = count(strs[index]);
        if (ret.first <= zero && ret.second <= one)
            p2 = 1 + dfs(strs, index + 1, zero - ret.first, one - ret.second);
        memo[index][zero][one] = max(p1, p2);
        return memo[index][zero][one];
    }
};
//分析严格位置依赖，index依赖于index+1，所以填表顺序是从右往左，zero one 都依赖于左侧，所以是从左往右
//返回值： dp[0][m][n]
//初始化： dp[sz][][]=0,zero one填表顺序无所谓，因为都不依赖于本层的值
class Solution3
{
public:
    //zero,one
    pair<int, int>count(string& str)
    {
        int zero = 0, one = 0;
        for (auto ch : str)
        {
            if (ch == '0')
                zero++;
            else
                one++;
        }
        return { zero,one };
    }
    int findMaxForm(vector<string>& strs, int m, int n)
    {
        int sz = strs.size();
        vector<vector<vector<int>>>dp(sz+1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        for (int i = sz - 1; i >= 0; i--)
        {
            pair<int,int>ret = count(strs[i]);
            int zero = ret.first, one = ret.second;
            for (int z = 0; z <= m; z++)
            {
                for (int o = 0; o <= n; o++)
                {
                    int p1 = dp[i + 1][z][o];
                    int p2 = 0;
                    if (zero <= z && one <= o)
                        p2 = 1 + dp[i + 1][z - zero][o - one];
                    dp[i][z][o] = max(p1, p2);
                }
            }
        }
        return dp[0][m][n];
    }
};
//https://www.bilibili.com/video/BV1gM41197rM?t=1113.1
//空间压缩
//要更新zero和one依赖于i+1层上的数据，那么如果将二维表中i+1层更新为i层数据？》
//要更新某一位置，发现依赖的值都是具备的，可以直接更新出来.
//要避免值得覆盖，所以要将zero和one的更新顺序做出规定，因为zero和one依赖的都是左侧的值
//所以保证二者都是从右往左更新，才能保证依赖的值都是未更新的。
// 每次都依赖于上一层自己的位置，也就是p1一定是经历的，只有zero和one满足条件时才会依赖之前的格子
// 所以遍历时才有两种可能性的PK
//每次来一个字符串，更新一次表即可

//经过测试，三维表优化为二维表还是很有必要的。
class Solution4
{
    int zero, one;
public:
    void count(string& str)
    {
        zero = 0, one = 0;
        for (auto ch : str)
        {
            if (ch == '0')
                zero++;
            else
                one++;
        }
    }
    int findMaxForm(vector<string>& strs, int m, int n)
    {
        vector<vector<int>>dp(m + 1, vector<int>(n + 1));
        for (string& str : strs)
        {
            count(str);
            for (int z = m; z >= zero; z--)
            {
                for (int o = n; o >= one; o--)
                {
                    dp[z][o] = max(dp[z][o],1+ dp[z - zero][o - one]);
                }
            }
        }
        return dp[m][n];
    }
};
//另外一种理解方式： 01背包问题，其实就是在给定数组中，在满足条件的情况下进行挑选所得到最大价值问题
//以index位置为结尾看待问题，
//二维费用的01背包问题
//dp[i][j]代表的是从 前i个 物品中挑选在容积 不超过j 的情况下所能达到的最大价值
//背包问题实质上就是给定一个待选数组,在满足某些种条件下所能达到的最大利益.
//dp[i][j][k]代表的就是从前i个字符串中选择,在满足0的个数不超过j,1的个数不超过k的情况下选择子集的最大个数
//到达第i个字符串选还是不选的问题,假设i字符串0的个数a,1的个数b,如果不选就是在前i-1个中选,dp[i-1][j][k]
//如果选i位置字符串,dp[i-1][j-a][k-b],因为是个数,所以还得+1,
//两种情况取较大值
//空间优化: 因为依赖的是上一层,所以保证从后往前遍历
class Solution6
{
public:
    int findMaxForm(vector<string>& strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<vector<int>>>dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        //因为是不超过的01背包问题,当选择前0个即不选的时候子集个数为0
        for (int i = 1; i <= len; i++)
        {
            //统计选中i字符串的01情况
            int a = 0, b = 0;
            for (auto ch : strs[i - 1])//因为多开一行多开一列,注意访问原数组时下标问题
            {
                if (ch == '0') a++;
                else b++;
            }
            for (int j = 0; j <= m; j++)
            {
                for (int k = 0; k <= n; k++)
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (j >= a && k >= b)
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - a][k - b] + 1);
                }
            }
        }
        return dp[len][m][n];
    }
};
class Solution5
{
public:
    int findMaxForm(vector<string>& strs, int m, int n)
    {
        int sz = strs.size();
        vector<vector<int>>dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= sz; i++)//从前i个字符串中选择
        {
            int a = 0, b = 0;
            for (auto ch : strs[i - 1])//访问原数组时要注意下标
            {
                if (ch == '0') a++;
                else b++;
            }
            for (int j = m; j >= a; j--)
            {
                for (int k = n; k >= b; k--)
                {
                    dp[j][k] = max(dp[j][k], dp[j - a][k - b] + 1);
                }
            }
        }
        return dp[m][n];
    }
};