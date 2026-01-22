//https://leetcode.cn/problems/paths-in-matrix-whose-sum-is-divisible-by-k/

// 当前来到(i,j)位置，最终一定要走到右下角(n-1,m-1)
// 从(i,j)出发，最终一定要走到右下角(n-1,m-1)，有多少条路径，累加和%k的余数是r
// 
//当前位置%k的值已知为mod1，需要整体下来%k的值为mod2,那么如何推导出后续路径和%k之后应该是多少？ mod0
// mod0 = (k+mod2-mod1)%k

#include<iostream>
#include<vector>
using namespace std;
class Solution11
{
	const int MOD = 1e9 + 7;
	int n, m, k;
	vector<vector<vector<int>>>memo;
public:
	int numberOfPaths(vector<vector<int>>& grid, int k1)
	{
		n = grid.size();
		m = grid[0].size();
		k = k1;
		memo = vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(k, -1)));
		return dfs(grid, 0, 0, 0);
	}
	int dfs(vector<vector<int>>& grid, int i, int j, int r)
	{
		if (i == n - 1 && j == m - 1)
			return grid[i][j] % k == r ? 1 : 0;
		if (memo[i][j][r] != -1)
			return memo[i][j][r];
		int need = (k + r - (grid[i][j] % k)) % k;
		int ans = 0;
		if (i + 1 < n)//还能往右走
			ans = dfs(grid, i + 1, j, need);
		if (j + 1 < m)//还能往下走
			ans = (ans + dfs(grid, i, j + 1, need)) % MOD;
		memo[i][j][r] = ans;
		return ans;
	}
};
//以i,j构建一个二维表，然后每个格子有一个向上的高度，类似于住进楼房，那就是k，k因为是取模得到，所以高度范围就是0~k
//初始化自然是最右下角的值，如果h=grid[n][m]%k h位置的楼房格子填上1，其他都是0,那么dp值就得到确定。
//i,j位置依赖于下方，或者右方的高度数组中的所有值。
//所以只需要将最下方，和最右方的两行数据更新，然后再往左上推导
//返回值就是0,0位置楼房中0的格子的值
class Solution11
{
	const int MOD = 1e9 + 7;
public:
	int numberOfPaths(vector<vector<int>>& grid, int k)
	{
		int n = grid.size();
		int m = grid[0].size();
		vector<vector<vector<int>>>dp(n, vector<vector<int>>(m, vector<int>(k, 0)));
		dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;
		for (int i = n - 2; i >= 0; i--)
		{
			for (int r = 0; r < k; r++)
				dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
		}
		for (int j = m - 2; j >= 0; j--)
		{
			for (int r = 0; r < k; r++)
				dp[n - 1][j][r] = dp[n - 1][j + 1][(k + r - grid[n - 1][j] % k) % k];
		}
		int need = 0;
		for (int i = n - 2; i >= 0; i--)
		{
			for (int j = m - 2; j >= 0; j--)
			{
				for (int r = 0; r < k; r++)
				{
					need = (k + r - grid[i][j] % k) % k;
					dp[i][j][r] = dp[i + 1][j][need];
					dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % MOD;
				}
			}
		}
		return dp[0][0][0];
	}
};