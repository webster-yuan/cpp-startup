//https://leetcode.cn/problems/maximum-subarray/description/
#include<iostream>
#include<vector>
using namespace std;
class Solution1
{
public:
    int maxSubArray1(vector<int>& nums)
    {
        int n = nums.size();
        vector<int>dp(n+1);
        int ret = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ret = max(ret, dp[i]);
        }
        return ret;
    }
    int maxSubArray2(vector<int>& nums)
    {
        int n = nums.size();
        vector<int>dp(n);
        dp[0] = nums[0];
        int ret = INT_MIN;
        for (int i = 1; i < n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            ret = max(ret, dp[i]);
        }
        return ret;
    }
    int maxSubArray3(vector<int>& nums)
    {
        int n = nums.size();
        int prev = nums[0];
        int ret = nums[0];
        for (int i = 1; i < n; i++)
        {
            prev = max(nums[i] + prev, nums[i]);
            ret = max(prev, ret);
        }
        return ret;
    }
};
//1.
//dp[i]代表以i位置为结尾，累加和最大的连续子数组，考虑最近一次操作
//1. 自己一组，2.和之前的一组，dp[i]=max(arr[i],dp[i-1]+arr[i])
// 
//2. 初始化：涉及到i-1，所以采用多开一个格子的方式，2.1 注意初始化，让新开的0位置为0不影响结果 2.2 在访问原数组时注意下标的变化
//3. 返回值： 返回dp数组中的最大值

//2. 
//以i位置数为结尾，考虑往左最大能扩展多长能够使得累加和能最大
//1. 自己一组，2. 因为是连续的数组，所以需要往前拓展得到最大和+自身，最大和就是dp[i-1]的含义

//3. 
//因为只依赖于前一个位置，所以没有必要准备一整张表，使用一个变量记录前一个位置的值即可
//prev时刻更新，变为dp[i]的值
//ans记录比较，看看能否变得更大，dp[0]

//附加问题： 想求出这段最大累加和区间的left,right,maxSum
//https://www.bilibili.com/video/BV1pw411M7Du?t=1055.3
// prev代表前置区间的累加和，left左区间，right右区间,sum代表已经遍历的范围内最大累加和
//当到达i位置时，如果prev>=0，说明有利可图，i位置可以和他们一起，right++
//如果prev<0,说明不可获利，就自己一组，prev=nums[i],left=right,寻求以i位置为开头，
//往后找能否让累加和更大的区间，
// 为什么直接跳这么多呢？因为如果后续区间再往前扩充，即left<i，得到的连续区间的累加和一定会减小

class Solution2
{
    int left, right, sum;
public:
    void extra(vector<int>& nums)
    {
        int n = nums.size();
        sum = INT_MIN;
        int prev = INT_MIN;
        for (int l = 0, r = 0; r < n; r++)
        {
            if (prev >= 0)
                prev += nums[r];
            else
            {
                prev = nums[r];
                l = r;
            }
            if (prev > sum)
            {
                sum = prev;
                left = l;
                right = r;
            }
        }
    }
};
