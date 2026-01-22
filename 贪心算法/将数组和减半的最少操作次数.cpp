
//https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/
//每次选择数组中数字最大的删除,为了提升效率使用大跟堆O(1)时间获取
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution 
{
public:
    int halveArray(vector<int>& nums) 
    {
        priority_queue<double> bigHeap;
        int n = nums.size();
        double sum = 0;//涉及到小数,一定要是double类型,否则会发生截断问题导致精度丢失
        for (int i = 0; i < n; i++)
        {
            bigHeap.push(nums[i]);
            sum += nums[i];
        }
        sum /= 2.0;
        int count = 0;
        while (sum > 0)
        {
            double t = bigHeap.top() / 2.0; bigHeap.pop();
            sum -= t;
            bigHeap.push(t);
            count++;
        }
        return count;
    }
};