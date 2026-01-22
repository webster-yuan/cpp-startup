//https://leetcode.cn/problems/increasing-triplet-subsequence/submissions/474081438/
#include<iostream>
#include<vector>
using namespace std;
//使用贪心的思想,只要出现了长度为3的递增子序列,就返回true
//所以完全可以使用两个变量来记录长度为1,长度为2的子序列的最后一个值
class Solution
{
public:
    bool increasingTriplet(vector<int>& nums)
    {
        int a = nums[0], b = INT_MAX;
        int n = nums.size();
        for (int i = 1; i < n; i++)
        {
            if (nums[i] > b) return true;
            else if (nums[i] > a) b = nums[i];
            else if (nums[i] < a) a = nums[i];
        }
        return false;
    }
};