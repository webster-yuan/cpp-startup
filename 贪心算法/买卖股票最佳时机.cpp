#include<iostream>
#include<vector>
using namespace std;
//https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/submissions/475455191/
//暴力方式是两层for循环,分别枚举买入点和卖出点
//枚举index位置为卖出的位置,需要找出[0,index-1]区间中的最小值.
//可以使用变量随着遍历的过程记录过程中的最小值
class Solution 
{
public:
    int maxProfit(vector<int>& prices) 
    {
        int ret = 0;
        int preMin = INT_MAX;
        for (int i = 0; i < prices.size(); i++)
        {
            ret = max(ret, prices[i] - preMin);
            preMin = min(preMin, prices[i]);
        }
        return ret; 
    }
};