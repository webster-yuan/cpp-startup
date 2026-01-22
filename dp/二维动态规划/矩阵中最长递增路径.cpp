//https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/
#include<iostream>
#include<vector>
using namespace std;
//思路:遍历矩阵,选中一个作为起点,dfs()去走四个方向,统计累加和,记录以每一个节点为头的最大值
//子问题,决策树: 以i,j位置为起点,互斥的往4个方向寻找递增路径,并且要将最大值记录并返回,ret=max(ret,dfs())
//函数头: 首先dfs的意义是将以i,j为起始点的最长路径返回,所以有int 返回值
//出口: 所有都找完,所以没出口
//剪枝: 没有剪枝,如果能改为记忆化搜索,就作为剪枝,将已经作为头遍历过得值直接返回
//回溯:没有回溯,都是一往无前的往前走
class Solution 
{
    int n, m;
    vector<vector<int>>memo;
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        n = matrix.size(), m = matrix[0].size();
        memo = vector<vector<int>>(n+1,vector<int>(m+1));
        int ret = 0;
        for (int i = 0; i < n; i++)
        {
            for(int j=0;j<m;j++)
            {
                int count = dfs(matrix, i, j);
                ret = max(ret, count);
            }
        }
        return ret;
    }
    int dx[4] = { -1,1,0,0 };
    int dy[4] = { 0,0,-1,1 };
    int dfs(vector<vector<int>>& matrix, int i, int j) 
    {
        if (memo[i][j] != 0)
            return memo[i][j];
        int ret = 1;//最小长度就是自身,初始化应该是1
        for (int k = 0; k < 4; k++)
        {
            int x = dx[k] + i, y = dy[k] + j;
            if (x < n && x >= 0 && y<m && y >= 0 && matrix[x][y]>matrix[i][j])
            {
                ret = max(ret, dfs(matrix, x, y) + 1);//记录i,j开始四个方向中加上自己之后的最大长度
            }
        }
        memo[i][j] = ret;
        return ret;
    }
};