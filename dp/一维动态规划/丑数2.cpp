//https://leetcode.cn/problems/ugly-number-ii/
//丑数: 默认第一个数字是1,其他数字只能包含质因子2 3 5组成的数
//请返回第n个丑数

//暴力: 将在1~n区间中一个个验证的过程,优化为写出下一个丑数是谁的过程
//已知丑数1,备选下一个丑数是1*2=2,1*3=3,1*5=5,选择最靠近cur的那个,所以下一个丑数是2
// ...
//https://www.bilibili.com/video/BV1Ww41167Ac?t=8383.9 
//选中三个指针,分别代表*2,*3,*5,初始化指向第1个丑数
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
public:
    int nthUglyNumber(int n) 
    {
        vector<int>dp(n + 1);
        dp[1] = 1;
        for (int i = 2, i2 = 1, i3 = 1, i5 = 1, cur = 0; i <= n; i++)
        {
            int a = dp[i2] * 2;
            int b = dp[i3] * 3;
            int c = dp[i5] * 5;
            cur = min(a, min(b, c));
            if (cur == a)
                i2++;
            if (cur == b)
                i3++;
            if (cur == c)
                i5++;
            dp[i] = cur;
        }
        return dp[n];
    }
};