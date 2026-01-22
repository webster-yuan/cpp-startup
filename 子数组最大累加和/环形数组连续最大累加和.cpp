//https://leetcode.cn/problems/maximum-sum-circular-subarray/
#include<iostream>
#include<vector>
using namespace std;
//因为是环形的,所以收尾可以相连作为一段连续的数组
//最大的连续的区间可能不涉及到收尾,可能涉及到收尾
//当不涉及时,就是简单数组求连续区间最大累加和问题,maxSum. 此处可以使用空间压缩之后,一个变量记录的方式更新
//当涉及时,就是整体和all-数组中累加和最小的区间minSum,
//二者选择较大值即可
//求区间最小累加和时,如果都是负数,得到的就是整个数组的累加和all,那么all-minSum时得到0,肯定不是,应该直接返回maxSum
class Solution21 
{
public:
    int maxSubarraySumCircular(vector<int>& nums) 
    {
        int n = nums.size();
        int all = nums[0];
        int maxSum =nums[0], minSum = nums[0];
        int maxPrev = nums[0], minPrev = nums[0];
        for (int i = 1; i < n; i++)
        {
            all += nums[i];
            maxPrev = max(nums[i], nums[i] + maxPrev);
            maxSum = max(maxSum, maxPrev);//记录可能更新的最大累加和

            minPrev = min(nums[i], nums[i] + minPrev);
            minSum = min(minPrev, minSum);
        }
        return minPrev == all ? maxSum : max(maxSum, all - minSum);
    }
};


//使用两个状态进行记录,经过以上分析需要记录区间最大和以及区间最小和两个条件
//f[i]表示区间最大和
//g[i]表示区间最小和
//f[i] = max(f[i-1],f[i-1]+nums[i])
//g[i] = min(g[i-1],g[i-1]+nums[i])
//两个状态之间没有关系,只是同时记录
//涉及到初始化以及i-1涉嫌越界的边界条件,采用多开一个空间的方式.1. 初始化新开的位置 2. 访问原数组时下标-1
//初始化f[0]时,如果[1](原0位置元素)<0,那么求最大肯定是不选为好,累加和不变,就应该加0即可.
//                              >0,那么求最大肯定是选为好,累加和+nums[1]
//最终决定将f[0]=0时满足上述分析
//同理将g[0]=0
class Solution22
{
public:
    int maxSubarraySumCircular(vector<int>& nums)
    {
        int n = nums.size();
        vector<int>f(n + 1);
        vector<int>g(n + 1);
        f[0] = g[0] = 0;
        int maxSum = INT_MIN, minSum = INT_MAX;
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            f[i] = max(nums[i - 1], nums[i - 1] + f[i - 1]);
            maxSum = max(maxSum, f[i]);
            g[i] = min(nums[i - 1], nums[i - 1] + g[i - 1]);
            minSum = min(minSum, g[i]);

            sum += nums[i - 1];
        }
        return sum == minSum ? maxSum : max(sum - minSum, maxSum);
    }
};