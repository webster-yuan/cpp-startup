//https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/description/

//基于贪心的思想
//取反操作为了得到最大数组和,所以优先对负数进行取反操作,
//所以负数的个数m和k的大小比较就十分关键
//if m>=k,就选中最小的那几个负数转化为正数即可
//else 1. 将所有的负数可以完全转化为正数,
//	   2. 需要对k剩下的次数奇偶进行判断,k-=m
//			2.1 如果是偶数,直接返回即可,直接对一个正数操作,偶数次取反操作得到最大
//			2.2 如果是奇数,就选择最小的那个数字进行一次取反操作即可.
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution 
{
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) 
    {
        int m = 0, n = nums.size(), minElem = INT_MAX;
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] < 0)m++;
            minElem = min(minElem, abs(nums[i]));
            sum += abs(nums[i]);
        }
        int ret = 0;
        if (m >= k)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < k; i++)
                ret += abs(nums[i]);
            for (int i = k; i < n; i++)
                ret += nums[i];
        }
        else
        {
            if ((k - m) % 2 == 0)
            {
                ret = sum;
            }

            else
            {
                ret = sum;
                ret -= 2*minElem;//一正一负,总和减去的是二倍的
            }
        }
        return ret;
    }
};