//https://leetcode.cn/problems/di-string-match/
//贪心: 如果是I,那么就将最小的值放在这里,如果是D降低,就将最大值放到这里
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
	vector<int> diStringMatch(string s)
	{
		int right = s.size(), left = 0;
		vector<int>ret;
		for (char ch : s)
		{
			if (ch == 'I')
				ret.push_back(left++);
			else
				ret.push_back(right--);
		}
		ret.push_back(left);
		return ret;
	}
};