//https://leetcode.cn/problems/decode-ways/
#include<iostream>
#include<vector>
using namespace std;


//从左到右尝试模型
//func(i)代表将s[i...]所有数字字符转化的方法数
//1. '0'转化不了,后序都转化不了,代表决策树中这一个分支可以直接返回,s[i...]方法数是0
//2. 自己转
//3. 自己和后面一个字符转化
class Solution1
{
public:
    int numDecodings(string s)
    {
        return func(s,0);
    }
    int func(string& s, int i)
    {
        if (i == s.size())//代表这个分支可以走通,是一种方法
            return 1;
        if (s[i] == '0')
            return 0;
        int ans = 0;
        if (i + 1 < s.size() && (s[i] - '0') * 10 + (s[i + 1] - '0') <= 26)
            ans += func(s, i + 2);
        return ans;
    }
};
//存在重复计算,可以改为记忆化搜索
class Solution2
{
    vector<int>memo;
    int n;
public:
    int numDecodings(string s)
    {
        n = s.size();
        memo = vector<int>(n,-1);
        return func(s, 0);
    }
    int func(string& s, int i)
    {
        if (i == s.size())//代表这个分支可以走通,是一种方法
            return 1;

        if (memo[i] != -1)
            return memo[i];

        int ans = 0;
        if (s[i] == '0')
        {
            ans = 0;
        }
        else
        {
            ans += func(s, i + 1);
            if (i + 1 < s.size() && (s[i] - '0') * 10 + (s[i + 1] - '0') <= 26)
                ans += func(s, i + 2);
        }
        memo[i] = ans;
        return ans;
    }
};

//严格位置依赖分析: 从右往左填写表格
class Solution3 
{
public:
    int numDecodings(string s) 
    {
        int n = s.size();
        vector<int>dp(n + 1);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == '0')
                dp[i] = 0;
            else
            {
                dp[i] = dp[i + 1];
                if (i + 1 < n &&( (s[i] - '0') * 10 + (s[i + 1] - '0') <= 26))
                    dp[i] += dp[i + 2];
            }
        }
        return dp[0];
    }
};
//发现i位置只依赖于i+1和i+2位置,所以可以用两个变量记录,滚动更新即可
//空间复杂度优化为O(1)
class Solution4
{
public:
    int numDecodings(string s)
    {
        int n = s.size();
        int next = 1;//dp[i]
        int nextnext = 0;//dp[i+1]
        for (int i = n - 1,cur=0; i >= 0; i--)
        {
            if (s[i] == '0')
                cur = 0;
            else
            {
                cur = next;
                if (i + 1 < n && ((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26))
                    cur += nextnext;
            }
            nextnext = next;
            next = cur;
        } 
        return next;
    }
};