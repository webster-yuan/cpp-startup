//https://leetcode.cn/problems/advantage-shuffle/description/

//给定两个长度相等的数组 nums1 和 nums2，nums1 相对于 nums2 的优势
//可以用满足 nums1[i] > nums2[i] 的索引 i 的数目来描述。
//返回 nums1 的任意排列，使其相对于 nums2 的优势最大化

//贪心:
//1. 废物利用最大化,最废物的和对面最牛的大,反正也赢不了
//2. 利用效率最大化,能赢够用就行,不用消耗我最牛的和他比
//为了O(1)时间获取到两个数组中的目标值,将两个数组进行排序即可,都按照能力值升序排列
//返回答案时发现: 是按照nums2中值的原始顺序一一匹配的值,所以用到 按身高排序 思想
//对下标进行排序即可,因为是对照nums2实现的,所以只需要nums2的下标数组即可
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution 
{
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) 
    {
        int n = nums1.size();
        vector<int>index2(n);
        for (int i = 0; i < n; i++)
            index2[i] = i;
        sort(nums1.begin(), nums1.end());
        sort(index2.begin(), index2.end(), [&nums2](int i, int j)->bool {
            return nums2[i] < nums2[j];//升序排序
            });
        vector<int>ret(n);
        int left = 0, right = n - 1;
        for (int i = 0; i < n; i++)
        {
            if (nums1[i] > nums2[index2[left]])
                ret[index2[left++]] = nums1[i];//注意是对应位置放
            else
                ret[index2[right--]] = nums1[i];
        }
        return ret;
    }
};