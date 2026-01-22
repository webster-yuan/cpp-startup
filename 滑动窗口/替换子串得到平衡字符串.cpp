//https://leetcode.cn/problems/replace-the-substring-for-balanced-string/description/
//范围单调性分析:
//如果在[l,r]区间上能够通过更改达到平衡,那么在[left,right]更大的区间上肯定也能通过修改达到平衡
//给定ok函数[l,r]范围,返回能否在这个范围上让字符串平衡
//如果在[l,r]上可以平衡,那么长度minLen=r-l+1.那么[l,r+1,r+2]肯定也能做到,所以后续没有必要进行了
//此时l++,再进行判断.为什么r可以不用回退? 因为在[l,r]区间这么大的区间才能达成第一个,那么更小的区间肯定不能做到.
//所以r没有回退的必要,直接试试[l+1,r]能不能行
// 
//OK函数如何设计?
//只能修改[l,r]范围内的字符,假设长度为len,那么要求每种字符出现的次数是len/4,
//如果在[l,r]区间之外的所有位置上发现有的字符出现次数>len/4,那么说明只修改[l,r]范围内字符是做不到的
//[l,r]区间能够修改的个数是x=r-l+1,我们想要通过修改[l ,r]区间内的字符,让每种词频都是require = len/4,
//在[l,r]区间中,每种字符缺多少到达len/4,就在区间中补多少,四种字符需要的累加在一起sum,
//if sum==x说明能够修改成功,用[l,r]这个自由支配的长度去补每种字符缺多少到达平均值.
//
//窗口设计为[l,r)
//目前窗口长度太小做不到,但是还有努力的空间,就往右扩充.
//cnts统计的是[l,r)区间之外的词频,在l=0,r=0即窗口没有时,就是整体的词频统计
//在l++过程中,因为cnts统计的是[l,r]之外的词频,所以l++之前要让cnts统计到l为止,所以cnts[str[l]]++
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    //Q W E R
    //0 1 2 3 完成转换arr,arr[i]代表的就是词频
    int balancedString(string s)
    {
        vector<int>arr(s.size());
        vector<int>cnts(4,0);
        int i = 0;
        for (int j=0;j<s.size();j++)
        {
            if (s[j] == 'Q') i = 0;
            else if (s[j] == 'W') i = 1;
            else if (s[j] == 'E')i = 2;
            else i = 3;
            arr[j] = i;
            cnts[arr[j]]++;
        }
        int n = s.size();
        int require = n / 4;
        int ans = n;//最差的修改区间长度就是整个呗,都修改一遍
        for (int l = 0, r = 0; l < n; l++)
        {
            while (!ok(cnts, r - l, require) && r < n)
                cnts[arr[r]]--,r++;
            if (ok(cnts, r - l, require))
                ans = min(ans, r - l);
            cnts[arr[l]]++;
        }
        return ans;
    }
    bool ok(vector<int>& cnts, int len, int require)
    {
        for (int i = 0; i < 4; i++)
        {
            if (cnts[i] > require)
                return false;
            len -= require - cnts[i];
        }
        return len == 0;
    }
};