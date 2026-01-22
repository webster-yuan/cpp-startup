//计算等位时间给定一个数组arr长度为n，表示n个服务员，arr[i]表示i位置服务员服务一个客人消耗的时间
// 给定一个正数m，表示有m个人等位，
// 如果你是刚来的人，每个客人遵循有空位就上的原则请问你需要等多久 ? 
//假设m远远大于n，比如n <= 10^3，m <= 10^9，该怎么做是最优解 ? 谷歌的面试
//
//经分析: 无论怎么选择空闲服务员,只要是遵循有空位就上的原则,被安排的时间就是确定的,只不过可能是不同的服务员.
//解法一:使用小根堆,<服务员就绪时间,服务员工作时间>
//每次弹出栈顶,累加就绪时间...
//一共弹m次,每次是logn,所以T=m*logn.数据量是10^9,当m很大时就会超时

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution
{
public:
	class waiter
	{
	public:
		int ready;
		int cost;
		waiter(int r, int c)
			:ready(r)
			, cost(c)
		{}
	};
	struct greater
	{
		bool operator()(const waiter& w1, const waiter& w2)
		{
			return w1.ready > w2.ready;
		}
	};
	int waitTime(vector<int>& waiters, int m)
	{
		priority_queue<waiter, vector<waiter>, greater>heap;
		int n = waiters.size();
		for (int i = 0; i < n; i++)
			heap.push(waiter(0,waiters[i]));
		for (int i = 0; i < m; i++)
		{
			waiter top = heap.top();
			heap.pop();
			top.ready += top.cost;
			heap.push(top);
		}
		return heap.top().ready;
	}
};


//解法二:
//等待时间时有范围的,[0,minWaiter*m],因为也知道遵循有空位就上的原则,
//提供func函数,规定所有员工都工作mid小时,能够给多少客人提供服务
//自然工作时间越长,能够提供服务也就越多,单调性.
//自己是第m+1个人 
class Solution
{
public:
	public:
	int waitTime(vector<int>& waiters, int m)
	{
		int minVal = INT_MAX;
		for (int i = 0; i < waiters.size(); i++)
			minVal = min(minVal, waiters[i]);
		int l = 0, r = minVal * m;
		int ans = 0;
		while (l <= r)
		{
			int mid = l + ((r - l) >> 1);
			if (func(waiters, mid) >= m + 1)
			{
				ans = mid;
				r = mid - 1;
			}
			else
				l = mid + 1;
		}
		return ans;
	}
	int func(vector<int>& nums, int time)
	{
		int ans = 0;
		for (int x : nums)
		{
			ans += (time/x) + 1;//当到time时仍有人在服务但是没有完成,也算!!
		}
		return ans;
	}
};