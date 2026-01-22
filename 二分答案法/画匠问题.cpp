//https://www.bilibili.com/video/BV1Mh4y1P7qE?t=1775.5
//https://leetcode.cn/problems/split-array-largest-sum/
//如何划分区间划分为连续的K份,让每一份累加和的最大值尽量小

//确定累加和sum范围,[0,整个数组累加和A],当数组中都是0时累加和都是0,如果只有一个画家,那么完成时间就是整体累加和
//范围可以定的很粗糙,因为二分的效率很高
//单调性: 划分的区间越多,每一个区间中的累加和越小,自然而然所有区间中累加和最大值也越小
//提供一个函数func(),给定累加和m,返回让所有区间中累加和最大值不超过m时,至少要划分多少个区间
//如果返回值ret<=k,说明[m,A]区间中都是达标的,有的画家甚至还没有被安排工作,所以就到左侧区间,让累加和尽可能的小
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
public:
    int splitArray(vector<int>& nums, int k)
    {
        int l = 0, r = 0;
        for (int x : nums)
            r += x;
        int ans = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            int cur = func(nums, mid);
            if (cur <= k)
            {
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        return (int)ans;
    }
    //当某一单点超过m,说明无法划分区间
    int func(vector<int>& nums, int m)
    {
        int sum = 0;
        int count = 1;//划分得到的区间数量初始化为1
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > m)
                return INT_MAX;
            if (sum + nums[i] > m)
            {
                count++;
                sum = nums[i];
            }
            else
                sum += nums[i];
        }
        return count;
    }
};