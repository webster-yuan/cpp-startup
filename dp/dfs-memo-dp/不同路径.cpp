#include<iostream>
#include<vector>
using namespace std;
//https://leetcode.cn/problems/unique-paths/submissions/
class Solution1
{
    int m;
    int n;
public:
    int uniquePaths(int _m, int _n)
    {
        m = _m, n = _n;
        return dfs(0, 0);
    }
    int dfs(int row, int col)
    {
        if (row == m - 1 && col == n - 1)
        {
            return 1;
        }
        int ret = 0;
        if (row + 1 < m)
            ret += dfs(row + 1, col);
        if (col + 1 < n)
            ret += dfs(row, col + 1);
        return ret;
    }
};
class Solution2
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n));
        //初始化第一行和第一列
        for (int i = 0; i < m; i++)
            dp[i][0] = 1;
        for (int i = 0; i < n; i++)
            dp[0][i] = 1;
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
//动归优化:多加一行,多加一列,这样可以将冗余的第一行第一列的初始化融入到后续循环代码中
//经分析,想要第一行第一列按规则都为1,则在dp[0][1]=1即可
class Solution3
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        //初始化第一行和第一列
        dp[0][1] = 1;
        for (int i = 1; i <=m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m][n];
    }
};
//int main()
//{
//    Solution1 s1;
//    Solution2 s2;
//    Solution3 s3;
//    cout << (s1.uniquePaths(23, 12) == s2.uniquePaths(23, 12)&&s1.uniquePaths(23,12)==s3.uniquePaths(23,12));
//    //由于暴力递归效率低,所以你多等一会发现结果都是对的.
//}