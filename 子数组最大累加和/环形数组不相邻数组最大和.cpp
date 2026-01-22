
// https://leetcode.cn/problems/house-robber-ii/submissions/455290787/
//打家劫舍II

//因为是环形数组,考虑0位置数字选还是不选
//[0]位置数字不选,那么环形不复存在,就是在[1,n-1]区间进行不相邻数组最大累加和求解 (打家劫舍I)
//[0]位置数组选择,那么[1],[n-1]位置不能选,在[2,n-2]区间进行打家劫舍I即可
//二者最大值即可
//下面是采用两个状态记录的方式求解
#include<iostream>
#include<vector>
using namespace std;
class Solution31
{
public:
	int rob(vector<int>& nums)
	{
		int n = nums.size();
		return max(nums[0] + rob1(nums, 2, n - 2), rob1(nums, 1, n - 1));
	}
	int rob1(vector<int>& nums, int left, int right)
	{
		if (left > right)return 0;//没有房屋没抢到
		int n = nums.size();
		//dp[i]代表抢到某个房屋之后的钱数
		vector<int>f(n);//偷
		vector<int>g(n);//不偷
		f[left] = nums[left], g[left] = 0;
		for (int i = left; i <= right; i++)
		{
			f[i] = g[i - 1] + nums[i];
			g[i] = max(f[i - 1], g[i - 1]);
		}
		return max(f[right], g[right]);
	}
};

class Solution32
{
public:
	int rob(vector<int>& nums)
	{
		int n = nums.size();
		if (n == 1)
			return nums[0];
		return max(nums[0] + rob1(nums, 2, n - 2), rob1(nums, 1, n - 1));
	}
	int rob1(vector<int>& nums, int l, int r)
	{
		if (l > r)
			return 0;
		if (l == r)
			return nums[l];
		if (l + 1 == r)
			return max(nums[l], nums[r]);

		int pprev = nums[l];
		int prev = max(nums[l], nums[l + 1]);
		for (int i = l + 2; i <= r; i++)
		{
			int cur = max(pprev + nums[i], prev);
			pprev = prev;
			prev = cur;
		}
		return prev;
	}
};