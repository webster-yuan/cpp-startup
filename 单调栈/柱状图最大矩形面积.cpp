//https://leetcode.cn/problems/largest-rectangle-in-histogram/description/
//使用单调栈的思想,找到index位置左右两侧比自己小的位置,那么大压小的单调性,相等时候也弹出,
//以自己的高度往左右两边进行扩充,如果nums[cur]<=左右两侧的高度,代表能扩充,否则就停下
// 得到的面积就是(i-left-1)*nums[cur],最后记录所有情况最小值即可
//模版严格找左右两侧最小可以做
//不用模板,当存在重复值时如何做呢?https://www.bilibili.com/video/BV1HH4y1X7T9?t=5368.6,发现可以修正

#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int largestRectangleArea(vector<int>& nums)
    {
        int n = nums.size();
        vector<int>st(n);
        int r = 0;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            while (r > 0 && nums[st[r - 1]] >= nums[i])
            {
                int cur = st[--r];
                int left = r>0 ?st[r - 1]:-1;
                ans = max(ans, (i - left - 1) * nums[cur]);
            }
            st[r++] = i;
        }
        while (r > 0)
        {
            int cur = st[--r];
            int left = r > 0 ? st[r - 1] : -1;
            ans = max(ans, (n - left - 1) * nums[cur]);
        }
        return ans;
    }
};