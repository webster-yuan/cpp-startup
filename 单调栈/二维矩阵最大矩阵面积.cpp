
//https://www.bilibili.com/video/BV1HH4y1X7T9?t=6074.5

//二维数组进行压缩数组操作,
//分别以index行为底进行压缩数组操作,然后进行柱状图最大面积的计算
//在压缩数组的时候,nums[j]代表从index行j位置网上有多少个连续的1,
//然后在nums数组中进行直方图最大面积的计算
//假设数组是n*m,那么加工数组时需要O(M),一共加工n次,所以时间复杂度是O(N*M)


#include<iostream>
#include<vector>
using namespace std;
class Solution
{
    vector<int>tmp;
    int r;
    vector<int>st;
public:
    int maximalRectangle(vector<vector<char>>& nums)
    {
        int n = nums.size(), m = nums[0].size();
        tmp = vector<int>(m);
        st = vector<int>(m);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                tmp[j] = nums[i][j] == '0' ? 0 : tmp[j] + 1;
            ans = max(ans, largestRectangleArea(m));
        }
        return ans;
    }
    int largestRectangleArea(int m)
    {
        r = 0;
        int ans = 0, cur=0, left=0;
        for (int i = 0; i < m; i++)
        {
            while (r > 0 && tmp[st[r - 1]] >= tmp[i])
            {
                cur = st[--r];
                left = r > 0 ? st[r - 1] : -1;
                ans = max(ans, tmp[cur] * (i - left - 1));
            }
            st[r++] = i;
        }
        while (r > 0)
        {
            cur = st[--r];
            left = r > 0 ? st[r - 1] : -1;
            ans = max(ans, (m - left - 1) * tmp[cur]);
        }
        return ans;
    }
};