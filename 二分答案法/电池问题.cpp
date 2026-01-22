//https://leetcode.cn/problems/maximum-running-time-of-n-computers/description/
// 请返回n台电脑同时运行的最长分钟数
//https://www.bilibili.com/video/BV1Mh4y1P7qE?t=5804.8
//关键结论:
// 给定电池电量数组,当数组中都是碎片电池时,当数组的累加和>=电脑数量*要求时间时,一定能够完成供电
//碎片电池: 电池的电量<要求时间
//如果数组中有大于要求时间的电量的电池,最不亏的方式就是让他单一负责一台电脑即可.
//
//N台电脑共同运行的分钟数是有范围的,[0,电池数组累加和]当只有一台电脑时,所有电池都给他供电
//单调性: 要求的时间越长,那么需要的电池也就越多
//func函数,提供在要求时间mid时,看是否能够让所有电脑运行


#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution11
{
public:
	//O(n*log(sum))
	long long maxRunTime(int n, vector<int>& nums)
	{
		long long sum = 0;
		for (int x : nums)
			sum += x;
		long long l = 0, r = sum;
		long long ans = 0;
		while (l <= r)
		{
			long long  mid = l + ((r - l) >> 1);
			if (func(mid, n, nums))
			{
				ans = mid;
				l = mid + 1;
			}
			else
				r = mid - 1;
		}
		return ans;
	}
	bool func(long long limit, int n, vector<int>& nums)
	{
		long long sum = 0;//碎片电池电量的总和
		for (int x : nums)
		{
			if (x > limit)
				n--;
			else
				sum += x;
			if (sum >= limit * n)
				return true;
		}
		return false;
	}
};

//https://www.bilibili.com/video/BV1Mh4y1P7qE?t=6538.0
// 贪心优化: beat 100%
			// 所有电池的最大电量是max
			// 如果此时sum > (long) max * num，
			// 说明 : 最终的供电时间一定在 >= max，而如果最终的供电时间 >= max
			// 说明 : 对于最终的答案X来说，所有电池都是讲的"碎片拼接"的概念
			// 那么寻找 ? * num <= sum 的情况中，尽量大的 ? 即可
			// 即sum / num
//否则,所有电脑的供电时间一定<max,时间范围就可以进一步缩小,[0,max],所有的数据类型就可以缩小为int
//相比于longlong提升效率

class Solution
{
public:
	//O(n*log(sum))
	long long maxRunTime(int n, vector<int>& nums)
	{
		long long sum = 0;
		int maxVal = 0;
		for (int x : nums)
		{
			sum += x;
			maxVal = max(maxVal, x);
		}
		if (sum > (long long )maxVal * n)
			return sum / n;
		int l = 0, r = maxVal;
		int ans = 0;
		while (l <= r)
		{
			int mid = l + ((r - l) >> 1);
			if (func(mid, n, nums))
			{
				ans = mid;
				l = mid + 1;
			}
			else
				r = mid - 1;
		}
		return ans;
	}
	bool func(int limit, int n, vector<int>& nums)
	{
		long long  sum = 0;//碎片电池电量的总和
		for (int x : nums)
		{
			if (x > limit)
				n--;
			else
				sum += x;
			if (sum >= (long long)limit * n)
				return true;
		}
		return false;
	}
};
