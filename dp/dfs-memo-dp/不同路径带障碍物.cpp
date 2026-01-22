#include<iostream>
#include<vector>
using namespace std;
//https://leetcode.cn/problems/unique-paths-ii/submissions/
class Solution1
{
    int m;
    int n;
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        m = obstacleGrid.size(), n = obstacleGrid[0].size();
        return dfs(obstacleGrid, 0, 0);
    }
    int dfs(vector<vector<int>>& grid, int row, int col)
    {
        //特殊情况:起点就是障碍那么直接返回0
        if (grid[row][col] == 1) return 0;//[[1]]

        //到达终点,说明就走了一条正确的路
        if (row == m - 1 && col == n - 1)
            return 1;
        int ret = 0;
        if (row + 1 < m && grid[row + 1][col] == 0)
            ret += dfs(grid, row + 1, col);
        if (col + 1 < n && grid[row][col + 1] == 0)
            ret += dfs(grid, row, col + 1);
        return ret;
    }
};
class Solution
{
public:
    //如果[i-1][j]或者[i][j-1]是障碍物的话,说明到从他那到我这条路是不通的是没有路径数的,dp[i][j]=0+另一个值
    int uniquePathsWithObstacles(vector<vector<int>>& ob)
    {
        //优化,多加一行多加一列
        //注意初始化dp[0][1]=1
        //注意下标变换,在访问ob原数组时
        int m = ob.size(), n = ob[0].size();
        vector<vector<int>>dp(m + 1, vector<int>(n + 1));
        dp[0][1] = 1;
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (ob[i - 1][j - 1] == 0)//如果不是从障碍物来的,说明路经是有效的
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m][n];
    }
};