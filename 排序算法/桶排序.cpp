#include<iostream>
#include<vector>
using namespace std;

//不基于比较的排序=>桶排序
//计数排序
class BucketSort
{
public:
	int radix = 10;//几进制就分几个桶
	//基数排序
	void radixSort(vector<int>& arr)
	{
		if (arr.size() == 0)return;
		radixSortHelper(arr,0,arr.size()-1,getMaxDigit(arr));
	}
	void radixSortHelper(vector<int>& arr, int begin, int end, int digit)
	{
		//最大位数决定了要出桶和入桶几次
		//入桶模拟:使用count[i]代表个位(十位...)<=i的数字有几个
		//出桶模拟:根据count[i]->使用helper数组乘放按照个位(十位...)排序号的数字
		for (int d = 1; d <= 10; d++)
		{
			vector<int>count(radix);
			for (int i = begin; i <= end; i++)
			{
				int j = getSingleDigit(arr[i], d);
				count[j]++;
			}
			//处理前缀和->代表个位小于等于i的有几个数字
			for (int i = 1; i < radix; i++)
				count[i] += count[i - 1];

			//出桶->helper数组中
			vector<int>bucket(end-begin+1);
			for (int i = end; i >= begin; i--)
			{
				int j = getSingleDigit(arr[i],d);
				bucket[count[i] - 1] = arr[i];
				count[i]--;
			}
			//helper->arr
			for (int i = begin, j = 0; i <= end; i++, j++)
			{
				arr[i] = bucket[j];
			}
		}
	}
	int getSingleDigit(int num, int digit)//获取数字num某一位的数字,题意:d=1->想要个位数
	{
		return (num / (int)(pow(10, digit - 1))) % 10;
		// 123456 你想要5,此时约定好的digit=2,123456 /10=12345 ,%10=5 
	}
	int getMaxDigit(vector<int>& arr)
	{
		//找到最大值的最大位数
		int maxSum = 0;
		for (auto e : arr)
			maxSum = max(maxSum,e);
		int digit = 0;
		while (maxSum)
		{
			digit++;
			maxSum /= 10;
		}
		return digit;
	}

public:
	//计数排序
	void CountSort(vector<int>& arr)
	{
		if (arr.size() == 0)return;
		//1. 找到最大值然后开空间
		int maxSum = INT_MIN;
		for (int i = 0; i < arr.size(); i++)
			maxSum = max(maxSum,arr[i]);
		vector<int>count(maxSum+1);
		//2. 遍历,统计词频
		for (int i = 0; i < arr.size(); i++)
			count[arr[i]]++;
		//3. 输出
		int i = 0;
		for (int j = 0; j < count.size(); j++)
		{
			while (count[j]--)
				arr[i++] = count[j];
		}
	}
};