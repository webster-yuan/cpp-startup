//https://leetcode.cn/problems/trapping-rain-water/
//i位置上方能够存放几个格子的水量,然后累加
//water[i]= min(左侧区间最大值,右侧区间最大值) -arr[index],
//如果water[i]<0,说名index位置足够高,导致没有水存储,直接等于0就行
//补充之后: water[i]= max(0,min(左侧区间最大值,右侧区间最大值) -arr[index])
//所以可以使用辅助数组分别记录i位置左侧最大值,右侧最大值是什么即可

//解法二: 双指针优化空间复杂度
//lmax=nums[0],rmax=nums[n-1],l=1,r=n-2
//if lmax>rmax,那么r位置的水量就可以确定了,因为r位置水量取决于左右两侧最大值中较小值,也就是rmax,
//为什么可以说确定呢? 如果左侧区间中不存在比lmax更大值,选择的瓶颈是rmax,存在比lmax更大的值,选择瓶颈依然是rmax
//所以说可以确定了,计算水量之后,移动r指针,更新rmax
//同理 lmax<rmax
//当lmax==rmax时,都可以选择更新,随便那个都行.
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    //<O(N),O(N)>
    int trap1(vector<int>& nums)
    {
        int n = nums.size();
        vector<int>left(n);
        vector<int>right(n);
        left[0] = nums[0];
        for (int i = 1; i < n; i++)
            left[i] = max(nums[i], left[i - 1]);
        right[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--)
            right[i] = max(right[i + 1], nums[i]);
        int ans = 0;
        for (int i = 1; i < n - 1; i++)
            ans += max(0, min(left[i], right[i]) - nums[i]);
        return ans;
    }
    int trap(vector<int>& nums)
    {
        int n = nums.size();
        int l = 1, r = n - 1, lmax = nums[0], rmax = nums[n - 1];
        int ans = 0;
        while (l <= r)
        {
            if (lmax <= rmax)
            {
                ans += max(0, lmax - nums[l]);
                lmax = max(nums[l++], lmax);
            }
            else
            {
                ans += max(0, rmax - nums[r]);
                rmax = max(nums[r--], rmax);
            }
        }
        return ans;
    }
};