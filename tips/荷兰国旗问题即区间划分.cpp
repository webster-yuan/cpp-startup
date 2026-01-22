#include<iostream>
#include<vector>
using namespace std;

//给定数组arr,和target,将arr划分为三部分,< = >三个区间
class NetherLandFlag
{
public:
	pair<int, int>partion(vector<int>& arr, int l, int r, int p)
	{
		int less = l - 1, more = r + 1;
		while (l < more)
		{
			if (arr[l] < p)//将值放到less区间中
			{
				swap(arr[less + 1], arr[l]);
				less++;
				l++;
			}
			else if (arr[l] > p)//将值放到more区间中
			{
				swap(arr[more - 1], arr[l]);
				more--;
			}
			else
				l++;
		}
		return {less+1,more-1};
	}
};