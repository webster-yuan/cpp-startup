//https://leetcode.cn/problems/tJau2o/description/
//costs[i]=ai-bi
//vals[i]=wi
//最终买游戏的钱可以超过预算,只需要总优惠价格不低于超过预算的总金额
//也就是每每决定要买一个游戏时,i号游戏,costs[i] > bi即可
//通过这一条件筛选出必须要选择的游戏,因为买了这个游戏对咱们还有好处,可以让我们有更大的优惠
//买更多地游戏,所以必买.
//然后再在剩下的游戏中选择若干游戏买,直到不满足条件.
//那么剩下的游戏可以得到新的数组nums[],得到对应的costs[i]和happys[i]
//在这三个数组中进行01背包问题的讨论即可
//输出的是能够获得的最大的快乐值

//dp[i][j]表示在1~i号商品中选择,预算不超过j时能够获得的最大快乐值
//i~[1,k]因为只需要在不能直接选择的游戏中选择,之前记录了一共是k个
//j~[1,x]因为必须选择的游戏会给我带来更大的预算,x是在随时变化的,记录之后是x

#include<iostream>
#include<vector>
using namespace std;
long long compute(vector<long long>& costs, vector<long long>& vals, int k, int x)
{
	vector<long long>dp(x + 1);
	for (int i = 1; i < k; i++)//注意k这里并不是<=像其他01背包一样.我们约定的costs[k]位置添加新元素,所以元素只有k-1个
	{
		for (int j = x; j >= costs[i]; j--)
		{
			dp[j] = max(dp[j], dp[j - costs[i]] + vals[i]);
		}
	}
	return dp[x];
}

int main()
{
	int n = 0, x = 0;
	while (cin >> n >> x)
	{
		vector<long long >costs(n + 1);
		vector<long long >happys(n + 1);
		long long  ans = 0;
		int k = 1;//记录一共有多少个不是必须选择的游戏
		long long happy = 0;
		for (int i = 1, a = 0, b = 0; i <= n; i++)//保证下标满足01背包从1开始
		{
			cin >> a >> b >> happy;
			int well = a - b - b;
			if (well >= 0)
			{
				x += well;
				ans += happy;
			}
			else//只有不是必须选的,才放到数组中寻求一种最佳的选择,得到在条件之内的最大快乐值
			{
				costs[k] = -well;
				happys[k++] = happy;
			}
		}

		ans += compute(costs, happys, k, x);
		cout << ans << endl;
	}
}
