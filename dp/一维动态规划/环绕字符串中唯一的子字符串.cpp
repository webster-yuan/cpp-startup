//https://leetcode.cn/problems/unique-substrings-in-wraparound-string
#include<iostream>
#include<vector>
using namespace std;
//思路1:
//以i位置 字符 为结尾,dp[i]表示以i位置 字符 为结尾的所有子串中,在Base中出现过的个数
// 
//问题划分: 自己一个子串(一定在Base中出现1)以及和前面的结合构成子串,
// 
//以i-1元素为结尾在base中出现过,dp[i-1],在加上我之后还出现过,[i-1]+1=[i] || [i-1]=='z'&&[i]=='a'
//在尾巴上加上,个数和前i-1个相同,dp[i]=dp[i-1].
//dp[i]=dp[i-1] +1 
//初始化: 所有都初始化为1,所以转移方程只需要判断和前面结合情况成立时,dp+=dp[i-1]
//填表顺序: 从左到右
//返回值:返回所有dp表里面的值加起来的和.但是,会存在重复字符导致重复累加,所以要去重
//相同字符结尾的dp值,我们取较大的即可.因为较大的代表相同字符结尾更长的那个字符串,肯定包含计算了短的那个字符串,这样就避免了重复计算.
//用int [26]保存对应字符结尾的最大dp值即可.返回数组里面的和
class Solution
{
public:
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int>dp(n, 1);
        //以i位置 字符 为结尾的所有子串在Base中出现的次数
        //自己一个->1或者和前面的部分组合->dp[i]=dp[i-1],如果是长度才+1
        for (int i = 1; i < n; i++)
        {
            if (s[i - 1] + 1 == s[i] || (s[i - 1] == 'z' && s[i] == 'a'))
                dp[i] += dp[i - 1];
        }
        //相同字符结尾的,长的肯定包含计算了短的,要的是累加和,所以要去重
        //保留最大即可完成
        int hash[26] = { 0 };
        for (int i = 0; i < n; i++)
            hash[s[i] - 'a'] = max(dp[i], hash[s[i] - 'a']);
        int ret = 0;
        for (auto e : hash)
            ret += e;
        return ret;
    }
};
//思路二:
//以i位置字符为结尾,在S串中探讨出现过的最大长度,即可完成讨论在Base串中出现次数,去重的功能
//ab串以b为结尾往前最大延伸长度是2<=>以b位置字符为结尾,构成的子串中在Base中出现过的,一共有两个,b,ab
// 问题转化:
//dp[i]表示在s字符串中以i位置字符为结尾,往前最大延伸长度是多少,当然是在满足base串规则的前提下
//https://www.bilibili.com/video/BV1Ww41167Ac?t=10659.2
class Solution
{
public:
    int findSubstringInWraproundString(string s)
    {
        int n = s.size();
        vector<int>str(n);
        for (int i = 0; i < n; i++)
            str[i] = s[i] - 'a';

        vector<int>dp(26);//统计的是26个字符,往前能够扩充的最大长度
        dp[str[0]] = 1;
        for (int i = 1,len=1; i < n; i++)
        {
            int cur = str[i];
            int prev = str[i - 1];
            if (prev + 1 == cur || (prev == 25 && cur == 0))
                len++;
            else
                len = 1;
            dp[cur] = max(dp[cur], len);
        }
        int ans = 0;
        for (int i=0;i<26;i++)
            ans += dp[i];
        return ans;
    }
};