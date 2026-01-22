//https://leetcode.cn/problems/wiggle-subsequence/description/
//摆动序列: 相邻两个数之间的差值必须是正负数交替称为摆动,找到最长的子序列并返回长度即可.
//可能存在多个子序列的长度是相同的,但是只要返回长度即可
//仅有一个元素或者含两个不等元素的序列也视作摆动序列

//解法一: 使用dp的方式,时间复杂度是O(N^2)
//以i位置为结尾的,所有子序列中,最长摆动序列的长度.因为是摆动,所以最后一个位置由两个状态
//f[i]:以i位置为结尾的所有子序列中,上升趋势到达i位置的最长摆动序列的长度
//g[i]:以i位置为结尾的所有子序列中,下降趋势到达i位置的最长摆动序列的长度
//f[i]=max(f[i],g[j-1]+1)
//g[i]=max(g[i],f[i-1]+1)
//因为是子序列,所以到达i位置时,[0,i-1]区间中任何一个j都可能是i的前一个位置,
//所以需要遍历寻找能够组成的最长的子序列
//初始化: 最少自己组成一个子序列
//返回值: 两个数组中,最大值
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
public:
    int wiggleMaxLength(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int>f(n,1);
        vector<int>g(n, 1);
        int ret = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                    f[i] = max(f[i], g[j] + 1);
                else if (nums[j] > nums[i])
                    g[i] = max(g[i], f[j] + 1);
            }
            ret = max(ret, max(f[i], g[i]));
        }
        return ret;
    }
};
//解法二: 贪心的方式
//因为要尽可能多的选择,所以将第一个就选中,
//那么要选择摆动序列时,贪心的选择距离自己最近的峰值点,这个点将整体分成两部分,
//一部分是左侧上升区间,剩下的作为另一部分,
//在左侧区间中选择峰值点之后,可以保证另一部分中可以有更多的点可以被选中,因为要保证摆动
//选中最近的峰值点是为了让后续有更多的峰值点被选中,让摆动更多.
//同理在下降的区间中选择最低点.
//统计出所有的波峰波谷
//1. 如何确定一个点是波峰还是波谷?index左右差值正负情况判断.
//2. 涉及到相等值导致一段水平的出现,但是还是趋近于波谷(峰)的,所以可以忽略水平的中间那些值,只考虑
//边界left左侧和right右侧的趋势是否代表着波峰(谷) if left*right <0,就是一个波峰(谷),ret++
// if right==0 continue;即i++,代表忽略这个水平区间相等值
// beat 100%
class Solution 
{
public:
    int wiggleMaxLength(vector<int>& nums) 
    {
        int n = nums.size();
        if (n <2)
            return n;
        int ret = 0, left = 0;
        for (int i = 0; i < n-1; i++)
        {
            int right = nums[i + 1] - nums[i];
            if (right == 0)
                continue;
            else
            {
                if (left * right <= 0)//==0代表的是第一个元素,选中
                    ret++;
                left = right;
            }
        }
        //循环无法选中最后一个节点,但是肯定还是选中的
        return ret + 1;
    }
};