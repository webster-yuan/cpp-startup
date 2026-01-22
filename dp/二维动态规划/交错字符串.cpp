//https://leetcode.cn/problems/interleaving-string/
// s3的长度肯定是s1和s2长度相加的和,如果不是就返回false
//dp[i][j]表示s1前i个字符,和s2前j个字符,组成s3的前i+j个字符,能否达成
//只讨论s3最后一个字符来自于s1还是s2,
//dp[i][j]=dp[i-1][j] || dp[i][j-1],||就是选择其中一个即可
//初始化: 涉及到i-1 j-1 那么就多开一行多开一列
// 1. 注意将新开辟的空间初始化,
//  第0行代表s1取0个字符,
//  第0列代表s2取0个字符,
// 只需要判断是否都对应相等,相等就是true,只要出现一个位置不同,后序都是false
// 2. 访问原字符串时注意下标-1,或者将原字符串首位置加个" "
//填表顺序: 依赖上和左,从左往右,从上往下
//返回值: dp[n][m]
#include<iostream>
#include<vector>
using namespace std;
class Solution34 
{
public:
    bool isInterleave(string s1, string s2, string s3) 
    {
        int n = s1.size(), m = s2.size();
        if ((n + m) != s3.size())
            return false;
        s1 = " " + s1;
        s2 = " " + s2;
        s3 = " " + s3;
        vector<vector<bool>>dp(n + 1, vector<bool>(m + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; i++)
        {
            if (s1[i] == s3[i])
                dp[i][0] = true;
            else
                break;
        }
        for (int j = 1; j <= m; j++)
        {
            if (s2[j] == s3[j])
                dp[0][j] = true;
            else
                break;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = (s1[i] == s3[i + j] && dp[i - 1][j]) || (s2[j] == s3[i + j] && dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }
};
//空间压缩: 依赖于上和左,为了避免左侧被覆盖,所以采用从右往左的方式去更新数组
//因为在原字符串中修改值,会造成效率的降低,所以我们就直接使用下标访问,只不过注意一下-1即可
class Solution35
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n = s1.size(), m = s2.size();
        if (n + m != s3.size())
            return false;
        vector<bool>dp(m + 1);
        dp[0] = true;
        for (int j = 1; j <= m; j++)
        {
            if (s2[j-1] == s3[j-1])
                dp[j] = true;
            else
                break;
        }
        for (int i = 1; i <= n; i++)
        {
            dp[0] = s1[i - 1] == s3[i - 1] && dp[0];
            for (int j = 1; j <=m; j++)
            {
                dp[j] = (s1[i - 1] == s3[i + j - 1] && dp[j]) || (s2[j - 1] == s3[i + j - 1] && dp[j - 1]);
            }
        }
        return dp[m];
    }
};