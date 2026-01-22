
//每滴水以每秒1单位往下落,
//给定N滴水的坐标和往下落的高度 (x,y)
//问: 当要求落到花盆中的水中,下落的最大时间间隔为D时,花盆的最小区间长度是多少
//https://www.luogu.com.cn/record/124757479

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
	static const int N = 100005;
	int maxQueue[N] = { 0 };
	int minQueue[N] = { 0 };
	int minh, mint, maxh, maxt;
	vector<vector<int>>nums;
private:
	struct compare
	{
		bool operator()(vector<int>& x, vector<int>& y)
		{
			if (x[0] < y[0])
				return true;
			else
				return false;
		}
	};
public:
	int minLenFallingWater(vector<vector<int>>& arr,int d)
	{
		const int MAX = 0x3f3f3f3f;
		minh = mint = maxh = maxt = 0;
		//先以下标x进行数组中排序,才好进行后续
		sort(arr.begin(),arr.end(),compare());
		//一定是先jb排序之后,再交给全局数组nums,要不然逻辑都错啦!!!!
		nums = arr;
		int n = nums.size();
		int ans = MAX;
		for (int l = 0, r = 0; l < n; l++)
		{
			while (!ok(d) && r < n)
				push(r++);
			if (ok(d))
				ans = min(ans, arr[r - 1][0] - arr[l][0]);//x坐标相减
			pop(l);
		}
		nums.clear();
		Clear();
		//注意返回值设置,这种特殊情况的判断!!!!!
		return ans==MAX?-1:ans;
	}
	void Clear()
	{
		for (int i = 0; i < N; i++)
		{
			minQueue[i] = 0;
			maxQueue[i] = 0;
		}
	}
	bool ok(int d)
	{
		int max_val = maxh < maxt ? nums[maxQueue[maxh]][1] : 0;
		int min_val = minh < mint ? nums[minQueue[minh]][1] : 0;
		return (max_val - min_val) >= d;
	}
	void push(int r)
	{
		while (maxh < maxt && nums[maxQueue[maxt - 1]][1] <= nums[r][1])
			maxt--;
		maxQueue[maxt++] = r;
		while (minh < mint && nums[minQueue[mint - 1]][1] >= nums[r][1])
			mint--;
		minQueue[mint++] = r;
	}
	void pop(int l)
	{
		//四个参数长得相似，可别写混啦啊啊！！！！！！！！！
		if (maxh < maxt && maxQueue[maxh] == l)
			maxh++;
		if (minh < mint && minQueue[minh] == l)
			minh++;
	}
};
int main()
{
	int n = 0, d = 0;//n滴水,时间间隔为d
	cin >> n >> d;
	vector<vector<int>> arr(n, vector<int>(2));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
			cin >> arr[i][j];
	}
	Solution s;
	int ret =s.minLenFallingWater(arr,d);
	cout << ret<< endl;
	return 0;
}