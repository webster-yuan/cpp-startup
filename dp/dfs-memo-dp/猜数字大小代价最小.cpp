#include<iostream>
#include<vector>
using namespace std;

//https://leetcode.cn/problems/guess-number-higher-or-lower-ii/
class Solution1
{
public:
    //思路: 策略的选择,在所有策略的最多花费中选择最小的那个返回.策略:就是选中一个作为开始,根据大小提示,分为左右区间,继续往下选
    //      我们想要的是最小现金数,不是最小查找次数所以不一定是二分查找.所以要来一遍暴搜
    //dfs子问题,决策树: 1.1 在 1~n 区间内选择一个数i作为根节点,告知大小之后,再在分出来的那部分再选择一个数作为节点.
    //      返回胜利的最小代价可能是任意数字为头的策略; 在左右子树中选择较大代价作为以i为节点的返回值.
    //      保证左右子树都能够完成.
    //      1.2 每次到一个节点,都需要在给定区间内选择一个作为此时的节点,然后再相信dfs能够将左右区间中最小开销返回,
    //          我再选择二者中较大的加上我就是保证胜利最大代价,
    //dfs的返回值: 在1~n 区间内的最小代价,所以我们在以i为头选中的策略返回至少代价之后,还需要记录所有策略的最小代价
    int getMoneyAmount(int n)
    {
        int ret = dfs(1, n);
        return ret;
    }
    int dfs(int left, int right)
    {
        if (left >= right)//说明到达叶子结点,直接猜出来的了,所以不需要支付钱
            return 0;

        int ret = INT_MAX;
        for (int i = left; i <= right; i++)
        {
            //1~i-1, i+1 right
            int x = dfs(left, i - 1);
            int y = dfs(i + 1, right);
            int minCost = i + max(x, y);

            ret = min(ret, minCost);
        }
        return ret;
    }
};

//在1~n之间选中某一个节点为头有大量的重复计算,所以可以改为记忆化搜索
//因为有两个可变参数,所以使用二维表
class Solution2
{
    int memo[202][202];
public:
    int getMoneyAmount(int n)
    {
        int ret = dfs(1, n);
        return ret;
    }
    int dfs(int left, int right)
    {
        if (memo[left][right] != 0)
            return memo[left][right];

        if (left >= right)//说明到达叶子结点,直接猜出来的了,所以不需要支付钱
        {
            memo[left][right] = 0;
            return memo[left][right];
        }

        int ret = INT_MAX;
        for (int i = left; i <= right; i++)
        {
            //1~i-1, i+1 right
            int x = dfs(left, i - 1);
            int y = dfs(i + 1, right);
            ret = min(ret, i + max(x, y));
        }
        memo[left][right] = ret;
        return memo[left][right];
    }
};