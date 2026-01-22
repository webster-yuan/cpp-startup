//https://leetcode.cn/problems/gas-station/	
//思路: gas[i]代表从i位置能够获取到的油量,cost[i]代表从i位置到达下一个位置消耗的油量
//leave= gas[i]-cost[i]代表到达i+1位置时油剩余多少.如果leave>=0,代表油剩下了,leave<0代表到中间就停下了
// 就代表从i位置无法到达i+1位置.
//判断从哪个位置为起点能够走一圈,也就是能够到达n个节点,
// 那么以每个位置为起点都进行一次上述过程,如果中途出现leave<0,
//说明此时的点无法实现走一圈,那么就去遍历下一个点.这样就相当于暴力尝试,T(N)=O(N^2),每次走left时都需要将right回退到left+1位置
//优化为滑动窗口: 如果发现leave<0了,left++,leave-[left],之后右区间尝试继续往下扩充.
//因为存在的解题目规定是唯一的,那么就返回.

//题型: 滑动窗口,以left位置为起点分析问题
//找到范围和答案指标之间的单调性关系
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
    {
        int n = gas.size();
        int len = 0;
        for (int l = 0, r = 0, sum = 0; l < n; l++)
        {
            while (sum >= 0)
            {
                if (len == n)
                    return l;
                //窗口即将进来的数字
                r = (l + (len)) % n;
                len++;
                sum += gas[r] - cost[r];
            }
            //sum<0
            len--;
            sum -= gas[l] - cost[l];
        }
        return -1;
    }
};