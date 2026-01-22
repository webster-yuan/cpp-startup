#include<iostream>
using namespace std;
//"好串":字符串中有且仅有一个长度>=2的回文串
//用r e d三种字符拼出长度为n的所有字符串中,好串的个数
//暴力生成所有长度为n的子串,然后一个个验证

class Solution
{
	int n;
	string str;
	int ret;
public:
	int getNum(int num)
	{
		string path;
		n = num;
		str = "red";
		int ans=dfs(path, 0);
		return ans;
	}
	int dfs(string path, int sz)
	{
		if (sz ==n)
		{
			int cnt = 0;
			for (int l = 0; l < path.size(); l++)
			{
				for (int r = l + 1; r < path.size(); r++)
				{
					if (isTrue(path, l, r))
						cnt++;
					if (cnt > 1)
						return 0;
				}
			}
			return cnt == 1 ? 1 : 0;
		}
		else
		{
			int ans = 0;
			for (int i = 0; i < str.size(); i++)
				ans += dfs(path + str[i], sz + 1);
			return ans;
		}
	}
public:
	int getNum1(int num)
	{
		string path;
		n = num;
		str = "red";
		ret = 0;
		dfs1(path, 0);
		return ret;
	}
	void dfs1(string path, int sz)
	{
		if (sz == n)
		{
			int cnt = 0;
			for (int l = 0; l < path.size(); l++)
			{
				for (int r = l + 1; r < path.size(); r++)
				{
					if (isTrue(path, l, r))
						cnt++;
					if (cnt > 1)
						return;
				}
			}
			if (cnt == 1)
				ret++;
			return;
		}
		for (int i = 0; i < str.size(); i++)
		{
			dfs1(path + str[i], sz+1);
		}
	}
private:
	bool isTrue(string& str, int l, int r)
	{
		while (l < r)
		{
			if (str[l] != str[r])return false;
			l++;
			r--;
		}
		return true;
	}
public:
	//打表法发现4之后都是在30的基础上+6
	//len=1 2 3   4  5  ...
	//num=0,3 18 30 36 42
	int getNum2(int n)
	{
		if (n == 1)return 0;
		if (n == 2)return 3;
		if (n == 3)return 18;
		if (n >= 4)
			return 30 + (n - 4) * 6;
	}
};

//int main()
//{
//	Solution s;
//	for (int i = 1; i <= 10; i++)
//	{
//		cout << i << ":" << s.getNum(i) <<"-"<<s.getNum1(i) << "-" << s.getNum2(i) << endl;
//	}
//	return 0;
//}