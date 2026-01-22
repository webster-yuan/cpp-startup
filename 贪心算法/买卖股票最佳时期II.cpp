//https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
//贪心: 肯定在股票上升的阶段买卖股票,在最低点买入,在最高点卖出
//解法一:
// 采用双指针的方式,分别记录最低点和最高点即可.
//解法二:
//连续上涨交易日: 指望着今天买最后一天卖,pn-p1=p2-p1 + p3-p2 + ... + pn-pn-1
//相当于在上升区间中每天都在交易
//连续下降交易:直接不买也不卖,最起码不会亏钱
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int maxProfit1(vector<int>& prices)
    {
        int ret = 0;
        int n = prices.size();
        for (int i = 0; i < n;i++ )
        {
            int j = i;
            while (j + 1 < n && prices[j + 1] > prices[j])
                j++;
            ret += prices[j] - prices[i];
            i = j;
        }
        return ret;
    }
    int maxProfit2(vector<int>& prices) 
    {
        int ret = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if (prices[i] > prices[i - 1])
            {
                ret += prices[i] - prices[i - 1];
            }
        }
        return ret;
    }
};