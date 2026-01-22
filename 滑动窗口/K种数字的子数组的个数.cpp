//以i位置为结尾
//https://leetcode.cn/problems/subarrays-with-k-different-integers/
// 区间范围固定,如果范围扩的越大,种类的个数越可能超过K.单调性
// 只求个数等于K是没有单调性的,因为不一定区间扩大或者缩小种类就不等于K.不超过K就有单调性了
//nums的所有子数组中是好子数组的个数是多少?
//好子数组: 包含的数字的种类必须是既定的K个,就是好子数组
//题解:
//如果有f函数,f(nums,k)返回的是数组中数字种类<=k的子数组的个数
//那么等于k的子数组的个数ret = f(nums,k)-f(nums,k-1)
//f函数统计区间[l,r]区间上数字种类小于k时的子数组的个数,累加上以r为结尾的所有子数组的个数
// 以r为结尾的子数组的个数是r-l+1,比如[0...3]: 0~3,1~3,2~3,3~3 4个
//用一个容器x统计区间出现的字符种类及个数,支持插入删除固定元素
//1. 如果右扩的过程中,x的种类数<k,r++
//2. 如果x的种类数kind==k,记录此时的子数组的个数
//	然后l++,删除l
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) 
    {
        return f(nums, k) - f(nums, k - 1);
    }
    int f(vector<int>& nums, int k)
    {
        //约定好大小是N,那么所有的数字都是1~N区间内的数字.那么就开N+1空间进行数字词频统计
        vector<int>cnts(20001,0);
        int collect = 0;
        int ans = 0;
        for (int l = 0, r = 0; r < nums.size(); r++)
        {
            if (++cnts[nums[r]] == 1)//这种字符第一次进来
                collect++;
            while (collect > k)
            {
                if (--cnts[nums[l++]] == 0)
                    collect--;
            }
            //collect==k
            //每次添加一会r,就累加上以r为结尾的子数组个数
            ans += r - l + 1;
        }
        return ans;
    }
};