#include<iostream>
#include<vector>
using namespace std;

//dp[i][j]表示在[1,i]号物品中挑选,在体积不大于j时能够获得的最大价值即dp[n][v]
//以i号位置为结尾考虑问题,
//1. 不选择i号物品,dp[i][j]=dp[i-1][j] 2. 选择i号物品,dp[i][j]=dp[i-1][j-costs[i]]+vals[i]
//dp(n+1,vector<int>(v+1));
// 初始化: i=0,也就是第0行,代表没有物品可以选择时,体积不超过j时能够获取的最大利润自然是0
//       j=0,在第0列,代表选择[1...i]物品,但是体积不超过0时,能够获取的最大利润自然是不选,为0
//costs数组对应的也是做了[1,i]位置的处理,[0]位置不放东西,所以不用注意访问原数组时下标-1处理

//空间压缩,因为需要依赖上一行左侧的值,所以为了更新时避免覆盖,所以将顺序改为从右往左更新

class Solution
{
public:
	int getMaxVal(int n,int limitV,vector<int>& costs, vector<int>& vals)
	{
		vector<vector<int>>dp(n + 1, vector<int>(limitV + 1));
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= limitV; j++)
			{
				dp[i][j] = dp[i - 1][j];
				if (j >= costs[i])
					dp[i][j] = max(dp[i][j], dp[i - 1][j - costs[i]] + vals[i]);
			}
		}
		return dp[n][limitV];
	}
	int getMaxVal1(int n, int limitV, vector<int>& costs, vector<int>& vals)
	{
		vector<int>dp(limitV);
		for (int i = 1; i <= n; i++)
		{
			//当j<costs[i]时代表第二种情况不存在,不用更新,也就是直接等于上一行的值即可
			//上一行的值就是此时的dp[j],不更新即可
			for (int j = limitV; j >= costs[i]; j--)
			{
				dp[j] = max(dp[j], dp[j - costs[i]] + vals[i]);
			}
		}
		return dp[limitV];
	}
};