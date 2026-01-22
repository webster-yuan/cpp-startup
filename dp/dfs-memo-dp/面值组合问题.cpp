#include<iostream>
#include<vector>
using namespace std;

class Coins1 // 每一种面值的钱有无数张,只要是组成aim值的均可,有多少种组合能够组成aim
{
public:
	int minMoney(vector<int>& arr, int aim)
	{
		return process(arr,0,aim);
	}
	//有多少种方法吧!
	int process(vector<int>& arr, int index, int rest)
	{
		if (index == arr.size()) 
			return rest == 0?1:0;
		int ways = 0;
		//既然是一个面值的可以重复使用,那么你就需要遍历到一个度即 张数* 面值<=aim 
		for (int count = 0;count* arr[index] <= rest ; count++)
			//第一个面值的用1张,往后走
			//第一个面值的用2张,往后走
			//第一个面值的用3张,往后走,直到第一个面值的张数最大值
		{
			ways += process(arr,index+1,rest - count*arr[index]);
		}
		return ways;
	}
};

//最少张数问题
class Coins2 // 每一种面值的钱有无数张,只要是组成aim值的均可
{
public:
	int getMin(vector<int>& arr, int aim)
	{
		return process(arr,aim);
	}
	//返回最少张数
	int process(vector<int>& arr, int rest)
	{
		if (rest < 0) return -1;
		if (rest == 0)return 0;
		//rest>0
		int minCount = INT_MAX;
		for (int i = 0; i < arr.size(); i++)
		{
			int count = process(arr, rest - arr[i]);
			if (count != -1)
				minCount = min(minCount, count + 1);
		}
		return minCount;

	}
};
//没有无数张,只有一张,问怎样获得最少硬币数能拼出aimm
class Coin3
{
public:
	int getMin(vector<int>& arr, int aim)
	{
		return process(arr,0, aim);
	}
	int process(vector<int>& arr, int index, int rest)
	{
		if (rest == 0)return 0;
		if (rest < 0)return -1;
		if (index == arr.size())
			return -1;
		int p1 = process(arr,index+1,rest-arr[index]);
		int p2 = process(arr,index+1,rest);
		if (p1 == -1 && p2 == -1) return -1;
		else
		{
			if (p1 == -1)
				return p2;
			else if (p2 == -1)
				return p1 + 1;
			else
				return min(p1+1,p2);
		}
	}
};