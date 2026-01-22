#include<iostream>
using namespace std;
//根据对数器打表找规律
//特判升级为O(1)复杂度
class Solution
{
public:
	int minBags(int apples)
	{
		int ans = func(apples);
		return ans == INT_MAX ? -1 : ans;
	}
	//给定rest剩余多少个苹果,使用6,8袋子必须装满,返回需要多少个袋子
	int func(int rest)
	{
		//代表无效解,是上一层rest-8得到的,如果<0,说明不能用8的袋子装满
		if (rest < 0)
			return INT_MAX;
		if (rest == 0)//已经没有苹果了,当然不需要袋子了
			return 0;
		int p1 = func(rest - 8);
		int p2 = func(rest - 6);
		if (p1 != INT_MAX)
			p1 += 1;
		if (p2 != INT_MAX)
			p2 += 1;
		return min(p1, p2);
	}
public:
	int minBages2(int n)
	{
		if (n % 2 != 0)return -1;
		if (n < 18)
		{
			if (n == 6 || n == 8)
				return 1;
			else if (n == 12 || n == 14 || n == 16)
				return 2;
			else
				return -1;
		}
		return (n - 18) / 8 + 3;
	}
};
//int main()
//{
//	Solution s;
//	for (int i = 1; i <= 50; i++)
//	{
//		cout << i << ": " << s.minBags(i) <<"<->"<<s.minBages2(i) << endl;
//	}
//	return 0;
//}