//https://www.bilibili.com/video/BV1Ww41167Ac?t=11929.0
//用一张表,分别记录每个字符为结尾的子序列集合的个数
//到达i位置,在之前出现过的子序列后面添加i位置字符,
//纯新增子序列个数 = all -当前字符上次记录
//然后,当前字符记录+=纯新增
//	 ,all+=纯新增
//https://leetcode.cn/problems/distinct-subsequences-ii/description/
//cnts[i]代表以i位置 字符 为结尾的不同子序列的个数
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int distinctSubseqII(string s)
    {
        int mod = 1000000007;
        vector<int>cnts(26);
        int all = 1;//空集个数一个
        int newAdd = 0;
        for (char x : s)
        {
            newAdd = (all - cnts[x - 'a'] + mod) % mod;
            cnts[x - 'a'] = (cnts[x - 'a'] + newAdd) % mod;
            all = (all + newAdd) % mod;
        }
        return (all - 1 + mod) % mod;
    }
};