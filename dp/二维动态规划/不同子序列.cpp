//https://leetcode.cn/problems/distinct-subsequences/
//dp[i][j]表示s[前缀长度为i ]的子序列匹配t[前缀长度为j ]子串的方法数
//考虑最后一个位置,s[i]位置可以不选择,就让s前i-1个去匹配t的前j个,即dp[i][j]=dp[i-1][j]
//也可以选择,那么只有在二者相等的时候才有意义,dp[i][j]=dp[i-1][j-1]
//以上两种情况都能得到结果,所以是相加的关系
//初始化: 考虑到依赖于i-1,在原始第一行会出现访问越界的情况,可以特殊处理,也可以
// 采取将第一行融入到整体计算中,就是多开一行多开一列
// 1. 注意新开位置的初始化: 第0行代表s为空时,那么""去生成子序列匹配t的方法数自然是0
//						 第0列代表t为空时,那么s生成的子序列匹配空的种树只有一种,就是空,所以第一列为1
// 2. 访问原字符串时要注意下标-1
//填表顺序:从左往右,从上往下
//返回值: dp[前缀长度为n][前缀长度为m]的匹配方法数

#include<iostream>
#include<vector>
using namespace std;
class Solution29
{
public:
	int numDistinct(string s, string t)
	{
		const int MOD = 1000000007;

		int n = s.size(), m = t.size();
		vector<vector<int>>dp(n + 1, vector<int>(m + 1));
		for (int i = 0; i <= n; i++)
			dp[i][0] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
				if (s[i - 1] == t[j - 1])
					dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
			}
		}
		return dp[n][m] % MOD;
	}
};
//空间压缩: 想如何将i行数据更新为i+1行数据,
//因为[i][j]格子依赖于上方和左上方的格子,一维数组中,[j]位置未更新就是代表上一行的值,
//要想直接获取左上方格子,避免他已经被更新覆盖,就需要从右往左去更新数组
class Solution30
{
public:
	int numDistinct(string s, string t)
	{
		const int MOD = 1000000007;
		int n = s.size(), m = t.size();
		vector<int>dp(m + 1);
		dp[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = m; j >= 1; j--)
			{
				if (s[i - 1] == t[j - 1])
					dp[j] = (dp[j] + dp[j - 1]) % MOD;
			}
		}
		return dp[m] % MOD;
	}
};