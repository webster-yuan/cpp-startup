//https://leetcode.cn/problems/max-value-of-equation/description/
// 横坐标 x 的值从小到大排序的二维数组代表二维平面的坐标值
// yi + yj + |xi - xj| 的最大值,也就是找到两个点的坐标最大值,并且要求这两个点
// x坐标相差不能超过K
//
// 表达式转化为 yi + yj +xj-xi => xj+yj + yi- xi的最大值
// 也就是到大一个点时yj+xj值是确定大小的,要找到之前区间中yi-xi值最大的点
//使用单调队列,维护一个从大到小的单调性,然后获取队头元素后计算和最大值.
//以key=yi-xi维护单调性,以不超过K来控制队头的过期操作,弹出队头操作
//如果新来的值,比之前的和更大,更好的指标,并且比之前的最大值更接近j位置,所以可以弹出队尾
//<index,yi-xi>
//因为这个题中保证x值是从左到有升序的,所以完全可以用x值来替代index唯一标识
//<x,y>
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
    int MAXLEN = 100001;
public:
    int findMaxValueOfEquation(vector<vector<int>>& nums, int k)
    {
        int n = nums.size();
        vector<vector<int>>dq(MAXLEN,vector<int>(2));
        int h =0, t = 0;
        int ans = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            int x = nums[i][0];
            int y = nums[i][1];
            while (h < t && dq[h][0] + k < x)//此时点的x坐标
                h++;
            if (h < t)
                ans = max(ans, x+y+dq[h][1]-dq[h][0]);
            while (h < t && dq[t-1][1]-dq[t - 1][0] <= y-x)
                t--;
            dq[t][0] = x;
            dq[t][1] = y;
            t++;
        }
        return ans;
    }
};