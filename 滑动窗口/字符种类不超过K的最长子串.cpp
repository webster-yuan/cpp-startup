
//窗口: 范围变大了含有的字符种类只可能变大,存在这种单调性,所以可以用滑动窗口
//使用哈希表统计字符个数和词频

#include<iostream>
#include<unordered_map>
using namespace std;
class Solution
{
public:
	int lengthOfLongestSubstringKDistinct(string s, int k)
	{
		if (s.size() == 0 || k < 1)return 0;

		int l = 0, r = 0;
		unordered_map<char, int>hashMap;
		int ans = 1;
		while (r < s.size())
		{
			if (hashMap.size() <= k)
			{
				hashMap[s[r]]++;
				r++;
			}
			else//此时r在正好字符种类> k位置,
			{
				int len = r - l;
				ans = max(ans, len);
				//出左窗口直到字符种类<=k,
				while (hashMap.size() > k)
					hashMap[s[l++]]--;
				r++;
			}
		}
		return ans;
	}
};