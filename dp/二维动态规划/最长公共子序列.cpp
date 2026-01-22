//https://leetcode.cn/problems/longest-common-subsequence/
#include<iostream>
#include<vector>
using namespace std;
//dp[i][j]表示s1[0...i]匹配s2[0...j]子序列的最大长度
//分析两个字符串的最后位置,i,j
//if s1[i]==s2[j],dp[i][j]=dp[i-1][j-1]+1
//else  两种选择,用s1[0...i]去匹配s2[0...j-1],dp[i][j]=dp[i][j-1]
//             ,用s1[0...i-1]去匹配s2[0...j],dp[i][j]=dp[i-1][j]
//二者选出较大值即可
//初始化: 在填写第一行,第一列时涉及到直接对两个字符串的讨论,可以将他整合到后序整体计算中
// 所以采取多开一行,多开一列的方式,
// 1. 注意初始化新开的0行0列,当i=0时,代表第一行即s2为空时,匹配s1为0,同理第一列都初始化为0
// // 2. 访问原字符串时注意下标-1 / 对原字符串+" "操作
// 
//填表顺序: 从左到右
//返回值: dp[n][m]
class Solution3 
{
public:
    int longestCommonSubsequence(string s1, string s2) 
    {
        int n = s1.size(), m = s2.size();
        vector<vector<int>>dp(n + 1, vector<int>(m + 1));
        s1 = " " + s1,s2=" "+s2;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i] == s2[j])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }
};
//--------------------------下面将介绍为什么要多开一行,多开一列整体递推思路------------
//dfs
//p1: 两个结尾都不要,s1[0...i-1]和s2[0...j-1]
//p2: 要s1结尾,不要s2结尾,s1[0...i-1]和s2[0...j]
//p3: 要s2结尾,不要s1结尾,s1[0...i]和s2[0...j-1]
//p4: 两个结尾都要,结尾相同, s1[0...i - 1]和s2[0...j - 1] +1

class Solution4
{
public:
    int longestCommonSubsequence(string s1, string s2)
    {
        return dfs(s1, s2, s1.size() - 1, s2.size() - 1);
    }
    int dfs(string& s1, string& s2, int i, int j)
    {
        if (i < 0 || j < 0)
            return 0;
        int p1 = dfs(s1, s2, i - 1, j - 1);
        int p2 = dfs(s1, s2, i , j - 1);
        int p3 = dfs(s1, s2, i - 1, j);
        int p4 = (s1[i] == s2[j] ? 1 : 0) + dfs(s1, s2, i - 1, j - 1);
        return max(p1, max(p2, max(p3, p4)));
    }
};
//使用dp表记录时,需要记录dp[-1][-1]=0,所以无论是memo还是dp存储,都设计越界的位置,
// 所以讨论长度,然后多开一行一列
// 
// 所以将下标升级为前缀长度作为可变参数,len
// 以i,j位置为结尾讨论两个字符串
//因为求得就是最长,既然i,j位置就已经匹配了,就没必要p1似的还舍弃再到前面更小区间找结果,所以p1没必要
//
//可能存在多次计算s1[i]s2[j]即dp[i][j],所以可以升级为记忆化搜索memo
class Solution5
{
    vector<vector<int>>memo;
public:
    int longestCommonSubsequence(string s1, string s2)
    {
        int n = s1.size(), m = s2.size();
        memo = vector<vector<int>>(n+1,vector<int>(m+1,-1));
        //因为长度的范围是0~n,所以要多开一个空间
        return dfs(s1, s2,n, m);
    }
    int dfs(string& s1, string& s2, int len1, int len2)
    {
        if (len1 == 0 || len2 == 0)
            return 0;
        if (memo[len1][len2] != -1)
            return memo[len1][len2];
        int ans = 0;
        if (s1[len1 - 1] == s2[len2 - 1])
            ans = dfs(s1, s2, len1 - 1, len2 - 1) + 1;
        else
            ans = max(dfs(s1, s2, len1 - 1, len2), dfs(s1, s2, len1, len2 - 1));
        memo[len1][len2] = ans;
        return ans;
    }
};

//https://www.bilibili.com/video/BV1WQ4y1W7d1?t=5298.2
//严格分析位置依赖,依赖左上,左,上,所以填表顺序是从左到右
//********此时第0行,第0列,分别代表s1,s2长度为0时的匹配情况,按理说都是0,所以可以直接从1,1位置开始
//********这就是为什么多开一行多开一列,因为要考虑越界的情况发生,整体的递推思路.
class Solution5
{
public:
    int longestCommonSubsequence(string s1, string s2)
    {
        int n = s1.size(),m=s2.size();
        vector<vector<int>>dp(n + 1, vector<int>(m + 1));
        for (int len1 = 1; len1 <= n; len1++)
        {
            for (int len2 = 1; len2 <= m; len2++)
            {
                if (s1[len1 - 1] == s2[len2 - 1])
                    dp[len1][len2] = dp[len1 - 1][len2 - 1] + 1;
                else
                {
                    dp[len1][len2] = max(dp[len1 - 1][len2], dp[len1][len2 - 1]);
                }
            }
        }
        return dp[n][m];
    }
};
//二维数组空间压缩,
//************为了进一步削减一维数组的占用空间,就让长度短的那个作为列
//https://www.bilibili.com/video/BV1WQ4y1W7d1?t=5681.1
//用一个变量存储左上角,跟着滚动过去即可
//其实就是更新i位置时,leftUp=dp[i],然后更新dp[i],leftUp留着给更新i+1位置时用\
//初始化为0即可,因为最左侧依赖的左上角是0
//此时是最优解
class Solution6
{
public:
    int longestCommonSubsequence(string s1, string s2)
    {
        if (s1.size() < s2.size())
            swap(s1, s2);
        //交换之后,s1是长的,s2是短的那个,让s2做列,即一维数组的长度
        int n = s1.size(), m = s2.size();
        vector<int>dp(m + 1);
        for (int len1 = 1; len1 <= n; len1++) 
        {
            int leftUp = 0, backup;//backUp 备份未更新的dp[i]
            for (int len2 = 1; len2 <= m; len2++) 
            {
                backup = dp[len2];
                if (s1[len1 - 1] == s2[len2 - 1]) 
                    dp[len2] = 1 + leftUp;
                else 
                    dp[len2] = max(dp[len2], dp[len2 - 1]);
                
                leftUp = backup;//滚动下去
            }
        }
        return dp[m];

    }
};