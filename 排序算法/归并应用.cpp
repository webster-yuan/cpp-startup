#include<iostream>
#include<vector>
using namespace std;
//逆序对和最小和都是一个思想,在归并的框架下用不同的方式收集结果
class minSum
{
public:
	//找右侧区间有x个比自己大的数,在两个有序区间归并时才会产生+,res+=x*i
	int getMinSum(vector<int>& arr)
	{
		if (arr.size() == 0)
			return;
		return merageSort(arr,0,arr.size()-1);
	}
	int merageSort(vector<int>& arr, int left, int right)
	{
		if (left >= right)return 0;
		int mid = left + (right - left) / 2;
		return merageSort(arr, left, mid) + merageSort(arr, mid + 1, right) + merage(arr,left,mid,right);
	}
	int merage(vector<int>& arr, int left, int mid, int right)
	{
		vector<int>tmp(right-left+1);
		int p1 = left, p2 = mid + 1;
		int res = 0;
		int i = 0;
		while (p1 <= mid && p2 <= right)
		{
			//右侧整个有序空间的门槛比我大,那么剩下的都比我大,我就得累加那么多次
			res += arr[p1] > arr[p2] ? 0 : (right - p2 + 1) * arr[p1];
			tmp[i++] = arr[p1] > arr[p2] ? arr[p2++] : arr[p1]++;
		}
		while (p1 <= mid)
			tmp[i++] = arr[p1++];
		while (p2 <= right)
			tmp[i++] = arr[p2++];
		for (int i = 0; i < tmp.size(); i++)
			arr[left + i] = tmp[i];
	}
};