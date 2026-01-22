#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
//拓扑排序:有向无环图的顶点排序方法,所有顶点排列为线性序列
//步骤
//1. 找到所有入度为0的点,将其输出到拓扑排序中
//2. 将顶点从图中删除,并将所有以该点为顶点的边的终点的入度-1
//3. 不断重复上述操作直到所有的顶点都被输出,并且图中不存在入度为0的顶点即可
class Solution
{
public:
	void topo_sort(vector<vector<int>>& arr, vector<int>& in)
	{
		queue<int> q;
		for (int i = 1; i < in.size(); i++)
		{
			if (in[i] == 0)
			{
				q.push(i);
				topo.push_back(i);
			}
		}
		while (!q.empty())
		{
			int front = q.front();
			q.pop();
			//将front指向的终点入度--
			for (int i = 0; i < arr[front].size(); i++)
			{
				int end = arr[front][i];
				in[end]--;
				if (in[end] == 0)
				{
					q.push(end);
					topo.push_back(end);
				}
			}
		}
	}
	void print()
	{
		for (int i = 0; i < topo.size(); i++)
			cout << topo[i] << " ";
		cout << endl;
	}
public:
	vector<int>topo;
};
//家谱树
void test1()
{
	int n = 0;
	cin >> n;
	int tmp = n;
	vector<vector<int>>arr(n + 1);
	vector<int> in(n + 1);		//入度,下标代表编号,只记录个数
	int index = 1;
	while (tmp--)
	{
		int next = 0;
		while (cin >> next && next != 0)
		{
			arr[index].push_back(next);
			in[next]++;
		}
		index++;
	}
	Solution s;
	s.topo_sort(arr, in);
	s.print();
}
void test2()
{
	int n = 0, m = 0;
	cin >> n >> m;
	vector<vector<int>>arr(n + 1);
	vector<int>in(n+1);
	while (m--)
	{
		int start = 0, end = 0;
		cin >> start >> end;
		arr[start].push_back(end);
		in[end]++;
	}
	Solution s;
	s.topo_sort(arr, in);
	if (s.topo.size() != n)
		cout << -1 << endl;
	else
		s.print();
}
int main()
{
	test2();
	return 0;
}