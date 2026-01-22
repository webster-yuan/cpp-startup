//https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea
//小强现在有n个节点, 他想请你帮他计算出有多少种不同的二叉树满足节点个数为n且树的高度不超过m的方案
//因为答案很大，所以答案需要模上1000000007后输出.

//https://www.bilibili.com/video/BV1WQ4y1W7d1?t=8590.7
#include<iostream>
#include<vector>
using namespace std;
class Solution11
{
	vector<vector<int>>memo;
	const int MOD = 1000000007;
public :
	int getNum(int n, int m)
	{
		memo = vector<vector<int>>(n, vector<int>(m, -1));
		return compute(n,m);
	}
	//当节点数是n时,返回层数小于等于m的方法数有多少
	int compute(int n, int m)
	{
		if (n == 0)
			return 1;//0个节点,高度<=m的方法数有一种
		if (m == 0)
			return 0;//有节点,但是堆不出来一种能够层数=0的方法
		if (memo[n][m] == -1)
			return memo[n][m];
		long long ans = 0;
		//枚举左子树能够分多少个节点去查找方案数,0~n-1,因为根节点肯定要占据一个
		for (int k = 0; k < n; k++)
		{
			ans = (ans + ((long long)compute(k, m - 1) *compute(n - k - 1, m - 1)) % MOD) % MOD;
		}
		memo[n][m] = ans;
		return (int)ans;
	}
};
//分析严格位置依赖关系: 
//只依赖m-1列的,并且0~i行的格子,这一批格子
//填表顺序就是从左往右,从上往下
//初始化,0行所有格子都是1
class Solution12
{
	const int MOD = 1000000007;
public:
	int getNum(int n, int m)
	{
		vector<vector<long long>>dp(n+1, vector<long long>(m+1));
		for (int j = 0; j <= m; j++)
			dp[0][j] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				dp[i][j] = 0;
				for (int k = 0; k < i; k++)
					dp[i][j] = (dp[i][j] + dp[k][j - 1] * dp[i - k - 1][j - 1] % MOD) % MOD;
			}
		}
		return dp[n][m];
	}
};
//递推的数组是一列一列数组往后递推更新
//https://www.bilibili.com/video/BV1WQ4y1W7d1?t=9647.9
//那么就需要从下往上更新,更新dp[i][j]位置时,前一列中[0,j-1]的所有数字还没更新,也就可以直接获取
//从左往右,从下往上即可
class Solution12
{
	const int MOD = 1000000007;
public:
	int getNum(int n, int m)
	{
		vector<long long >dp(n+1);
		dp[0] = 1;//第0列,初始化为1
		for (int j = 1; j <= m; j++)//按照列,一列一列更新
		{
			for (int i = n; i >= 1; i--)
			{
				dp[i] = 0;
				for (int k = 0; k < i; k++)
				{
					dp[i] = (dp[i] + dp[k] * dp[i - k - 1] % MOD) % MOD;
				}
			}
		}
		return (int)dp[n];
	}
};