//https://leetcode.cn/problems/daily-temperatures/
//给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，
// 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。
// 如果气温在这之后都不会升高，请在该位置用 0 来代替。

//寻找后面距离自己最近比自己大的元素,
//使用单调栈的思想,维护从底到顶从大到小的顺序
//区别与模版,相等情况下也能进,因为弹出时可以更新
#include<iostream>
#include<vector>
using namespace std;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int>& nums)
    {
        int n = nums.size();
        vector<int>st(n);
        vector<int>ans(n);
        int r = 0;
        for (int i = 0; i < n; i++)
        {
            while (r > 0 && nums[st[r - 1]] < nums[i])
            {
                int pop = st[--r];
                ans[pop] = i-pop;
            }
            st[r++] = i;
        }
    }
};