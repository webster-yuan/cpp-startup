
//https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/

//和至少为K的最短子数组长度
//使用前缀和预处理方式处理数组,以index为结尾往左扩,能扩到满足条件时的最短长度
//如何处理呢? 前缀和数组preSum,区间[a,b]的和就是preSum[b]-preSum[a]的值
//前缀和数组肯定是保持单调递增的,当都是整数的时候
//要在[0,index-1]区间中找到能够让累加和>=K时,最靠右的那个值,如何获取?
//可以采用单调队列的方式,queue<Node>
//Node<index,val>,val 是preSum[index]
//当preSum>K时,依次尝试弹出左边界,时刻更新最短长度
//front位置弹出后,再也不会被使用.因为我们寻求的是最短长度,既然在此时包含他的子数组
//已经不是最短,那么之后无论再对值进行更新,包含f
// 
//当数组存在负数时,导致index位置累加和变小,要维持单调队列中从小到大的单调性就应该弹出队尾(比他大就弹出)
//然后将index,preSum[index]插入,
//解释: 如果后续数组组合sum -preSum[index]都不达标的话,那么减去比preSum[index]更大的前面的累加和
//肯定更不达标,因为index位置时负数导致preSum减小
//并且会变得更长,所以可以弹出队尾.
//等于这个preSum[index]的也应该弹出,因为我们想要的是最短的,后序数字和index位置结合肯定比和index之前的数字结合
//要更短,在累加和数值都相同的情况下
//https://www.bilibili.com/video/BV1y8411i7cY?t=1203.1
//1 <= nums.length <= 10^5
//-10^5 <= nums[i] <= 10^5
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
    int maxlen = 100001;
public:
    int shortestSubarray(vector<int>& nums, int k)
    {
        //vector<int>preSum(maxlen);//preSum[i]表示前i个数的前缀和
        vector<long long>preSum(maxlen);//preSum[i]表示前i个数的前缀和
        vector<int>myqueue(maxlen);
        int h = 0, t = 0;
        
        int n = nums.size();
        for (int i = 0; i < n; i++)
            preSum[i + 1] = nums[i] + preSum[i];
        int ans = INT_MAX;
        for (int i = 0; i <= n; i++)
        {
            // 如果当前的前缀和 - 头前缀和，达标！->记录更新最短值并弹出head
            while (h != t && preSum[i] - preSum[myqueue[h]] >= k)
                ans = min(ans, i - myqueue[h++]);
            // 减去头不达标,那么就涉及到放入队列中,保证单调性是从小到大,相等值仍然弹出
            while (h != t && preSum[myqueue[t - 1]] >= preSum[i])
                t--;
            myqueue[t++] = i;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};