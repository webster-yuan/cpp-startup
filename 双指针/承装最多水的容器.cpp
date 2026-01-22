//https://leetcode.cn/problems/container-with-most-water/description/
//
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
    //暴力 枚举左右区间计算最大容纳量[left,right]
    //V= (right-left) * min()
    //优化: right是否需要每次都回退到left+1的位置重新往后走
    //left++,1. 范围肯定小了,2. 如果上次计算时高度是由right决定的,right 是较小值,这次不管nums[left]如何V都是减小的 3. 如果上次计算时高度是由left决定的,left是较小值,3.1 nums[left+1]>right,需要计算.3.2 如果nums[left+1]<right,V肯定减小不用算了
    //所以,不用回退right,left++过程中如果存在if([left]< [right] && [left+1]>right)计算一下,其余在left<right时均不需要计算
    //我为什么不从两边往中间找呢?
    //高度是哪边决定的,
    int maxArea(vector<int>& height)
    {
        int left = 0, right = height.size() - 1;
        int ret = INT_MIN;
        while (left < right)
        {
            int tmp = (right - left) * min(height[left], height[right]);
            ret = max(ret, tmp);
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return ret;

        // int left=0,right=0;
        // int ret=0;
        // for(int i=0;i<height.size();i++)
        // {
        //     int tmp=0;
        //     while(left<=right)
        //     {
        //         tmp=(right-left)*min(height[left],height[right]);
        //         ret=max(ret,tmp);
        //         if(height[left]<height[right] && height[left+1] >height[right])
        //         {
        //             tmp=(right-left)*min(height[left],height[right]);
        //             ret=max(ret,tmp);
        //         }
        //         left++;
        //     }
        // }
    }
};