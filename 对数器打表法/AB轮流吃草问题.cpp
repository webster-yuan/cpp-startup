#include<iostream>
using namespace std;
//AB轮流吃草,一共n份草,每次吃的时候能选择4^x份草,x>=0
//谁最先面对无草可吃的场景,谁输.
//问吃完时谁会赢?假设AB都尽力让自己赢
class Solution
{
public:
	string win(int n)
	{
		return func(n, "A");
	}
	//当剩下rest份草时,选手是cur,返回最终谁能赢
	//<4时只能一份一份吃,=4时直接吃了就赢了
	//rest: 0  1   2   3   4  
	//win:    cur     cur  cur
	string func(int rest, string cur)
	{
		string enemy = cur == "A" ? "B" : "A";
		if (rest < 5)
		{
			if (rest == 0 || rest == 2)
				return enemy;
			else return cur;
		}
		//cur开始尝试,分别尝试1,4,16,64,...时看看最终自己能不能赢
		int pick = 1;
		while (pick <= rest)
		{
			if (func(rest-pick, enemy) == cur)
				return cur;
			pick *= 4;
		}
		//都尝试一遍,发现自己都赢不了
		return enemy;
	}
public:
	string win2(int n)
	{
		if (n % 5 == 0 || n % 2 == 0)
			return "B";
		else
			return "A";
	}
};
//int main()
//{
//	Solution s;
//	for (int i = 1; i <= 50; i++)
//	{
//		cout << i << ":" << s.win(i) << endl;
//	}
//	return 0;
//}