//给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
//请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。

//首个做不到nums[index]==index+1时,返回index+1就是缺失的第一个正数.但是数组是未排序的,而且还不让你排序
//l: l左侧区间都是能做到的
//r: r右侧划分的是垃圾区域,如果最好状态,前n个数字都不缺,初始化为n,代表0~n-1区间中都有1~n这些个数字
//1. if [l]== l+1
//2. if [l]<=l,垃圾,和垃圾r的前一个位置交换,让最好预期在变差,也就是指望能做到标准的区间在缩小.
//  指望的是[l,r]区间上的数字,这样是出现和之前已经确认的数字重复了,没用了
//3. if [l]>r,垃圾
//4. [[l]-1]==[l],垃圾,出现两个重复的值,本来指望让[l]到达[l]-1的位置,但是你发现[[l]-1]==[l],
//  重复数字让预期变差
//5. 不是垃圾,就交换[l]-1和l位置,看此时l位置是不是l+1这个值,不是继续,是就l++,有效区间扩充
//https://www.bilibili.com/video/BV1V841167Rg?t=6014.1
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
    int firstMissingPositive(vector<int>& arr)
    {
		// l的左边，都是做到i位置上放着i+1的区域
		// 永远盯着l位置的数字看，看能不能扩充(l++)
		int l = 0;
		// [r....]垃圾区
		// 最好的状况下，认为1~r是可以收集全的，每个数字收集1个，不能有垃圾
		// 有垃圾呢？预期就会变差(r--)
		int r = arr.size();
		while (l < r) {
			if (arr[l] == l + 1) 
				l++;
			else if (arr[l] <= l || arr[l] > r || arr[arr[l] - 1] == arr[l]) 
				swap(arr[l], arr[--r]);
			else 
				swap(arr[l], arr[arr[l] - 1]);
		}
		return l + 1;
    }
};