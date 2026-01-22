#include<iostream>
using namespace std;
//12 =3+4+5 true
//从每一个起点开始尝试连续区间,有一个区间能够构成就返回true
class Solution
{
public:
	bool isTrue(int n)
	{
		for (int start = 1, sum = 0; start <= n; start++)
		{
			sum = start;
			for (int j = start + 1; j <= n; j++)
			{
				if (sum + j > n)
					break;
				else if (sum + j == n)
					return true;
				else
					sum += j;
			}
		}
		return false;
	}
public:
	//发现如果是2^x就不能表示,其他都可以表示
	bool isTrue2(int n)
	{
		return (n & (n - 1)) != 0;
	}
};
//int main()
//{
//	Solution s;
//	for (int i = 1; i <= 50; i++)
//	{
//		cout << i << ":" << s.isTrue(i) << endl;
//	}
//	return 0;
//}