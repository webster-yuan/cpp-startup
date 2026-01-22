//https://www.nowcoder.com/practice/7037a3d57bbd4336856b8e16a9cafd71
// 起初， 机器人在编号为0的建筑处。
// 每一步，它跳到下一个（右边）建筑。假设机器人在第k个建筑，且它现在的能量值是E, 下一步它将跳到第个k+1建筑。
// 它将会得到或者失去正比于与H(k+1)与E之差的能量。
// 如果 H(k+1) > E 那么机器人就失去 H(k+1) - E 的能量值，否则它将得到 E - H(k+1) 的能量值。
// 因为存在获取能量,所以可能类加的过程中导致能量越界,当大于max时就肯定能完成了,直接返回即可,实现剪枝
//问你想要到达最终台阶,初始能量至少应该是多少?
//单调性: 肯定是初始能量越高,能够走得台阶数量肯定更多
//能量范围:[0,maxVal]台阶高度最大值
//提供func函数判断在m初始能量下能否到达最终的台阶?

#include <iostream>
#include<vector>
using namespace std;
bool func(vector<int>& arr, int m, int maxVal)
{
	for (int i = 0; i < arr.size(); i++)
	{
		if (m <= arr[i])
			m -= arr[i] - m;
		else
			m += m - arr[i];
		if (m >= maxVal)
			return true;
		if (m < 0)
			return false;
	}
	return true;
}
int compute(vector<int>& arr)
{
	int l = 0, r = 0;
	for (int x : arr)
		r = max(x, r);
	int maxVal = r;
	int ans = -1;
	while (l <= r)
	{
		int m = l + ((r - l) / 2);
		if (func(arr, m, maxVal))
		{
			ans = m;
			r = m - 1;
		}
		else
			l = m + 1;
	}
	return ans;
}

int main() 
{
	int n = 0;
	cin >> n;
	vector<int>arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	int ret = compute(arr);
	printf("%d\n", ret);
	return 0;
}
