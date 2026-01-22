// 删除至少几个字符可以变成另一个字符串的子串
// 给定两个字符串s1和s2
// 返回s1至少删除多少字符可以成为s2的子串
//https://www.bilibili.com/video/BV1cg4y1o719?t=4921.2
//dp[i][j]表示s1前i个字符串变成s2前j个的字符的任意后缀串,需要删除的个数
// S1[0...i-1] s2[0...j-1],s1的第i个字符和s2的第j个字符,
// 1. s1[i-1]!=s2[j-1], dp[i][j]=dp[i-1][j] +1 把i位置删了一个
// 2. s1[i-1]==s2[j-1], dp[i][j]=dp[i-1][j-1]
//返回值选择最后一行中最小删除个数即可
#include<iostream>
#include<vector>
using namespace std;
class Solution36
{
public:
	int minDel(string& s1, string& s2)
	{
		int n = s1.size(), m = s2.size();
		vector<vector<int>>dp(n + 1, vector<int>(m + 1));
		for (int i = 0; i <= n; i++)
			dp[i][0] = i;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (s1[i - 1] == s2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = dp[i - 1][j] + 1;
				}
			}
		}
		int ans = INT_MAX;
		for (int i = 0; i <= m; i++)
			ans = min(ans, dp[n][i]);
		return ans;
	}
};