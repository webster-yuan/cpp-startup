#include<iostream>
#include<vector>
using namespace std;

class BSFind
{
public:
	//无序数组找局部最小值问题
	int FindOneLessVal(vector<int>& arr)
	{
		int n = arr.size();
		if (n == 0)return -1;
		if (n==1 || arr[0] < arr[1])
			return arr[0];
		if (arr[n - 1] < arr[n - 2])
			return arr[n - 1];
		int left = 1,right=n-2;
		while (left < right)
		{
			int mid = left + (right - left) / 2;
			if (arr[mid] < arr[mid - 1] && arr[mid] < arr[mid + 1])
				return mid;
			else if (arr[mid] > arr[mid + 1])
				left = mid + 1;
			else if(arr[mid] > arr[mid - 1])
				right = mid - 1;
		}
		return left;
	}
	//数组翻转,将最小的那n个折叠到后面,数组分为两段有序,找到最小值下标
	// 旋转排序数组中最小值
	//分到右半区间,选取最后数字作为区分是左区间还是右区间的标志.< >=
	int FindLeastVal(vector<int>& arr)
	{
		int n = arr.size();
		if (n == 0)return -1;
		int left = 0, right = n - 1;
		int x = arr[right];//选取最后数字作为区分是左区间还是右区间的标志
		while (left < right)
		{
			int mid = left + (right - left) / 2;
			if (arr[mid] > x)
				left = mid + 1;
			else
				right = mid;
		}
		return left;
	}
	//经典二分查找
	bool BSExist(vector<int>& arr, int x)
	{
		int left = 0, right = arr.size() - 1;
		while (left <= right)
		{
			int mid = left + (right - left) / 2;
			if (arr[mid] > x)
				right = mid - 1;
			else if (arr[mid] < x)
				left = mid + 1;
			else
				return true;
		}
		return false;
	}
	//找到相等区间中最左边的下标,二段性那个值被分配到了右半区间 < >= 
	//最终left和right共同指向那个位置
	int BSFindLeftEdge(vector<int>& arr, int x)
	{
		int left = 0, right = arr.size() - 1;
		while (left < right)
		{
			int mid = left + (right - left) / 2;//偶数个时取到左边的那个
			if (arr[mid] > x)
				left = mid + 1;
			else right = mid;
		}
		return left;
	}
	//在有序数组中搜索插入位置 < >= 
	int FindInsertPos(vector<int>& arr, int x)
	{
		int left = 0, right = arr.size() - 1;
		while (left < right)
		{
			int mid = left + (right - left) / 2;//偶数个时取到左边的那个
			if (arr[mid] > x)
				left = mid + 1;
			else right = mid;
		}
		if (arr[left] < x) return right + 1;
		return left;
	}

	//找到相等区间中最右边的下标,二段性那个值被分配到了左半区间 <= > 
	//最终left和right共同指向那个位置
	int BSFindRightEdge(vector<int>& arr, int x)
	{
		int left = 0, right = arr.size() - 1;
		while (left < right)
		{
			int mid = left + (right - left+1) / 2;//偶数个时取到右边的那个
			if (arr[mid] < x)
				left = mid;
			else
				right = mid - 1;
		}
		return left;
	}
	//x的平方根,向左取整, <= >
	int mySqrt(int x)
	{
		if (x < 1)return 0;
		int left = 1, right = x;
		while (left < right)
		{
			long long mid = left + (right - left+1) / 2;
			if (mid * mid < x)
				left = mid;
			else
				right = mid - 1;
		}
		return left;
	}

	//查找峰值索引,一段上升到顶之后持续下降,下面两种做法均可
	//arr[mid]>arr[mid+1]右半区间 arr[mid]<arr[mid+1]左半区间 mid+1可能是返回值,所以分为 <= >
	//arr[mid]>arr[mid-1]右半区间 arr[mid]<arr[mid-1]左半区间 mid-1可能是返回值,所以分为 < >=
	int findTopIndex(vector<int>& arr)
	{
		int n = arr.size();
		if (n < 0)return -1;
		int left = 0, right = n - 1;
		while (left < right)
		{
			int mid = left + (right - left+1) / 2;
			if (arr[mid + 1] > arr[mid])
				left = mid;
			else 
				right = mid - 1;
		}
		return left;
	}
};