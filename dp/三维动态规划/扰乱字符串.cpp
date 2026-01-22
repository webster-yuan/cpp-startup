//https://leetcode.cn/problems/scramble-string/
#include<iostream>
#include<vector>
using namespace std;
//https://www.bilibili.com/video/BV1gM41197rM?t=5540.6
//区间dp讨论：
//分为两种，交错还是不交错，既然是扰乱串，所以长度都应该是相同的
//1. 不交错的： isTrue(s1[0,i],s2[0,i]) && isTrue(s1[i+1,n-1],s2[i+1,n-1])
//2. 交错的： isTrue(s1[0,i],s2[n-i,n]) && isTrue(s1[i+1,n],s2[0,n-i-1])
class Solution
{
public:
	bool isScramble(string s1, string s2)
	{
		int n = s1.size();
		return func1(s1, s2, 0, n - 1, 0, n - 1);
	}
	// 是不是扰乱串的关系
	bool func1(string& s1, string& s2, int l1, int r1, int l2, int r2)
	{
		//只剩下最后一个字符，只需要判断是否相等即可
		if (l1 == r1)
			return s1[l1] == s2[l2];
		//不交错
		// s1[l1..i][i+1....r1]
		// s2[l2..j][j+1....r2]
		for (int i = l1, j = l2; i < r1; ++i, j++)
		{
			if (func1(s1, s2, l1, i, l2, j) && func1(s1, s2, i + 1, r1, j + 1, r2))
				return true;
		}
		//交错
		// s1[l1..........i][i+1...r1]
		// s2[l2...j-1][j..........r2]
		for (int i = l1, j = r2; i < r1; j--, i++)
		{
			if (func1(s1, s2, l1, i, j, r2) && func1(s1, s2, i + 1, r1, l2, j - 1))
				return true;
		}
		return false;
	}
};
//四个可变参数，引入长度相同len,所以只要l1,l2,len就可
//0 表示没展开过
//1 true
//-1 false
class Solution21
{
	vector<vector<vector<int>>> memo;
public:
	bool isScramble(string s1, string s2)
	{
		int n = s1.size();
		memo = vector<vector<vector<int>>>(n,vector<vector<int>>(n,vector<int>(n+1)));
		return func(s1, s2, 0, 0, n);
	}
	bool func(string& s1, string& s2, int l1, int l2, int len)
	{
		if (len == 1)
			return s1[l1] == s2[l2];
		if (memo[l1][l2][len] != 0)
			return memo[l1][l2][len]==1;
		bool ans = false;
		//s1左侧k个匹配s2左侧k个-》不交错
		for (int k = 1; k < len; k++)
		{
			if (func(s1, s2, l1, l2, k) && func(s1, s2, l1 + k, l2 + k, len - k))
			{
				ans = true;
				break;
			}
		}
		//交错
		if (ans == false)
		{
			for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
			{
				if (func(s1, s2, l1, j, k) && func(s1, s2, i, l2, len - k))
				{
					ans = true;
					break;
				}
			}
		}
		memo[l1][l2][len] = ans?1:-1;
		return ans;
	}
	bool _func(string& s1, string& s2, int l1, int l2, int len)
	{
		if (len == 1)
			return s1[l1] == s2[l2];

		//s1左侧k个匹配s2左侧k个-》不交错
		for (int k = 1; k < len; k++)
		{
			if (_func(s1, s2, l1, l2, k) && _func(s1, s2, l1 + k, l2 + k, len - k))
				return true;
		}
		//交错
		for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
		{
			if (_func(s1, s2, l1, j, k) && _func(s1, s2, i, l2, len - k))
				return true;
		}
		return false;
	}
};

//https://www.bilibili.com/video/BV1gM41197rM?t=6598.4
//同样将l1,l2为二维表，然后len作为高度层理解，而且len依赖于len-k,所以代表将
//低层填好了之后，自然就可以填写高层
//初始化： 填写第一层
//每个格子都需要进行枚举，所以O(N^4)

class Solution22
{
public:
	bool isScramble(string s1, string s2)
	{
		int n = s1.size();
		vector<vector<vector<bool>>> dp(n,vector<vector<bool>>(n,vector<bool>(n+1)));
		for (int l1 = 0; l1 < n; l1++)
		{
			for (int l2 = 0; l2 < n; l2++)
				dp[l1][l2][1] = s1[l1] == s2[l2];
		}
		for (int len = 2; len <= n; len++)
		{
			for (int l1 = 0; l1 <= n - len; l1++)//在递归过程中那些格子不会被遍历到，所以没有填写的意义
			{
				for (int l2 = 0; l2 <= n - len; l2++)
				{
					for (int k = 1; k < len; k++)
					{
						if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k])
						{
							dp[l1][l2][len] = true;
							break;
						}
					}
					if (!dp[l1][l2][len])
					{
						for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
						{
							if (dp[l1][j][k] && dp[i][l2][len - k]) 
							{
								dp[l1][l2][len] = true;
								break;
							}
						}
					}
				}
			}
		}
		return dp[0][0][n];
	}
};