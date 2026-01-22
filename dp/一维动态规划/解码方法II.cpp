//https://leetcode.cn/problems/decode-ways-ii/description/
//https://www.bilibili.com/video/BV1Ww41167Ac?t=6763.3
#include<iostream>
#include<vector>
using namespace std;

//在解码方法的基础上增加了*可以转化为1~9中任意一个数字,对i和i+1位置进行讨论即可
class Solution1
{
public:
    int numDecodings(string s) 
    {
        return func(s, 0);
    }
    int func(string& s, int i)
    {
        if (i == s.size())
            return 1;
        if (s[i] == '0')
            return 0;
        //单独转化
        int ans = func(s, i + 1) * (s[i] == '*' ? 9 : 1);
        if (i + 1 < s.size())
        {
            if (s[i] != '*')
            {
                if (s[i + 1] != '*')
                {
                    //s[index]:  num num
                    //index:     i  i+1
                    if ((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26)
                        ans += func(s, i + 2);
                }
                else
                {
                    //s[index]:  num *
                    //index:     i  i+1
                    if (s[i] == '1')
                        ans += 9 * func(s, i + 2);
                    else if (s[i] == '2')
                        ans += 6 * func(s, i + 2);
                }
            }
            else
            {
                if (s[i + 1] != '*')
                {
                    //s[index]:  * num
                    //index:     i i+1
                    if (s[i + 1] <= '6')
                        ans += 2 * func(s, i + 2);//11~16 21~26 两种方法
                    else
                        ans += func(s, i + 1);//17~19 一种方法
                }
                else
                {
                    //s[index]:  * *
                    //index:     i i+1
                    ans += 15 * func(s, i + 2);
                }
            }
        }
        return ans;
    }
};
class Solution2
{
    vector<long long>memo;
    static const long long mod = 1000000007;
    int n;
public:
    int numDecodings(string s)
    {
        n = s.size();
        memo = vector<long long>(n,-1);
        return (int)func(s, 0);
    }
    long long func(string& s, int i)
    {
        if (i == s.size())
            return 1;
        if (s[i] == '0')
            return 0;
        if (memo[i] != -1)
            return memo[i];

        //单独转化
        long long  ans = func(s, i + 1) * (s[i] == '*' ? 9 : 1);
        if (i + 1 < s.size())
        {
            if (s[i] != '*')
            {
                if (s[i + 1] != '*')
                {
                    //s[index]:  num num
                    //index:     i  i+1
                    if ((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26)
                        ans += func(s, i + 2);
                }
                else
                {
                    //s[index]:  num *
                    //index:     i  i+1
                    if (s[i] == '1')
                        ans += 9 * func(s, i + 2);
                    else if (s[i] == '2')
                        ans += 6 * func(s, i + 2);
                }
            }
            else
            {
                if (s[i + 1] != '*')
                {
                    //s[index]:  * num
                    //index:     i i+1
                    if (s[i + 1] <= '6')
                        ans += 2 * func(s, i + 2);//11~16 21~26 两种方法
                    else
                        ans += func(s, i + 2);//17~19 一种方法
                }
                else
                {
                    //s[index]:  * *
                    //index:     i i+1
                    ans += 15 * func(s, i + 2);
                }
            }
        }
        ans %= mod;
        memo[i] = ans;
        return ans;
    }
};
//严格位置依赖,转化为dp,从右往左填表
//初始化dp[n]=1
//将上面的ans转化为dp[i]即可,最后别忘了取模
