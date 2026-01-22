//https://www.nowcoder.com/practice/2a2c00e7a88a498693568cef63a4b7bb
#include <iostream>
#include<vector>
using namespace std;
//vector底层使用的就是new,就是在堆上申请空间,不用考虑栈溢出问题.
//所以根本不用自己new,效率是一样的.
//效率上cout << printf(),这道题就是cout完全过不了
void func(vector<int>&arr)
{
	int n = arr.size();
	vector<int>st = vector<int>(n);
	vector<vector<int>>ans = vector<vector<int>>(n, vector<int>(2));
	int r = 0;
	int cur = 0;
	for (int i = 0; i < n; i++)
	{
		while (r > 0 && arr[st[r - 1]] >= arr[i])
		{
			cur = st[--r];
			ans[cur][0] = r > 0 ? st[r - 1] : -1;
			ans[cur][1] = i;
		}
		st[r++] = i;
	}
	while (r > 0)
	{
		cur = st[--r];
		ans[cur][0] = r > 0 ? st[r - 1] : -1;
		ans[cur][1] = -1;
	}
	for (int i = n - 2; i >= 0; i--)
	{
		if (ans[i][1] != -1 && arr[i] == arr[ans[i][1]])
			ans[i][1] = ans[ans[i][1]][1];
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d %d\n",ans[i][0],ans[i][1]);
		//cout << ans[i][0] << " " << ans[i][1] << endl;时间太长,还是得用printf()
	}
}
int main()
{
	int n = 0;
	cin >> n;
	vector<int>arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	func(arr);
	return 0;
}


//class Solution
//{
//    static const int MAXN = 1000001;
//    int* st;
//    int** ans;
//    int n;
//public:
//    Solution()
//    {
//        st = new int[MAXN];
//        ans = new int* [MAXN];
//        for (int i = 0; i < MAXN; i++)
//            ans[i] = new int[2];
//        for (int i = 0; i < MAXN; i++)
//        {
//            st[i] = 0;
//            for (int j = 0; j < 2; j++)
//                ans[i][j] = 0;
//        }
//    }
//    ~Solution()
//    {
//        delete[] st;
//        for (int i = 0; i < MAXN; i++)
//            delete[] ans[i];
//    }
//public:
//    void func(vector<int>&arr)
//    {
//        n = arr.size();
//        int r = 0;
//        int cur = 0;
//        for (int i = 0; i < n; i++)
//        {
//            //需要弹出栈顶
//            while (r > 0 && arr[st[r - 1]] >= arr[i])
//            {
//                cur = st[--r];
//                ans[cur][0] = r > 0 ? st[r - 1] : -1;
//                ans[cur][1] = i;
//            }
//            st[r++] = i;
//        }
//        //st中可能剩余元素,进入清算环节
//        while (r>0)
//        {
//            cur = st[--r];
//            ans[cur][1] = -1;
//            ans[cur][0] = r > 0 ? st[r - 1] : -1;
//        }
//        //修正环节,因为是从左向右进行,所以左侧最近较小值一定是正确的,
//        //如果存在重复值造成错误,也是右侧更新有误,如果发现和自己相等,就直接等于他的答案即可
//        //注意需要从后往前进行修正更新
//        for (int i = n - 2; i >= 0; i--)
//        {
//            if (ans[i][1] != -1 && arr[ans[i][1]] == arr[i])
//                ans[i][1] = ans[ans[i][1]][1];
//        }
//    }
//public:
//    void print()
//    {
//        for (int i = 0; i < n; i++)
//        {
//            cout << ans[i][0] << " " << ans[i][1] << endl;
//        }
//    }
//};
//int main()
//{
//    int n = 0;
//    cin >> n;
//    Solution s;
//    vector<int>arr(n);
//    for (int i = 0; i < n; i++)
//        cin >> arr[i];
//    s.func(arr);
//    s.print();
//}