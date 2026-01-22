//https://leetcode.cn/problems/last-stone-weight-ii/description/
//1. 每一轮都选择两个数字进行对撞,得到相减之后的值重新放到数组中,重复上述过程
//直到只剩下最后一个数,我们想要让这个数字是所有情况中的最小值
//2. 无论怎么选择,选择的过程就是划分的过程.[3,2,5]
//此次选择3和2,其实就是将3->A{},2->B{},最后得到3-2=1 ->A{},然后再选择5->B{},
//宏观上就是3->A{},2,5->B{},然后让 abs(sumA -sumB )的值最小,返回最后的这个数字
//肯定是越接近的数字相减之后得到的差值最小,那么这个非负数组的累加和为10,
//划分AB集合时,选择一部分数字->A{},那么剩下的都进入B{},
//那么肯定是希望在nums数组中挑选一些数字,在累加和<=5时,A的累加和最大是多少(达成sumA尽量接近5)
//只有这样选择,最后两个数组累加和的差值才会是最小.

//01背包问题就是要还是不要的问题
//dp[i][j]代表的就是在前i个物品中选择,在j<=t时能够获得的最大累加和是多少
//i位置不要: dp[i][j]=dp[i-1][j]
//i位置要: dp[i][j]=dp[i-1][j-nums[i]] +nums[i]
//最后获取二者中较大值
//初始化: 涉及到i-1,所以选择多开一个,dp[n+1][t+1].需要对新开的空间初始化,dp[0]=0
//填表顺序: 优化为一维数组时,因为要依赖于左侧数据,所以为了避免左侧数据被覆盖,需要从右往左更新
//返回值就是dp[t]
#include<iostream>
#include<vector>
using namespace std;

class Solution 
{
public:
    int lastStoneWeightII(vector<int>& stones) 
    {
        int sum = 0;
        for (int& num : stones)
            sum += num;
        int t = sum / 2;
        int near = func(stones, t);
        return sum - near-near;
    }
    int func1(vector<int>& nums, int t)
    {
        int n = nums.size();
        vector<vector<int>>dp(n + 1, vector<int>(t + 1));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= t; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j > nums[i - 1])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - nums[i - 1]] + nums[i - 1]);
            }
        }
        return dp[n][t];
    }
    int func2(vector<int>& nums, int t)
    {
        int n = nums.size();
        vector<int>dp(t + 1);
        for (int i = 1; i <= n; i++)
        {
            for (int j = t; j >= nums[i]; j--)
                dp[j] = max(dp[j], dp[j - nums[i - 1]] + nums[i - 1]);
        }
        return dp[t];
    }
public:
    int func(vector<int>& nums, int t)
    {
        vector<int>dp(t + 1);
        for (int num : nums)
        {
            for (int j = t; j >= num; j--)
                dp[j] = max(dp[j], dp[j - num] + num);
        }
        return dp[t];
    }
};