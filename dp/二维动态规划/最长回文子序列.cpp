//https://leetcode.cn/problems/longest-palindromic-subsequence/

//解法一: str和他的的逆序串rstr的最长公共子序列,就是str的最长回文子序列
//解法二: 区间dp问题
//以i位置为结尾,dp[i]表示所有子序列中最长的回文子序列的长度.
//因为是子序列,那么第i-1个字符可能是[0,i-1]上的任意一个,选中j位置作为倒数第二个位置将[i]字符贴到后面,
// 想的是dp[i]=dp[j]+1但是无法判断此时是否是回文串.所以这种表示不行.
//dp[i][j]表示[i,j]区间内的所有子序列中最长的回文子序列的长度
//1. s[i]==s[j],
// 1.1 i==j =>是只有一个字符,1 
// 1.2 i+1=j =>是两个相邻字符2 
// 1.3 i+1<j dp[i+1][j-1]+2(就是边界这俩字符) 
//  1.2 1.3合并,在填表时访问i+1 j 0+2 就等于2
// 
//2. s[i]!=s[j],
// 1.1 dp[i][j-1] 
// 1.2 dp[i+1][j] 分别在两个区间找找最大回文长度,选出最大值即可,
//   dp[i][j]=max(dp[i+1][j],dp[i][j-1])
//初始化: 二维表中i=j位置已经填过了
//填表顺序:  从下往上,从左往右
//返回值: dp[0][n-1]


#include<iostream>
#include<vector>
using namespace std;
class Solution7
{
public:
	int longestPalindromeSubseq(string s)
	{
		int n = s.size();
		vector<vector<int>>dp(n, vector<int>(n, 0));
		for (int i = n - 1; i >= 0; i--)
		{
			dp[i][i] = 1;//i==j,并且因为是区间,所以j>i开始的
			for (int j = i + 1; j < n; j++)
			{
				if (s[i] == s[j])
					dp[i][j] = dp[i+1][j-1] + 2;
				else
					dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
			}
		}
		return dp[0][n - 1];
	}
};
//https://www.bilibili.com/video/BV1WQ4y1W7d1?t=7021.8

//记忆化搜索: 区间dp中l<=r,所以只需要填写一半的表就行,其他位置是无意义的.
class Solution8
{
	vector<vector<int>>memo;
public:
	int longestPalindromeSubseq(string s)
	{
		int n = s.size();
		memo = vector<vector<int>>(n, vector<int>(n));
		return dfs(s, 0, n - 1);
	}
	int dfs(string& s, int l, int r)
	{
		if (l == r)
			return 1;
		if (l + 1 == r)
			return s[l] == s[r] ? 2 : 1;
		if (memo[l][r] != 0)
			return memo[l][r];
		int ans = 0;

		if (s[l] == s[r])
			ans = dfs(s, l + 1, r - 1) + 2;
		else
			ans = max(dfs(s, l + 1, r), dfs(s, l, r - 1));
		memo[l][r] = ans;
		return ans;
	}
};
//分析严格位置依赖,依赖于左下角,下,左的格子
//所以是从下往上,从左往右
//https://www.bilibili.com/video/BV1WQ4y1W7d1?t=7551.4
//返回值是最右上角的格子
class Solution9
{
public:
	int longestPalindromeSubseq(string s)
	{
		int n = s.size();
		vector<vector<int>>dp(n, vector<int>(n, 0));
		for (int i = n - 1; i >= 0; i--)
		{
			//二维表中,每一行,先完成两个特殊格子,
			dp[i][i] = 1;
			if (i + 1 < n)
				dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
			//然后再填
			for (int j = i + 2; j < n; j++)
			{
				if (s[i] == s[j])
					dp[i][j] = dp[i+1][j-1] + 2;
				else
					dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
			}
		}
		return dp[0][n - 1];
	}
};
//https://www.bilibili.com/video/BV1WQ4y1W7d1?t=8011.2
//空间优化,将二维数组优化为一维数组,从下往上更新数组,
//更新dp[j]位置时,需要dp[j-1](已更新),dp[j](待更新,下面的值),左下角的值(leftdown)

class Solution10
{
public:
	int longestPalindromeSubseq(string s)
	{
		int n = s.size();
		vector<int>dp(n);
		int leftdown = 0, backup = 0;
		for (int l = n - 1; l >= 0; l--)
		{
			dp[l] = 1;//对角线位置
			if (l + 1 < n)
			{
				leftdown = dp[l + 1];
				dp[l + 1] = s[l] == s[l + 1] ? 2 : 1;
			}
			for (int r = l + 2; r < n; r++)
			{
				backup = dp[r];
				if (s[l] == s[r])
					dp[r] = 2 + leftdown;
				else
					dp[r] = max(dp[r - 1], dp[r]);
				leftdown = backup;
			}
		}
		return dp[n-1];
	}
};