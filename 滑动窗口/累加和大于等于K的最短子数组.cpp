//https://leetcode.cn/problems/minimum-size-subarray-sum/description/

//题解:
//滑动窗口

#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    //O(N):r一直往右走,走到n就停下来了
    int minSubArrayLen(int target, vector<int>& nums)
    {
        int ans = INT_MAX;
        int sum = 0;
        for (int l=0,r=0;r<nums.size();r++)
        {
            sum += nums[r];
            while (sum - nums[l] >= target)//持续弹出左边界,寻求满足条件的最小值
                sum -= nums[l++];
            if (sum >= target)
                ans = min(ans, r - l + 1);
        }
        return ans==INT_MAX?0:ans;
    }
};