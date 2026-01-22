#include<iostream>
#include<vector>
using namespace std;

class Solution 
{
public:
//数组分三块,当都是重复元素时,只遍历一次,因为左右区间都不存在,遍历一次之后就返回了
//随机返回数组中的选择基准元素
    vector<int> sortArray(vector<int>& nums) 
    {
        srand(time(NULL));
        qsort(nums,0,nums.size()-1);
        return nums;
    }
    void qsort(vector<int>&nums,int left,int right)
    {
        if(left>=right) return ;
        int key=getRandom(nums,left,right);
        int i=left,less=left-1,more=right+1;
        while(i<more)
        {
            if(nums[i]>key)
                swap(nums[--more],nums[i]);
            else if(nums[i]<key)
                swap(nums[++less],nums[i++]);
            else
                i++;
        }
        //left less  less+1,more-1, more,right
        qsort(nums,left,less);
        qsort(nums,more,right);
    }
    //返回区间内的一个随机值
    int getRandom(vector<int>&nums,int left,int right)
    {
        int r=rand();
        return nums[r%(right-left+1) + left];
    }
};
class Sort
{
public:
	//堆排序
	//堆:用数组空间模拟的完全二叉树结构
	//如果是二倍扩容,扩容次数O(logN),拷贝是O(N),整体是O(nlogn),均摊到每个点就是O(logn)
	void HeapSort(vector<int>& arr)
	{
		if (arr.size() < 2)return;
		//建立大堆
		for (int i = 0; i < arr.size(); i++)
		{
			HeapInsert(arr,i);//O(logN)
		}
		//进行堆排
		int sz = arr.size();
		swap(arr[0],arr[sz-1]);
		while (sz>0)//O(N)
		{
			HeapIfy(arr,0,sz);//O(logN)
			swap(arr[0], arr[--sz]);
		}
	}
	//在index的位置插入x之后,调整类似向上调整,和父亲节点比较
	//默认是大堆调整
	//需求:将整个数组调整为大跟堆,从最后一个父亲节点开始向下调整heapIfy
	//最底层占将近一半,N/2,无法向下再调整,只看一眼,代价是1
	//倒数第二层N/4个,可以向下操作,看一眼,代价是2
	//倒数第二层N/8个,可以向下操作2次,看一眼,代价是3
	//....
	//整体复杂度就是T(N)=N/2*1+N/4*2+N/8*3....
	//从heapInsert的O(N*logN)=>O(N)
	void HeapInsert(vector<int>& arr, int index)
	{
		while (arr[index] > arr[(index - 1) / 2])
		{
			swap(arr[index], arr[(index - 1) / 2]);
			index = (index - 1) / 2;
		}
	}
	//从index位置开始向下调整,此时heap.size()=sz
	void HeapIfy(vector<int>& arr, int index, int sz)
	{
		int left = index * 2 + 1;
		while (left < sz)
		{
			int better = left;
			if (left + 1 < sz && arr[left + 1] > arr[left])
				better = left + 1;
			if (arr[better] < arr[index])
				break;
			else //if (arr[better] > arr[index])
			{
				swap(arr[better], arr[index]);
				index = better;
				left = index * 2 + 1;
			}
		}
	}
public:
	//T=O(nlogn)空间复杂度为O(logn)当正好取到二分时,主要是递归栈中的空间使用
	//version1-挖坑法
	void QuickSort1(vector<int>& arr)
	{
		int n = arr.size();
		if (n < 2)return;
		return quick_sort(arr,0,n-1);
	}
	void quick_sort(vector<int>& arr, int l, int r)
	{
		if (l >= r)return;
		int key = partition1(arr, l, r);
		quick_sort(arr, l, key - 1);
		quick_sort(arr,  key+1,r);
	}
	int partition1(vector<int>& arr, int l, int r)
	{
		//三数取中,避免极端情况的出现
		int key =l;
		while (l < r)
		{
			//从右区间找一个<key的值
			while (l<r && arr[r]>arr[key])
				r--;
			while (l < r && arr[l] < arr[key])
				l++;
			swap(arr[l], arr[r]);
		}
		swap(arr[key], arr[l]);
		return l;
	}
	//version2-区间划分
	//将荷兰国旗最好情况target正好是一半时,T=O(nlogn)推广,可能是1/3,1/4...,每一种概率的期望都是1/3p+(2/3(1-p))
	//最后将所有相加之后总期望就是O(nlogn)
	//随机选择一个数和最后一个交换,进行荷兰国旗问题即区间划分
	void QuickSort2(vector<int>& arr)
	{
		if (arr.size() < 2)
			return;
		quickSort(arr, 0, arr.size() - 1);
	}
	void quickSort(vector<int>& arr, int l, int r)
	{
		if (l >= r)return;
		int pos = rand() % (r-l+1)+l;//偏移量+left
		swap(arr[l + pos], arr[r]);
		pair<int, int>ret = partition(arr,l,r);
		quickSort(arr,l,ret.first-1);
		quickSort(arr,ret.second+1,r);
	}
	pair<int,int> partition(vector<int>& arr, int l, int r)
	{
		int less = l - 1, more = r + 1;
		while (l < more)//遍历到more区间就停止
		{
			if (arr[l] > arr[r])
			{
				swap(arr[more - 1], arr[l]);
				more--;
			}
			else if (arr[l] < arr[r])
			{
				swap(arr[less + 1], arr[l]);
				less++, l++;
			}
			else
				l++;
		}
		swap(arr[r],arr[more-1]);
		return {less+1,more-1};
	}
	//
	//master公式的使用
	void merageSort(vector<int>& arr)
	{
		if (arr.size() < 2)
			return;
		return merageSortHelper(arr, 0, arr.size() - 1);
	}
	//两次二分调用,a=2,b=2 log(b,a)=1,其他调用merage是O(N^1),d=1,所以T(N)=O(N^d*logN)
	void merageSortHelper(vector<int>& arr, int left, int right)
	{
		if (left >= right)return;
		int mid = left + (right - left) + 1;
		merageSortHelper(arr, left, mid);
		merageSortHelper(arr, mid+1,right);
		merage(arr,left,mid,right);//将两个有序数组进行归并
	}
	void merage(vector<int>& arr, int left, int mid, int right)
	{
		vector<int>tmp(right-left+1);
		int p1 = left;
		int p2 = mid + 1;
		int i = 0;
		while (p1 <= mid && p2 <= right)
		{
			tmp[i++] = arr[p1] > arr[p2] ? arr[p2++] : arr[p1++];
		}
		while (p1 <= mid)
			tmp[i++] = arr[p1++];
		while (p2 <= right)
			tmp[i++] = arr[p2++];
		//拷贝回原数组
		for (int i = left; i < tmp.size(); i++)
			arr[left + i] = tmp[i];
	}
public://<O(n^2),O(1)>
	//数据发生变化影响流程
	//想让[0,i]区间有序,从i-1往前找合适的位置插入
	void Insert(vector<int>& arr)
	{
		int n = arr.size();
		if (n < 2)return;
		for (int i = 1; i < n; i++)
		{
			for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
				swap(arr[j],arr[j+1]);
		}
	}
public://数据发生变化不影响流程

	//从i位置开始向后走,如果比后一个更大就交换
	//一轮安排一个最大值,区间右边界一直在左移动
	void BubbleSort(vector<int>& arr)
	{
		int n = arr.size();
		if (n < 2)return;
		for (int i = n-1; i>=0; i--)//
		{
			for (int j = 0; j <i; j++)
			{
				if (arr[i] > arr[i + 1])
					swap(arr[i],arr[i+1]);
			}
		}
	}
	//从i位置开始向后找最小的数放在i位置,i++
	//O(n^2)不稳定排序
	void SelectSort(vector<int>& arr)
	{
		if (arr.size() < 2)
			return;
		for (int i = 0; i < arr.size(); i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < arr.size(); j++)
			{
				minIndex = arr[minIndex] > arr[j]?j:minIndex;
			}
			swap(arr[minIndex],arr[i]);
		}
	}
};