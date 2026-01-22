//https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
#include<iostream>
#include<vector>
using namespace std;
//暴力的方式是使用双指针,固定left,移动right,找到以left为开头的递增子数组的长度,确定右端点right-1
//必然此时[right]<[left],那么在[left+1,right-1]中所有值都比[right]大,所以区间固定,
//如果left右移,长度在进一步缩小,所以可以直接让left=right,跳到right的位置,继续往下寻找,提升效率.
//贪心+双指针
class Solution
{
public:
    int findLengthOfLCIS(vector<int>& nums)
    {
        int ret = 0, n = nums.size();
        for (int i = 0; i < n;)
        {
            int j = i + 1;
            while (j<n && nums[j]>nums[j - 1])
                j++;
            ret = max(ret, j - i);
            i = j;
        }
        return ret;
    }
};