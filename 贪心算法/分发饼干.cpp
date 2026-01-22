
//https://leetcode.cn/problems/assign-cookies/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//首先肯定需要先将数组进行排序
//如果s[j]>g[i],说明这个孩子可以满足,所以ret++;
//排序之后采用这种贪心的思想.
//采用交换论证法验证正确
class Solution 
{
public:
    int findContentChildren(vector<int>& g, vector<int>& s) 
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int n = g.size(), m = s.size();
        int ret = 0;
        for (int i = 0, j = 0; i < n && j < m; i++,j++)
        {
            while (j<m && g[i] > s[j])
                j++;
            if (j < m) ret++;
        }
        return ret;
    }
};