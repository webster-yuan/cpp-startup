//https://leetcode.cn/problems/knight-probability-in-chessboard/description/
//八个方向都可以走，走k次还在棋盘上就代表存活，返回存活的概率
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
    vector<vector<vector<double>>>memo;
public:
    double knightProbability(int n, int k, int row, int column) 
    {
        memo = vector<vector<vector<double>>>(n,vector<vector<double>>(n,vector<double>(k+1,-1)));
        return f(n, row, column, k);
    }
    int dx[8] = {2,1,2,1,-2,-2,-1,-1};
    int dy[8] = {1,2,-1,-2,1,-1,2,-2};
    double f(int n, int i, int j, int k)
    {
        if (i < 0 || i >= n || j < 0 || j >= n)
            return 0;
        if (memo[i][j][k] != -1)
            return memo[i][j][k];

        double ans = 0;
        if (k == 0)
            return 1;
        else
        {
            for (int z = 0; z < 8; z++)
            {
                int x = i + dx[z], y = j + dy[z];
                ans += f(n, x, y, k - 1)/8;
            }
        }        
        memo[i][j][k] = ans;
        return ans;
    }
};