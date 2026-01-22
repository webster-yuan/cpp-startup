//https://leetcode.cn/problems/target-sum/description/
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

//解法1:
//使用暴力尝试的方式,遇到一个数无非就是+或者是-
// -------------数据量小可以通过暴力,但是时间是 1000ms左右
class Solution11 //
{
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int ret = dfs(nums, target, 0, 0);
        return ret;
    }
    int dfs(vector<int>& nums, int target, int index, int path)
    {
        if (index == nums.size())
            return path == target ? 1 : 0;
        return dfs(nums, target, index + 1, path - nums[index])
            + dfs(nums, target, index + 1, path + nums[index]);
    }
};


//解法2:
//尝试使用记忆化搜索记录,但是可能path存在是负数的情况,所以只能使用哈希表进行记录
//由于本题i>=0,sum(j)可能小于0,所以sum的记录使用哈希表记录
// 2.1 vector<unordered_map<int, int>>memo; i是直接O(1)级别查找
// 2.2 unordered_map<int,unordered_map<int, int>>memo i也是O(logn)级别查找
// -------------T(N) 差不多在200~300ms左右
class Solution12_1
{
    vector<unordered_map<int, int>>memo;//i用vector记录,j用unordered_map记录
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int n = nums.size();
        memo = vector<unordered_map<int, int>>(n);
        int ret = dfs(nums, target, 0, 0);
        return ret;
    }
    int dfs(vector<int>& nums, int target, int i, int path)
    {
        if (i == nums.size())
            return path == target ? 1 : 0;
        if (!memo[i].empty() && memo[i].count(path)!=0)//vector<i>位置有东西 && path记录过(才会有插入的节点,无论0 or 1)
            return memo[i][path];
        int ret= dfs(nums, target, i + 1, path + nums[i]) + dfs(nums, target, i + 1, path - nums[i]);
        memo[i].insert({ path,ret });
        return ret;
    }
};
class Solution12_2
{
    unordered_map<int,unordered_map<int, int>>memo;//i用vector记录,j用unordered_map记录
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int n = nums.size();
        int ret = dfs(nums, target, 0, 0);
        return ret;
    }
    int dfs(vector<int>& nums, int target, int i, int path)
    {
        if (i == nums.size())
            return path == target ? 1 : 0;
        if (memo.count(i)!=0 && memo[i].count(path)!=0)
            return memo[i][path];
        int ret = dfs(nums, target, i + 1, path + nums[i]) + dfs(nums, target, i + 1, path - nums[i]);
        if (memo.count(i) == 0)
            memo.insert({ i, unordered_map<int, int>() });
        memo[i].insert({ path,ret });
        return ret;
    }
};



//解法3:
//想分析严格的位置依赖,但是呢由于sum可能是负数导致二维表j有负数肯定存不了,
//所以可以位置平移的方式进行存储即可
//https://www.bilibili.com/video/BV1NN41137jF?t=2953.4
//分析: 
//sum最大值就是所有数字都是负数即a,最小值就是所有数字都是负数即b,那么二维表中[i][j]
//j: b<=j<=a,由于左半部分都是负数,那么我们实际用表的时候就向右平移,保证左半部分都>=0即可 ---  1 
//都平移a个单位即可,[0...n][0...2*a],[j]->[j+a]位置存储
//i是能够取到n的,所以空间需要是n+1,j取到target是有意义的,所以空间在保证为正时要开辟2*sum+1空间的
//注意初始化: sum==target时是一种方式,1
//填表顺序: 依赖于i+1,所以从下网上,j的取值是-sum~+sum,此时就要注意下标的偏移了,方向无所谓
//返回值 : dp[0][0]->dp[0][sum]
//T(N): 80ms左右  内存是22MB
class Solution13_1
{
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int sum = 0;
        for (int e : nums)
            sum += e;
        //特判: 增大效率
        if (target<-sum || target>sum)
            return 0;
        int offset = sum;//1

        int n = nums.size();
        int maxSum = sum + offset;          //注意与开辟空间的区分
        vector<vector<int>>dp(n + 1, vector<int>(maxSum + 1));
        //dp[n + 1][target] = 1;
        dp[n][target + offset] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = -offset; j <= offset; j++)
            {
                if (j + offset + nums[i] <= maxSum)//注意取值范围,maxSum是能够取到的
                {
                    //dp[i][j]=dp[i+1][j+nums[i]];
                    dp[i][j + offset] = dp[i + 1][j + offset + nums[i]];
                }
                if (j + offset - nums[i] >= 0)
                {
                    dp[i][j + offset] += dp[i + 1][j + offset - nums[i]];
                }
            }
        }
        return dp[0][offset];
    }
};
//可能不是最右侧的值,也可能是最左侧的值,那么无法空间压缩,因为无论从那头开始,都会导致另一侧的值被覆盖
//所以需要使用滚动数组存储下一行的数据,然后寻求更新上一行
class Solution13_2
{
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int sum = 0;
        for (int e : nums)
            sum += e;
        if (target<-sum || target>sum)
            return 0;
        int offset = sum;
        int n = nums.size();
        int maxSum = sum + offset;
        vector<int> dp(maxSum + 1);
        dp[target + offset] = 1;
        for (int i = n - 1; i >= 0; i--) 
        {
            vector<int> next(maxSum+ 1);
            for (int j = -offset; j <= offset; j++)
            {
                if (j + offset + nums[i] <= maxSum)
                {
                    next[j + offset] += dp[j + offset + nums[i]];
                }
                if (j + offset - nums[i] >= 0)
                {
                    next[j + offset] += dp[j + offset - nums[i]];
                }
            }
            dp = next;
        }
        return dp[offset];
    }
};


//解法4
// 新思路，转化为01背包问题
// 思考1:
// 虽然题目说nums是非负数组，但即使nums中有负数比如[3,-4,2]
// 因为能在每个数前面用+或者-号
// 所以[3,-4,2]其实和[3,4,2]会达成一样的结果
// 所以即使nums中有负数，也可以把负数直接变成正数，也不会影响结果
// 思考2:
// 如果nums都是非负数，并且所有数的累加和是sum
// 那么如果target>sum，很明显没有任何方法可以达到target，可以直接返回0
// 思考3:
// nums内部的数组，不管怎么+和-，最终的结果都一定不会改变奇偶性
// 所以，如果所有数的累加和是sum，并且与target的奇偶性不一样
// 那么没有任何方法可以达到target，可以直接返回0
// 思考4(最重要):
// 比如说给定一个数组, nums = [1, 2, 3, 4, 5] 并且 target = 3
// 其中一个方案是 : +1 -2 +3 -4 +5 = 3
// 该方案中取了正的集合为A = {1，3，5}
// 该方案中取了负的集合为B = {2，4}
// 所以任何一种方案，都一定有 sum(A) - sum(B) = target
// 现在我们来处理一下这个等式，把左右两边都加上sum(A) + sum(B)，那么就会变成如下：
// sum(A) - sum(B) + sum(A) + sum(B) = target + sum(A) + sum(B)
// 2 * sum(A) = target + 数组所有数的累加和
// sum(A) = (target + 数组所有数的累加和) / 2
// 也就是说，任何一个集合，只要累加和是(target + 数组所有数的累加和) / 2
// 那么就一定对应一种target的方式
// 比如非负数组nums，target = 1, nums所有数累加和是11
// 求有多少方法组成1，其实就是求，有多少种子集累加和达到6的方法，(1+11)/2=6
// 因为，子集累加和6 - 另一半的子集累加和5 = 1（target)
// 所以有多少个累加和为6的不同集合，就代表有多少个target==1的表达式数量
// 至此已经转化为01背包问题了


class Solution14
{
public:
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int sum = 0;
        for (int n : nums)
            sum += n;
        if (sum < target || ((target & 1) ^ (sum & 1)) == 1)
            return 0;
        return func(nums, (target + sum) >> 1);
    }
    // 求非负数组nums有多少个子序列累加和是t
    // 01背包问题(子集累加和严格是t) + 空间压缩
    // dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]]
    int func(vector<int>& nums, int t)
    {
        if (t < 0)
            return 0;
        vector<int>dp(t + 1);
        dp[0] = 1;//多少个子序列的累加和是0,0个就是空集,也是一种做法,所以填写1
        for (int num : nums)
        {
            for (int j = t; j >= num; j--)//依赖的是左侧,为了避免左侧被覆盖,所以从右侧开始更新
            {
                dp[j] += dp[j - num];
            }
        }
        return dp[t];
    }
};