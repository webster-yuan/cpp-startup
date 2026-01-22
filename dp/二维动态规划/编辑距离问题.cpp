//https://leetcode.cn/problems/edit-distance
//dp[i][j]代表s1[前缀i个]完全变为s2[前缀j个]的最小代价是多少
//https://www.bilibili.com/video/BV1cg4y1o719?t=1655.1
//初始化: 多开一行多开一列的方式
//  1. 新开出的空间需要初始化保证后续计算正确,第0行代表s1为空时,空依次变成s2的代价就是依次增加就行,dp[0][j]=j*新增
//              第0列,代表s2为空时,不空变为空的代价就是依次删除呗 ,dp[i][0]=i*删除的代价
//dp[0][0]完全不需要动,就是0.
// 2. 访问原字符串的时候需要注意下标-1
//返回值: 就是s1[前n个]完全变化为s2[前m个]的最小代价
//填表顺序,依赖于左和上,所以-> 上到下

//做一个小贪心: 就是如果最后一个位置二者相同,就直接使用s[i]位置即可,就不需要考虑舍弃s[i]字符了
#include<iostream>
#include<vector>
using namespace std;
class Solution31 
{
public:
    int minDistance(string s1, string s2)
    {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
            dp[i][0] = i;
        for (int j = 1; j <= m; j++)
            dp[0][j] = j;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                {
                    int p1 = dp[i - 1][j] + 1;//删除s[i]位置
                    int p2 = dp[i][j - 1] + 1;//新增
                    int p3 = dp[i - 1][j-1]+1;//替换s[i]位置
                    dp[i][j] = min(p1, min(p2, p3));
                }
            }
        }
        return dp[n][m];
    }
};
//空间压缩:从左往右填表,注意leftUp即可
//题意特殊,注意初始化
class Solution32
{
public:
    int minDistance(string s1, string s2)
    {
        int n = s1.size(), m = s2.size();
        vector<int>dp(m + 1);
        for (int i = 1; i <= m; i++)
            dp[i] = i;//代表的是新增代价
        int leftUp = 0, backUp = 0;
        for (int i = 1; i <= n; i++)
        {
            leftUp = (i - 1) * 1;//代表删除代价是1
            dp[0] = i * 1;//删除代价
            for (int j = 1; j <=m; j++)
            {
                backUp = dp[j];
                if (s1[i - 1] == s2[j - 1])
                    dp[j] = leftUp;
                else
                {
                    int p1 = dp[j]+1;//删除,使用dp[i-1][j],也就是前一行的数据,一维数组中就是本地且未更新的数值
                    int p2 = dp[j - 1] + 1;//新增,使用dp[i][j-1],也就是这一行,前一列的数据,
                    int p3 = leftUp + 1;//替换,使用dp[i-1][j-1],也就是左上的值
                    dp[j] = min(p1, min(p2, p3));
                }
                leftUp = backUp;
            }
        }
        return dp[m];
    }
};
//当新增,删除,替换代价具体化时,如下代码
class Solution33 {
public:
    int minDistance(string word1, string word2) {
        return minDistance2(word1, word2, 1, 1, 1);
    }
    int minDistance2(string s1, string s2, int a, int d, int r)
    {
        int m = s1.size(), n = s2.size();
        vector<int>dp(n + 1);
        for (int i = 1; i <= n; i++)
            dp[i] = i * a;
        for (int i = 1; i <= m; i++)
        {
            int prev = dp[0];
            dp[0] = d * i;
            for (int j = 1; j <= n; j++)
            {
                int tmp = dp[j];//原本上一行的dp[i-1][j]
                if (s1[i - 1] == s2[j - 1])
                    dp[j] = prev;
                else
                {

                    int p1 = dp[j - 1] + a;
                    int p2 = dp[j] + d;
                    int p3 = prev + r;
                    dp[j] = min(p1, min(p2, p3));
                }
                prev = tmp;
            }
        }
        return dp[n];
    }
};