//给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。
//需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
//https://leetcode.cn/problems/remove-duplicate-letters/description/

//当考虑index位置字符是否删除时,应该考虑后面还有几个这个字符,如果还有,那么我放心删除,
//如果没有了,只能硬着头皮放他,所以考虑到词频统计.
//保证字典序最小,所以应该是大压小,最后将栈中弹出元素逆序即可
//所以维护时,大压小+字符词频 统一考虑
//当重复字符出现时,看看栈中是否已经存在,如果没有就压入,如果有了就直接跳过.
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        int N = 26;
        vector<int>cnts(N);
        vector<bool>visi(N, false);
        vector<char>st(N);
        //词频统计
        for (char ch : s)
            cnts[ch - 'a']++;
        int r = 0;
        for (char ch:s)
        {
            if (!visi[ch - 'a'])//栈中没有这个字符
            {
                while (r > 0 && st[r - 1] > ch && cnts[st[r-1] - 'a'])
                {
                    visi[st[r - 1] - 'a'] = false;
                    r--;
                }
                st[r++] = ch;
                visi[ch - 'a'] = true;
            }
            cnts[ch - 'a']--;
        }
        string ret = "";
        for (int i = 0; i < r; i++)
            ret += st[i];
        return ret;
    }
};