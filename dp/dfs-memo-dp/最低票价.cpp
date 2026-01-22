//https://leetcode.cn/problems/minimum-cost-for-tickets/description/

#include<iostream>
#include<vector>
using namespace std;

//从左到右尝试模型,三种决策中选出最小消耗
//从顶到底,决策树
//T = O(30*N),i遍历N个数字,每个数字在func函数中需要进行3次抉择,每次抉择中需要遍历寻找失效时间j
//最大可跳跃的区间是30天,最多也就是30个格子
//每个i都需要进行一次,所以是O(30*N)
class Solution1
{
    vector<int>durations;//持续时间
public:
    //duration是k下标票的持续时间,cost是k下标票的花费
    int mincostTickets(vector<int>& days, vector<int>& costs) 
    {
        durations = vector<int>{1,7,30};
        return func(days, costs, 0);
    }
    //解决days[i...]之后需要的最少花费是多少
    int func(vector<int>& days, vector<int>& costs,int i)
    {
        if (i == days.size())
            return 0;
        int ans = INT_MAX;
        for (int k = 0; k < 3; k++)
        {
            int j = i;//j计算的是票失效的那一天
            while (j<days.size() && days[i] + durations[k] > days[j])
                j++;
            ans = min(ans, costs[k] + func(days, costs, j));
        }
        return ans;
    }
};
//func(i)存在大量的重复计算,[0,i-1]区间中不同的选择策略,到达i位置都需要进行最小消耗计算
//所以可以升级为记忆化搜索
//在从上往下的模型中通过表的记录提升效率
class Solution2
{
    vector<int>duration;
    vector<int>memo;
    int n;
public:
    int mincostTickets(vector<int>& days, vector<int>& costs)
    {
        duration = vector<int>{ 1,7,30 };
        n = days.size();
        memo= vector<int>(n,-1);
        return func(days, costs, 0);
    }
    int func(vector<int>& days, vector<int>& costs, int i)
    {
        if (i == n)
            return 0;
        if (memo[i] != -1)
            return memo[i];
        int ans = INT_MAX;
        for (int k = 0; k < 3; k++)
        {
            int j = i;
            while (j<n && days[i] + duration[k] > days[j])
                j++;
            ans = min(ans, costs[k] + func(days, costs, j));
        }
        memo[i] = ans;
        return ans;
    }
};

//严格位置依赖的从底到顶的动态规划
//分析位置依赖,要得出days[0....]就需要先知道days[4...],
//改变顺序,将递归改为动态规划
//只有一个可变参数,i,范围是0,n-1,所以开辟n个空间就够
//初始化: dp[n]=0;
//填表顺序: 因为是左侧依赖右侧,所以先右后左,从右往左的顺序

class Solution3
{
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) 
    {
        vector<int>duration{ 1,7,30 };
        int n = days.size();
        const int inf = 0x3f3f3f3f;
        vector<int>dp(n + 1, inf);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int k = 0, j = i; k < 3; k++)
            {
                while (j<n && days[i] + duration[k] > days[j])
                    j++;
                dp[i] = min(dp[i], costs[k] + dp[j]);
            }
        }
        return dp[0];
    }
};