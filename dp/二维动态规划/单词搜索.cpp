//https://leetcode.cn/problems/word-search/description/
#include<iostream>
#include<vector>
using namespace std;
//子问题,决策树: 到达(i,j)位置,遍历四种方向,尝试去匹配word的index位置字符,选中一个之后,
// 相信dfs()能够在选中这个位置的基础上,依次找到所有匹配的字符串,返回值是bool,
// false代表选中的这个不行,true代表匹配word成功.
//所有节点作为起点(i,j)都遍历了一遍,从第一个字符相同的位置开始匹配,在还没true时即为false.
//递归出口:按照合法的方向找,找到word结尾就算找成功了
//剪枝: 看选中的下一个位置和word[index]是否匹配,不匹配的就没必要往下走了;
//注意: 不能回头找,所以用二维矩阵visited标记,某一个节点是否在这条路中已经用过了||修改原始矩阵的值
//回溯: 恢复现场.
//在查找4个方向时,避免重复进入,可以使用visi数组标记,或者使用更改原数组值的方式

//此题决定返回值的不止这三个下标,https://www.bilibili.com/video/BV1WQ4y1W7d1?t=3377.6
//还可能是由这个二维表状态的变化决定的,而我们无法用可变参数的二维表存储这个无线的变化,所以无法更改为dp
//所以这种题数据量很小,比如这个题1<n,m<7,直接暴力展开即可.
class Solution 
{
    int n, m;
    bool visi[7][7];
public:
    bool exist(vector<vector<char>>& board, string word) 
    {
        n = board.size(), m = board[0].size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == word[0])//找到第一个字符匹配的,剪枝
                {
                    visi[i][j] = true;
                    if (dfs(board, i, j, word, 1))
                        return true;
                    visi[i][j] = false;//恢复现场,代表从他开始没好!
                }
            }
        }
        return false;
    }
    int dx[4] = { 0,0,1,-1 };
    int dy [4] = {1,-1,0,0};
    bool dfs(vector<vector<char>>& board, int i, int j, string word, int index)
    {
        if (index == word.size())
            return true;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dx[k], y = j + dy[k];
            if (x < n && x >= 0 && y < m && y >= 0 && !visi[x][y] && board[x][y] == word[index])
            {
                visi[x][y] = true;
                if (dfs(board, x, y, word, index + 1))
                    return true;
                visi[x][y] = false;
            }
        }
        return false;
    }
};