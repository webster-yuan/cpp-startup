//https://leetcode.cn/problems/longest-valid-parentheses/
#include<iostream>
#include<vector>
using namespace std;
//以i位置为结尾,往左推,最长能够得到多长的有效括号子串
//最后得到所有情况中的最大值即可
//利用之前求出来的dp[i]讨论更新自己
//https://www.bilibili.com/video/BV1Ww41167Ac?t=9379.2
//dp[i]代表必须以i位置为结尾的情况下,最左能推多远
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int n = s.size();
        vector<int>dp(n);
        int ans = 0;
        for (int i = 1; i < n; i++)
        {
            if (s[i] == ')')
            {
                int prev = i - dp[i - 1] - 1;
                if (prev >= 0 && s[prev] == '(')
                    dp[i] = dp[i - 1] + 2 + (prev > 0 ? dp[prev - 1] : 0);
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
#include<stack>
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        stack<int>st;//栈中存下标,方便计算长度
        int ret = 0;
        st.push(-1);//方便直接减
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                st.push(i);
            else
            {
                st.pop();
                if (st.empty())
                    st.push(i);//方便直接减
                else
                    ret = max(ret, i - st.top());//方便直接减
            }
        }
        return ret;
    }
};