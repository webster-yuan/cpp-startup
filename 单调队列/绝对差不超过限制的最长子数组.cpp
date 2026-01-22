
// https://leetcode.cn/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/
// https://www.bilibili.com/video/BV11h4y1w7Bu?t=3209.2
// 给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，
// 该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。
// 如果不存在满足条件的子数组，则返回 0 。

//使用窗口得分析单调性,题干说的是区间中任意两个数字之间的差值,那么极端情况就是最大值和最小值的差值
//如果满足情况,那么他就是合法的区间,可以更新长度最大值.那么随着右区间的扩大,新进来的数字
//会使差值变得更大,或者不变.当新进来的数字比最大值大,或者比最小值小时就会使得差值变大,如果介于中间,长度++;
//单调性就出来了.如果一个小区间不达标,那么再扩出去的大区间肯定不达标,所以l++;
// 如果一个大区间都达标,那么小区间一定达标.
// 当新进来的数字导致差值>limit时,从l出发的长度就确定了,记录最大值.
//那么如何随时随地O(1)获取区间的最大值和最小值呢?使用两个单调队列就行了
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
    static const int N = 100001;
    vector<int>arr; 
    int min_h, min_t;
    int max_h, max_t; 
    int maxDeque[N] = { 0 };//大双端队列
    int minDeque[N] = { 0 };//小双端队列
public:
    int longestSubarray(vector<int>& nums, int limit) 
    {
        min_h = min_t = max_h = max_t = 0;

        arr = nums;
        int ans = 0;
        //[L,R),每次都是问R位置数字能否进来
        int n = arr.size();
        for ( int l = 0, r = 0; l < n; l++)
        {
            while (r < n && ok(limit, nums[r]))
                push(r++);

            ans = max(ans, r - l);
            pop(l);
        }
        return ans;
    }
    bool ok(int limit, int num)
    {
        int max_val = max_h < max_t ? max(arr[maxDeque[max_h]], num) : num;
        int min_val = min_h < min_t ? min(arr[minDeque[min_h]], num) : num;
        return max_val - min_val <= limit;
    }
    void push(int r)
    {
        while (max_h < max_t && arr[maxDeque[max_t - 1]] <= arr[r])
            max_t--;
        maxDeque[max_t++] = r;
        while (min_h < min_t && arr[minDeque[min_t - 1]] >= arr[r])
            min_t--;
        minDeque[min_t++] = r;
    }
    void pop(int l)
    {
        if (max_h < max_t && maxDeque[max_h] == l)
            max_h++;
        if (min_h < min_t && minDeque[min_h] == l)
            min_h++;
    }
};