//https://leetcode.cn/problems/find-k-th-smallest-pair-distance/
// https://www.bilibili.com/video/BV1Mh4y1P7qE?t=4583.4
//数值对差值范围,[0,maxVal-minVal]
//提供func函数,给定差值m,返回差值小于等于m的数值对的个数有多少个,
//单调性: 当差值越大时,小于等于这个差值的数值对个数就越多(注意是小于等于)
//if ret<k,说明数值定小了,得去右侧区间中寻找值. if ret>=k,记录答案,到左侧
//数组中数字状况并不影响结果,所以可以排序
//排序: nlogn + log(max-min)*n
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
    int smallestDistancePair(vector<int>& nums, int k)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int l = 0, r = nums[n - 1] - nums[0];
        int ans = 0;
        while (l <= r)
        {
            int mid = ((r - l) / 2) + l;
            if (func(nums, mid) < k)
                l = mid + 1;
            else
            {
                ans = mid;
                r = mid - 1;
            }
        }
        return ans;
    }
    //在有序数组中寻找数值对小于等于limit 的数值对有多少个
    //使用窗口解决,两个指针不回退,O(N)
    int func(vector<int>& nums, int limit)
    {
        int n = nums.size();
        int ans = 0;
        for (int l = 0, r = 0; l < n; l++)
        {
            while (r + 1 < n && nums[r + 1] - nums[l] <= limit)
                r++;
            //[0,3]=>[0,1][0,2][0,3]三对都满足情况
            ans += r - l;
        }
        return ans;
    }
};