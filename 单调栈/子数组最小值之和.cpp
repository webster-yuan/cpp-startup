//https://leetcode.cn/problems/sum-of-subarray-minimums/description/
//给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
//由于答案可能很大，因此 返回答案模 10 ^ 9 + 7 。

//使用单调栈思想找到cur位置左右两侧比自己小的最近的数字位置x,y
// 那么在[x+1,y-1]区间中,cur就是最小值,那么必须包含cur的子数组的个数就是
// (cur-x) * (y-cur)个,那么这些数组的和就是个数*arr[cur]
//个数求解 : https://www.bilibili.com/video/BV1HH4y1X7T9?t=4183.4
// 单调栈相等值时仍然采取弹出操作
//存在相等值时可能存在漏算? 分析,后序可以将落下的修正对
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int sumSubarrayMins(vector<int>& arr)
    {
        const int MOD = 1000000007;
        int n = arr.size();
        vector<int>st(n);
        long long ans = 0;
        int r = 0;
        for (int i = 0; i < n; i++)
        {
            while (r > 0 && arr[st[r - 1]] >= arr[i])
            {
                int cur = st[--r];
                int left = r == 0 ? -1 : st[r - 1];
                ans = (ans + (long long)(cur - left) * (long long)(i - cur) * arr[cur]) % MOD;
            }
            st[r++] = i;
        }
        while (r > 0)
        {
            int cur = st[--r];
            int left = r == 0 ? -1 : st[r - 1];
            ans = (ans + (long long)(cur - left) * (long long)(n - cur) * arr[cur]) % MOD;
        }
        return (int)ans;
    }
};
