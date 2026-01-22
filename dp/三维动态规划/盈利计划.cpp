//https://leetcode.cn/problems/profitable-schemes/description/
#include<iostream>
#include<vector>
using namespace std;

//使用dfs->memo记忆化搜索的方式
class Solution7 
{
    vector<vector<vector<int>>>memo;
    const int MOD = 1000000007;
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) 
    {
        int m = group.size();
        memo = vector<vector<vector<int>>>(m,vector<vector<int>>(n+1,vector<int>(minProfit+1,-1)));
        return dfs(0, group, profit, n, minProfit);
    }
    //当到达index位置时，还剩下rest个人，还需要need金额才能达到标准，返回一共有多少种方法数
    int dfs(int index,vector<int>& group, vector<int>& profit, int rest, int need)
    {
        if (rest <= 0)//不剩下人了
            return need == 0 ? 1 : 0;
        if (index == group.size())//工作已经耗尽了
            return need == 0 ? 1 : 0;

        if (memo[index][rest][need] != -1)
            return memo[index][rest][need];

        //不选当前工作
        int p1 = dfs(index+1, group, profit, rest, need);
        int p2 = 0;
        //选当前工作
        if(group[index]<=rest)//当前工作需要的人数 <= 剩下的人数
            p2 = dfs(index + 1, group, profit, rest - group[index], max(0,need - profit[index]));
        int ans = (p1 + p2) % MOD;
        memo[index][rest][need] = ans;
        return ans;
    }
};
//分析严格位置依赖，将其优化为二位动态规划表
//将需要利润小于0时都处理为0，代表达标。因为要升级为dp表进行存储，然后使用need进行查询时，避免出现dp[-100]越界的情况
//https://www.bilibili.com/video/BV1gM41197rM?t=2562.8 空间压缩为二维
//依赖于i+1层，所以得到第5层，希望推导出第4层，依赖于左下二位范围区间。
//初始化： 当来到最高层时，即i=m时，代表没有剩余工作时，初始化为1
class Solution8
{
    const int MOD = 1000000007;
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit)
    {
        vector<vector<int>>dp(n + 1, vector<int>(minProfit + 1, 0));
        int m = group.size();
        //二维表中当need=0时，初始化为1
        for (int r = 0; r <= n; r++)
            dp[r][0] = 1;
        for (int i = m - 1; i >= 0; i--)
        {
            for (int r = n; r >= 0; r--)
            {
                for (int need = minProfit; need >= 0; need--)
                {
                    int p1 = dp[r][need];
                    int p2 = 0;
                    if (r >= group[i])
                        p2 = dp[r - group[i]][max(0, need - profit[i])];
                    dp[r][need] = (p1 + p2)% MOD;
                }
            }
        }
        return dp[n][minProfit];
    }
};

//采用01背包思想
//dp[i][j][k]表示在 前i个任务中 挑选，在满足（人数不超过j）的条件下，利润不小于K时的选择任务的方法个数
//在i位置的任务选不选的问题,如果不选,dp[i-1][j][k],如果选了,dp[i-1][j-g[i]][k-p[i]]
//j-g[i]<0,代表第i个任务的消耗已经超过j总人数,所以不行.
//k-p[i]<=0,代表第i个任务带来的利润已经超过预期k,是可以的.
// 所以前i-1中选择时只需要总利润p[i]>=k即可,k`=[max(0,k-p[i])]
//两种情况得到的计划数相加即可
//初始化： 在前0个当中选择，在满足人数<=j时，利润不小于0，那么就是一种方式，不选，所以为1
//填表顺序： 只需要i从小到大就行，jk无所谓
//多开一行一列时保证访问原数组时要下标 -1 
class Solution9
{
    const int MOD = 1000000007;
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit)
    {
        int len = group.size();
        vector<vector<vector<int>>>dp(len+1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1, 0)));
        for (int j = 0; j <= n; j++)
            dp[0][j][0] = 1;

        for (int i = 1; i <= len; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                for(int k=0;k <= minProfit;k++)
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (j >= group[i - 1])
                        dp[i][j][k] += dp[i - 1][j - group[i-1]][max(0, k - profit[i-1])];
                    dp[i][j][k] %= MOD;
                }
            }
        }
        return dp[len][n][minProfit];
    }
};

//背包问题优化为二维，需要考虑jk的更新顺序，需要从大往小了更新
class Solution10
{
public:
    int profitableSchemes(int n, int m, vector<int>& g, vector<int>& p)
    {
        const int mod = 1e9 + 7;
        int len = g.size();
        vector<vector<int>>dp(n + 1, vector<int>(m + 1));
        for (int j = 0; j <= n; j++)
            dp[j][0] = 1;

        for (int i = 1; i <= len; i++)
        {
            for (int j = n; j >= g[i - 1]; j--)
            {
                for (int k = m; k >= 0; k--)
                {
                    dp[j][k] += dp[j - g[i - 1]][max(0, k - p[i - 1])];
                    dp[j][k] %= mod;//为了避免数据量大导致int越界
                }
            }
        }
        return dp[n][m];
    }
};