//https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/

//要求子串中每一种字符出现的次数都>=k,求出最长子串的长度
//基于暴力优化为滑动窗口
//      单调性存在于哪里?种类数规定好,在[l,r]范围内先找到require种,然后再扩大缩小,找满足.实现单调性
// 没有单调性,根据种类创造单调性去做.
// 
//提供函数实现,子串中必须只包含i种字符,每种字符次数>=k,最长是多长,(1<=i<=26)
//那么每次要求的字符种类是require种,每种必须出现>=k次,
// 词频统计数组cnts[26]={0}
//那么在过程中需要两个变量,collect: 统计已经出现的字符种类,count是对应出现次数; 
// satisfy: 统计出现次数已经>=k的字符种类个数. count==K 时,satisfy++
//r++,当satisfy==require时,说明此时require种字符都出现了k次,记录此时的ans,
//继续往后的过程中,可能safisfy仍然不变化,但是长度变长了,ans持续更新,while
//当添加r位置之后,发现collect>require了,左边界left++,直到让collect==require才行.while
//然后继续找这新的两个字符组合,他们满足>=k的最长长度
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int longestSubstring(string s, int k)
    {
        int n = s.size();
        int ans = 0;
        for (int require = 1; require <= 26; require++)
        {
            int cnts[256] = { 0 };
            int collect = 0, satisfy = 0;
            for (int l = 0, r = 0; r < n; r++)
            {
                cnts[s[r]]++;
                if (cnts[s[r]] == 1)
                    collect++;
                if (cnts[s[r]] == k)
                    satisfy++;
                //种类超了
                while (collect > require)
                {
                    //--之前
                    if (cnts[s[l]] == 1)
                        collect--;
                    if (cnts[s[l]] == k)
                        satisfy--;
                    cnts[s[l]]--;
                    l++;
                }
                //种类没超,直接更新
                if (satisfy == require)
                    ans = max(ans, r - l + 1);
            }
        }
        return ans;
    }
};