#include<iostream>
#include<vector>
using namespace std;
class Solution1//以i,j位置为起点走暴力递归
{
    int m, n;
    int ret;
public:
    int maxValue(vector<vector<int>>& grid)
    {
        m = grid.size(), n = grid[0].size();
        dfs(0, 0, grid, grid[0][0]);
        return ret;
    }
    //以row,col位置作为起点,到达该位置之间,如果那个位置是合法的,已经将那个位置的值加上了
    void dfs(int row, int col, vector<vector<int>>& grid, int path)
    {
        //出口:到达最后一个位置,需要更新ret最大值
        if (row == m - 1 && col == n - 1)
        {
            ret = max(ret, path);
            return;
        }
        if (row + 1 < m) dfs(row + 1, col, grid, path + grid[row + 1][col]);
        if (col + 1 < n) dfs(row, col + 1, grid, path + grid[row][col + 1]);
    }
};
class Solution2//以i,j位置为终点走暴力递归
{
    int m;
    int n;
public:
    //dp[i][j]以ij位置为结尾,到达ij位置时的最大价值
    int maxValue(vector<vector<int>>& grid)
    {
        m = grid.size(), n = grid[0].size();
        return zuo(m - 1, n - 1, grid);
    }
    //返回值是到达xy时的最大价值
    int zuo(int x, int y, vector<vector<int>>& grid)
    {
        if (x == 0 && y == 0)
        {
            return grid[0][0];
        }
        int p1 = 0, p2 = 0;
        if (x > 0)
            p1 = zuo(x - 1, y, grid);
        if (y > 0)
            p2 = zuo(x, y - 1, grid);
        return grid[x][y] + max(p1, p2);
    }
};
class Solution3 
{
    int m;
    int n;
public:
    //dp[i][j]以ij位置为结尾,到达ij位置时的最大价值
    //dp[i][j]=max(dp[i-1][j],dp[i][j-1])
    //优化:多加一行,多加一列
    //注意:1. 初始化位置,使得不影响后续,多加的都是0就行 2. 往回找grid时注意下标变换
    int maxValue(vector<vector<int>>& grid)
    {
        m = grid.size(), n = grid[0].size();
        vector<vector<int>>dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = grid[i - 1][j - 1] + max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};