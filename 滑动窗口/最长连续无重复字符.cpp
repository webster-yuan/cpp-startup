//滑动窗口: 单调性存在于只要r++,那么长度肯定是变长的,在不满足重复时缩小范围.
// 以每一个位置为结尾求解答案
//记录每一种字符上次出现的位置last[256]=-1
//左边界限制是max(last[[i]]+1,此时窗口左边界)
//时刻更新last[x]x字符上一次出现的位置
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int lengthOfLongestSubstring(string str)
    {
        int n = str.size();
        vector<int>last(256,-1);
        int ans = 0;
        for (int l = 0, r = 0; r < n; r++)
        {
            l = max(last[str[r]] + 1, l);
            ans = max(ans, r - l + 1);
            last[str[r]] = r;
        }
        return ans;
    }
};