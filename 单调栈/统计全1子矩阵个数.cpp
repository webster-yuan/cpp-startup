
//https://leetcode.cn/problems/count-submatrices-with-all-ones/
//先得到一维矩阵中必须以他为底的矩阵的个数
//如果存在重复值: https://www.bilibili.com/video/BV1GH4y1D7TB?t=5029.8
//  因为相等弹出栈顶的不算个数,等到后面相等值弹出时统一算就能把之前的所有丢失的都找回来
//矩形个数怎么算呢? 1 2 3 能形成6个组合就是3*(3+1)/2,
//所以同理m*n的矩阵,能形成的矩形个数就是 (m*(m+1)/2)*n
//https://github.com/algorithmzuo/algorithm-journey/blob/main/src/class053/Code04_CountSubmatricesWithAllOnes.java
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
    vector<int>st;
    vector<int>tmp;
public:
    int numSubmat(vector<vector<int>>& mat)
    {
        int n = mat.size(), m = mat[0].size();
        st = vector<int>(m);
        tmp = vector<int>(m);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                tmp[j] = mat[i][j] == 0 ? 0 : tmp[j] + 1;
            ans += countFromBottom(m);
        }
        return ans;
    }
    //必须以某一行为底时能够数出来多少个矩形
    int countFromBottom(int m)
    {
        int r = 0;
        int left = 0, len = 0, bottom = 0;
        int ans = 0;
        for (int i = 0; i <m; i++)
        {
            while (r > 0 && tmp[i] <= tmp[st[r - 1]])//等于也弹出
            {
                int cur = st[--r];
                if (tmp[cur] != tmp[i])
                {
                    //只有严格大于的时候再算个数
                    left = r > 0 ? st[r - 1] : -1;
                    len = i - left - 1;
                    bottom = max(left == -1 ? 0 : tmp[left], tmp[i]);
                    ans += (tmp[cur] - bottom) * len * (len + 1) / 2;
                }
            }
            st[r++] = i;
        }
        while (r > 0)
        {
            int cur = st[--r];
            left = r > 0 ? st[r - 1] : -1;
            len = m - left - 1;
            int down = left == -1 ? 0 : tmp[left];
            ans += (tmp[cur] - down) * len * (len + 1) / 2;
        }
        return ans;
    }
};