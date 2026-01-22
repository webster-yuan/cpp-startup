#include<iostream>
#include<vector>
#include<string>
using namespace std;

//一组数组串，比如“283691235”进行分割，要求分出的数字范围[3, 135]
//例如：28 3 6 9 12 3 5
//打印所有的结果

// dfs() 每一个数字都有为头的情况
// 子问题: 决策树: 遍历到index位置时,都可以遍历和index+1的字符组合.
// 剪枝: 由数字范围可知,数字的大小不会超过三位数,所以当拼得到的path.size()==3时就可以返回
// 回溯: 恢复现场,使用形参拷贝的方式,在返回的时候就自动完成恢复的操作
// 出口: 每次到达一个节点,就判断它是否在范围之内,当path.size()==3时就可以直接返回
class Solution
{
	vector<int> ret;
	int n;
	int low, high;
public:
	vector<int> getNums(string& str)
	{
		n = str.size();
		low = 3, high = 135;
		string path = "";
		dfs(str, path, 0);
		return ret;
	}
	void dfs(string& str, string path, int index)
	{
		if (path.size() > 3)return;
		//<=3就可以判断是否是满足条件的
		if (path.size() >= 1)
		{
			int num = stoi(path);
			if (num >= low && num <= high)
				ret.push_back(num);
		}
		//path.size()<=3
		for (int i = index; i < n; i++)
		{
			dfs(str, path + str[i], i+1);
		}
	}
};
int main()
{
	Solution s;
	string str = "2836";
	vector<int>ret = s.getNums(str);
	for (auto e : ret)
		cout << e << " ";
}