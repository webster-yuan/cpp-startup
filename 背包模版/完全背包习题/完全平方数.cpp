
//完全平方数组成和为n的最少数量
//完全平方数是指他是另一个数字的平方

//题解:
//完全背包问题: 每个数字都能选无数个
// dp[i][j]表示在前i个数字中选择,在体积为j时所能到达的最大价值
//dp[i][j]表示在前i个数字中选择,和为n的为最少数量是多少
//dp[i][j]=dp[i-1][j],dp[i][j-x]+1
//初始化: 多开一行多开一列...
//      第一行代表不选择数字时,和为j时的最少数量,不选咋么得和j,所以初始化为-1,INT_MAX
//返回值: dp[n][v]==-1?-1:dp[n][v]
//填表顺序: 从上往下从左往右
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution 
{
public:
    int numSquares1(int n) 
    {
        const int inf = 0X3f3f3f3f;
        int m = sqrt(n);//既然是乘方,范围肯定是在[1,sqrt(n)]中选择
        vector<vector<int>>dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++)
            dp[0][i] = inf;
        for (int i = 1; i <=m; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j - i * i >= 0)
                    dp[i][j] = min(dp[i][j], dp[i][j - i * i] + 1);
            }
        }
        return dp[m][n];
    }
    //滚动数组优化空间复杂度
    int numSquares(int n)
    {
        const int inf = 0X3f3f3f3f;
        int m = sqrt(n);//既然是乘方,范围肯定是在[1,sqrt(n)]中选择
        //vector<vector<int>>dp(m + 1, vector<int>(n + 1));
        vector<int>dp(n + 1);
        for (int i = 1; i <= n; i++)
            dp[i] = inf;
        for (int i = 1; i <= m; i++)
        {
            for (int j =i*i;j<=n;j++)
            {
                 dp[j] = min(dp[j], dp[j - i * i] + 1);
            }
        }
        return dp[n];
    }
};

//回顾01背包: 物品只能选中一次
// https://github.com/tail-yuan/Review_Code/blob/main/%E8%83%8C%E5%8C%85%E6%A8%A1%E7%89%88/01%E8%83%8C%E5%8C%85.cc
//1. dp[i][j]表示在前i个物品中选择物品,在体积  不超过j  时所能到达的最大价值
//考虑最后一个位置[i]
//dp[i][j]=dp[i-1][j],就是第i个位置的物品不选择,
//选择的话: dp[i][j]=dp[i-1][j-v[i]]+w[i],两种情况选择较大值
//初始化: 多开一行多开一列,1. 保证初始化2. 访问原数组时注意下标
//      第一行代表选择0时也就是不选时,在体积不超过J时,能够得到的最大价值->0
//dp[i][j]=max(dp[i][j],dp[i][j-v[i]]+w[i])
//返回值: dp[n][v]
//填表顺序: 从上往下
// 
//2. dp[i][j]表示在前i个物品中选择物品,在体积  恰好为j  时所能到达的最大价值
//考虑最后一个位置[i]
//dp[i][j]=dp[i-1][j],就是第i个位置的物品不选择,
//选择的话: dp[i][j]=dp[i-1][j-v[i]]+w[i],两种情况选择较大值
//初始化: 多开一行多开一列,1. 保证初始化2. 访问原数组时注意下标
//      第一行代表选择0时也就是不选时,在体积恰好为J时,能够得到的最大价值->-1,不选怎么达到体积j?
//      -1代表到达不了
//dp[i][j]=max(dp[i][j],dp[i][j-v[i]]+w[i])
//返回值: dp[n][v]==-1?-1:dp[n][v]
//填表顺序: 从上往下

//完全背包: 每个物品可以选择无数次
////1. dp[i][j]表示在前i个物品中选择物品,在体积  不超过j  时所能到达的最大价值
//考虑最后一个位置[i]
//dp[i][j]=dp[i-1][j],就是第i个位置的物品不选择,
//选择的话: 
// 第i个位置可以选0次,dp[i][j]=dp[i-1][j]
// 第i个位置可以选1次,dp[i][j]=dp[i][j-v[i]]+w[i]
// 第i个位置可以选2次,dp[i][j]=dp[i][j-v[i]]+2w[i]
// 第i个位置可以选3次,dp[i][j]=dp[i][j-v[i]]+3w[i]...
// dp[i][j]等于这些选择中的最大值max,
//dp[i][j]=dp[i][j-v[i]]+w[i],两种情况选择较大值
//初始化: 多开一行多开一列,1. 保证初始化2. 访问原数组时注意下标
//      第一行代表选择0时也就是不选时,在体积不超过J时,能够得到的最大价值->0
//...