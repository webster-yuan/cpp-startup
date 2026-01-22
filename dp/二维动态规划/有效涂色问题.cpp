// 有效涂色问题https://www.bilibili.com/video/BV1cg4y1o719?t=4042.9
// 给定n、m两个参数
// 一共有n个格子，每个格子可以涂上一种颜色，颜色在m种里选
// 当涂满n个格子，并且m种颜色都使用了，叫一种有效方法
// 求一共有多少种有效的涂色方法
// 1 <= n, m <= 5000
// 结果比较大请 % 1000000007 之后返回
// 对数器验证

//dp[i][j]代表前i个格子已经凑够了j中颜色的有效方法数
// 以i这个格子涂色为准,考虑之前的操作
//1. 前i-1个格子已经凑够了j种颜色,那么i位置只需要在m中颜色中任意选择一种涂色即可,dp[i][j]=dp[i-1][j] *m
//2. 前i-1个格子已经凑够了j-1种颜色那么i位置只需要在剩下的m-(j-1)种颜色中选择一个涂上,
//   dp[i][j]=dp[i-1][j-1] * (m-j+1)
//也就是在i位置,可以选择之前的颜色,可以选择剩下的颜色涂上

//https://www.bilibili.com/video/BV1cg4y1o719?t=4402.9 初始化

#include<iostream>
#include<vector>
using namespace std;
class Solution34
{
public:
	int getWays(int n, int m)
	{
		const int MOD = 1000000007;
		vector<vector<int>>dp(n + 1, vector<int>(m + 1));
		for (int i = 1; i <= n; i++)
			dp[i][1] = m;//i个格子只涂上一种颜色,能够有m种选择
		for (int i = 1; i <= n; i++)
		{
			for (int j = 2; j <= m; j++)
			{
				dp[i][j] = (int)((long long)dp[i - 1][j] * j) % MOD;
				dp[i][j] = (int)(((long long)dp[i - 1][j - 1] * (m - j - 1)) + dp[i][j]) % MOD;
			}
		}
		return dp[n][m];
	}
};

