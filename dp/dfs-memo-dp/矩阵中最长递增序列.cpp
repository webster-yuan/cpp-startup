#include<iostream>
#include<vector>
using namespace std;
//https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/submissions/
class Solution
{
    int m, n;
    int next[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
    int memo[201][201];
public:
    //思路:遍历矩阵,选中一个作为起点,dfs()去走四个方向,统计累加和,记录以每一个节点为头的大值
    //子问题,决策树: 以i,j位置为起点,互斥的往4个方向寻找递增路径,并且要将最大值记录并返回,ret=max(ret,dfs())
    //函数头: 首先dfs的意义是将以i,j为起始点的最长路径返回,所以有int 返回值
    //出口: 所有都找完,所以没出口
    //剪枝: 没有剪枝,如果能改为记忆化搜索,就作为剪枝,将已经作为头遍历过得值直接返回
    //回溯:没有回溯,都是一往无前的往前走
    int longestIncreasingPath(vector<vector<int>>& matrix)
    {
        m = matrix.size(), n = matrix[0].size();
        int ret = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int count = dfs(matrix, i, j);
                ret = max(ret, count);
            }
        }
        return ret;
    }
    //返回值: 以i,j为起点的最长递增路径的长度.
    //对于每一个节点都需要比较出四个方向的最大长度,至少是自己本身,所以最小返回值也是1
    int dfs(vector<vector<int>>& matrix, int i, int j)
    {
        if (memo[i][j] != 0) return memo[i][j];

        int ret = 1;
        for (int k = 0; k < 4; k++)
        {
            int x = i + next[k][0], y = j + next[k][1];
            if (x < m && x >= 0 && y<n && y >= 0 && matrix[x][y]>matrix[i][j])
            {
                ret = max(ret, dfs(matrix, x, y) + 1);
            }
        }
        memo[i][j] = ret;
        return memo[i][j];
    }
};