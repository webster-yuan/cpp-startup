
//https://leetcode.cn/problems/longest-increasing-subsequence/description/
//最长递增子序列
//解法一: 使用dp的方式
// dp[i]代表以i位置为结尾时最长递增子序列的长度
// dp[i]=max(dp[i],dp[j]+1) j属于[0,i-1]位置
// 初始化时都是1
class Solution9 
{
public:
    int lengthOfLIS(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int>dp(n, 1);
        int ret = 1;//长度问题老实初始化为1
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            ret = max(ret, dp[i]);
        }
        return ret;
    }
};
//解法二: 二分查找的方式
//----只能把点数小的牌压到点数比它大的牌上；
//如果当前牌点数较大没有可以放置的堆，则新建一个堆，把这张牌放进去；
//如果当前牌有多个堆可供选择，则选择最左边的那一堆放置。
//最后,有多少个堆,最长的子序列就是多少长度
//那么在遍历到index位置,将这个数字放到哪个堆上就涉及到二分查找
#include<iostream>
#include<vector>
using namespace std;
class Solution1
{
public:
    //二分时区间划分为top[mid] < >= poker,>=都是满足的,查找的是右区间最左边界
    int lengthOfLIS1(vector<int>& nums) 
    {
        int piles = 0;
        int n = nums.size();
        vector<int>top(n);//记录的是每一堆中最上面一层的元素
        for (int i = 0; i < n; i++)
        {
            int poker = nums[i];
            int left = 0, right = piles;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (top[mid] >= poker)
                    right = mid;
                else left = mid + 1;
            }
            if (left == piles)
                piles++;
            top[left] = poker;
        }
        return piles;
    }
    int lengthOfLIS(vector<int>& nums)
    {
        int piles = 0;
        int n = nums.size();
        vector<int>top(n);
        for (int i = 0; i < n; i++)
        {
            int poker = nums[i];
            int left = 0, right = piles;
            int index = piles;//如果没有查找到合适位置,也就是一直没有做出更新.初始化不得随意
            while (left <= right)
            {
                int mid = (left + right) / 2;
                if (top[mid] >= poker)
                {
                    index = mid;
                    right = mid - 1;
                }
                else
                    left = mid + 1;
            }
            if (index == piles)
                piles++;
            top[index] = poker;
        }
        return piles;
    }
};
//解法三:
// 贪心解法
//dp时我们只用考虑i的前一个位置是谁,也就是j即可,不需要再考虑j之前的元素是什么.
//二分的时候因为我们记录了一个top数组,top[index]只记录了这个堆中最小值,并且最后的答案是一共有几堆
//贪心是结合以上两点,
//因为是形成递增子序列,0位置直接作为长度为1 [len=1]的最后一个元素,
// if [index] < [len=1],****贪心1: 直接替换,[len=1] =[index],所有len=x的所有元素最小值
// 后面出现的数字既然能够放到更小的数后面,肯定是更好的.所以是正确的,交换论证法.
// else if [index]>[len=1],可以自己形成另一个一个长度为1的子序列,也可以连在之前的后面,
// 说明是可以放在len=1的子序列的后面,形成长度为2的子序列,
// ****贪心2: 两种选择中,放在之前的那个子序列的后面,形成更长的子序列,因为想要的就是长度更长,
// 那么最后一个元素就是[len=2]=[index]
// ...,形成长度为3,4,5的子序列,最后返回[len]即可.
// 和top数组分成几堆是一样的,但是拼接的序列并不是那个最长的,只是长度确实是相同的.
//使用数组记录len=index时的最小值,数组中因为上述规则导致是递增的,(根据形成规则 直接证明法)
// 所以可以使用二分优化,查找的是>=的最左边界
class Solution 
{
public:
    int lengthOfLIS(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int>ret;
        ret.push_back(nums[0]);
        for (int i = 1; i < n; i++)
        {
            if (nums[i] > ret.back())//比他大,那就选择连在他后面,形成len+1的子序列,结尾就是nums[i]
                ret.push_back(nums[i]);
            else//比他小,覆盖他
            {
                int left = 0, right = ret.size() - 1;//-1 or not都无所谓
                while (left < right)
                {
                    int mid = (left + right) / 2;
                    if (ret[mid] < nums[i])left = mid + 1;
                    else right = mid;
                }
                ret[left] = nums[i];
            }
        }
        return ret.size();
    }
};
//int main()
//{
//    vector<int>arr{ 10,9,2,5,3,7,101,18 };
//    Solution1 s;
//    cout<<s.lengthOfLIS(arr);
//}