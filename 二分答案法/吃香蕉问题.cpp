//给定香蕉数组,arr[index]代表的是香蕉数量
//在规定时间time内,求出能够将所有香蕉吃完的至少每个小时应该吃多少香蕉,
//也就是将吃香蕉的速度求出来.
//规则: 假设速度是v,如果v>arr[index],吃完之后尽管有剩余,选择休息

//确定这个速度的范围,[1,maxVal],maxVal就是所有香蕉中最大值,一个小时保证能吃完
//也没有必要定速度是更大值了.
//单调性: 速度越大,那么吃完所有香蕉的时间就会越小
//因为单调性的存在,可以二分的缩小区间排除可能性
//二分法确定速度,看此时的速度能否在规定时间内都吃完
//那么就需要实现f函数,告诉我这个速度下是否能够完成所有香蕉
//https://leetcode.cn/problems/koko-eating-bananas/
//T= O(N* log(max()))
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
public:
    int minEatingSpeed(vector<int>& piles, int h)
    {
        int l = 1, r = 0;
        for (int x : piles)
            r = max(r, x);
        int ans = 0;
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (func(piles, m)<=h)
            {
                ans = m;
                r = m - 1;
            }
            else
                l = m + 1;
        }
        return ans;
    }
    //根据规则求速度其实就是向上取整a/b向上取整= (a+b-1)/b
    long func(vector<int>& piles, int m)
    {
        long ans = 0;
        for (int x : piles)
        {
            ans += (x + m - 1) / m;
        }
        return ans;
    }
};