//https://leetcode.cn/problems/minimum-path-sum/
#include<iostream>
#include<vector>
using namespace std;
//dfs: 考虑(i,j)位置最近的一次操作,
//子问题: i,j位置可能是从上,左来到这个位置的,
// 相信dfs函数能够在我给定这两个选择之后,返回到达我的最小路径和,
// 然后我加上自己就是最小路径和.
//所以在返回的时候别忘了把自己加上再返回
//到达(i,j)位置的路径有很多,每次来都会把dfs(i,j)重复计算,所以可以升级为记忆化搜索
//达到剪枝的目的
//使用dp方式,分析严格位置依赖,(i,j)位置依赖于左侧和上方两个数据,所以填表顺序是从左上往右下
// 两种考虑模式: 
// 一: 
//初始化: 因为第一行,第一列只有一个方向的选择,所以需要将dp[0][j].dp[i][0]进行初始化,
//但是也可以将这两列放到后序整体中一起计算,所以需要多开一行,多开一列,
//根据题意分析,放入后序后,只需要将此时多出来的一行一列全部初始化为INT_MAX,dp[0][1]或者dp[1][0]=0
//使得后序计算能够取到grid[0][0]值即可
//但是访问原数组时要注意下标-1.返回值就是dp[n][m]
//二: 
//由memo改进而来,分析位置依赖,(i,j)位置依赖于左和上,所以先填左再填右
//返回值是dp[n-1][m-1],所以dp[n][m]
//初始化dp[0][0]=grid[0][0],老实初始化第一行,第一列

//两个可变参数可以决定返回值,所以可以更改为dp
class Solution1
{
    int n, m;
    vector<vector<int>>memo;
public:
    int minPathSum1(vector<vector<int>>& grid)
    {
        n = grid.size(), m = grid[0].size();
        memo = vector<vector<int>>(n, vector<int>(m));
        return dfs(grid, n-1, m-1);
    }
    int dfs(vector<vector<int>>& grid, int i, int j)
    {
        if (memo[i][j])
            return memo[i][j];

        //出口: 当(i,j)位置到达最开始的点(0,0)
        if (i == 0 && j == 0)
        {
            memo[i][j] = grid[0][0];
            return memo[i][j];
        }
        int p1 = INT_MAX, p2 = INT_MAX;
        if (i - 1 >= 0)
            p1 = dfs(grid, i - 1, j);
        if (j - 1 >= 0)
            p2 = dfs(grid, i, j - 1);
        memo[i][j] = min(p1, p2) + grid[i][j];
        return memo[i][j];
    }
};
class Solution2
{
    //------------
//dp1
public:
    int minPathSum2(vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>>dp(n + 1, vector<int>(m + 1, INT_MAX));
        dp[0][1] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
            }
        }
        return dp[n][m];
    }
    //dp2
    int minPathSum3(vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>>dp(n, vector<int>(m));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < n; i++)
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        for (int j = 1; j < m; j++)
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[n - 1][m - 1];
    }
    //空间压缩https://www.bilibili.com/video/BV1WQ4y1W7d1?t=1996.4
    int minPathSum4(vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<int>dp(m);
        dp[0] = grid[0][0];
        for (int j = 1; j < m; j++)
            dp[j] = dp[j - 1] + grid[0][j];
        for (int i = 1; i < n; i++)
        {
            // i = 1，dp表变成想象中二维表的第1行的数据
            // i = 2，dp表变成想象中二维表的第2行的数据
            // i = 3，dp表变成想象中二维表的第3行的数据
            // ...
            // i = n-1，dp表变成想象中二维表的第n-1行的数据
            dp[0] = dp[0] + grid[i][0];//每一行开头自我更新
            for (int j = 1; j < m; j++)
            {
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1];
    }
};