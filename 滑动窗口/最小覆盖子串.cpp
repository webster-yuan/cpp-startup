//https://leetcode.cn/problems/minimum-window-substring/description/?utm_source=LCUS&utm_medium=ip_redirect&utm_campaign=transfer2china
//求解子数组在每个位置开头或者结尾时的答案
//滑动窗口的关键: 查找范围和答案指标之间的单调性关系
//单调性: 范围越大,越容易包含t子串.s的区间范围,右区间越扩大,越容易找到答案,左区间越往右,越不容易找到答案.
// 
//返回S中包含t字符串的最少覆盖子串.t在S中字符出现的顺序是随机的,但是得都有.
//在过程中记录开头和长度,最后截取返回即可.
//也是滑动窗口,只不过如何判定让l++,
//因为忽略顺序,所以只需要有固定字符的那么多个就行.
//使用第三方数组,tmp记录每个字符应该出现的个数,作为欠债表,debt记录负数总个数即总债
//然后在窗口中"还债"
//[i]以i位置为结尾往前最小的还债窗口,当债务清0时,尝试在不欠债的情况下缩小左边界,left++
//记录长度和起始位置
//在遍历s过程中,肯定会出现t中没有的,那么就将债务表中他出现的次数++,肯定是正数,在缩小左边界时>0代表可以吐出
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    string minWindow(string s, string t)
    {
        if (s.size() < t.size())
            return "";
        int tmp[256] = {0};
        for (auto e : t)
            tmp[e]--;

        int len = INT_MAX;//记录最小覆盖子串
        int start = 0;
        int debt = t.size();
        for (int l = 0, r = 0; r < s.size(); r++)
        {
            if (tmp[s[r]]++ < 0)
                debt--; 
            if (debt == 0)
            {
                //尝试尽量缩小左边界
                while (tmp[s[l]] > 0)
                    tmp[s[l++]]--;
                if (r - l + 1 < len)
                {
                    len = r - l + 1;
                    start = l;
                }
            }
        }
        return len == INT_MAX ? "" : s.substr(start, len);
    }
};
