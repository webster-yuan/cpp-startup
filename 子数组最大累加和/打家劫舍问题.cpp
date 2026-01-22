//https://leetcode.cn/problems/house-robber/submissions/455246828/

//1. 
//dp[i]表示在[0...i]区间任意选择,能够得到的最大的累加和
//i位置数字不要,那么dp[i]=dp[i-1]
//i位置数字要,1.自己一组最大,dp[i]=nums[i] 2. 和前面的组合起来最大,但是不能要i-1位置,dp[i]=dp[i-2]+nums[i]
//两种情况取最大值
//2. 
//空间压缩,因为只依赖于前两个位置,所以可以使用两个变量滚动更新

//3. 采用两个状态进行记录
//f[i]表示i位置选择,g[i]表示i位置不选择
//f[i] = nums[i]+g[i-1] i位置选择,那么i-1位置必然不选择
//g[i] = max(f[i-1],g[i-1]) i位置不选择,那么可能i-1位置选择或者不选择,取较大值即可
//涉及到i-1导致的越界问题,选择直接初始化 or 多开一个位置将边界值挪动到整体计算中(仍要注意初始化)
//选择直接初始化: 考虑实际情况得到,f[0]=nums[0] g[0]=0
#include<iostream>
#include<vector>
using namespace std;
class Solution11
{
public:
    int rob1(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        if (n == 2)
            return max(nums[0], nums[1]);
        vector<int>dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++)
            dp[i] = max(dp[i - 1], max(nums[i], nums[i] + dp[i - 2]));
        return dp[n - 1];
    }
    int rob2(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        if (n == 2)
            return max(nums[0], nums[1]);

        int prev = max(nums[0],nums[1]);
        int pprev = nums[0];
        for (int i = 2; i < n; i++)
        {
            int cur = max(prev, max(nums[i], pprev + nums[i]));
            pprev = prev;
            prev = cur;
        }
        return prev;
    }
    int rob3(vector<int>& nums)
    {
        int n = nums.size();
        vector<int>f(n);
        vector<int>g(n);
        f[0] = nums[0], g[0] = 0;
        for (int i = 1; i < n; i++)
        {
            f[i] = g[i - 1] + nums[i];
            g[i] = max(g[i - 1], f[i - 1]);
        }
        return max(f[n - 1], g[n - 1]);
    }
};