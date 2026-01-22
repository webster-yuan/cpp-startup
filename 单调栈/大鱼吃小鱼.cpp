
//正常例子: https://www.bilibili.com/video/BV1GH4y1D7TB?t=3245.9
//因为只能吃右侧比自己小的鱼
//当从后往前遍历时,单调栈维护小压大的单调性,
//top()一定是在下面的鱼的左边,那么如果是大压小的话,为什么不直接吃掉呢?
//单调栈记录的数据<鱼大小,将这个鱼以及后续完成总共需要的轮数>
//当[index]>top()时,代表可以吃掉,那么弹出栈顶元素,轮数是max([index]+1,top().轮数)
//特殊情况: https://www.bilibili.com/video/BV1GH4y1D7TB?t=3504.8
//存在相等值时: https://www.bilibili.com/video/BV1GH4y1D7TB?t=3930.5
//直接进入不用弹出,只有当严格小的时候再弹出.

//https://www.nowcoder.com/practice/77199defc4b74b24b8ebf6244e1793de
#include<iostream>
#include<vector>
using namespace std;
int get_turns(vector<int>& arr)
{
	int n = arr.size();
	vector<vector<int>>st(n,vector<int>(2));//存放两个数据<arr[i],turns>
	int r = 0;
	int ans = 0;
	int curTurns = 0;
	for (int i = n-1; i>=0; i--)
	{
		curTurns = 0;
		while (r > 0 && arr[i] > st[r - 1][0])
		{
			curTurns = max(curTurns + 1, st[--r][1]);
		}
		st[r][0] = arr[i];
		st[r++][1] = curTurns;
		ans = max(ans, curTurns);
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
	int ret = get_turns(arr);
	printf("%d\n", ret);
	return 0;
}