#include<iostream>
#include<vector>
using namespace std;
class Solution1
{
public:
    int numDecodings(string s)
    {
        int n = s.size();
        vector<int>dp(n);
        dp[0] = s[0] == '0' ? 0 : 1;
        if (n == 1) return dp[0];
        //因为是从前往后,如果前面的那个都不满足,说明到i-1都无法转化,那么就更没必要判断i位置是否能够转化,所以要保证前一个也能转化,为了处理06 05这种不能转化的情况
        if (s[0] != '0' && s[1] != '0') dp[1] += 1;
        int t = (s[0] - '0') * 10 + s[1] - '0';
        if (t >= 10 && t <= 26)
            dp[1] += 1;
        for (int i = 2; i < n; i++)
        {
            if (s[i] != '0') dp[i] += dp[i - 1];
            int t = (s[i - 1] - '0') * 10 + s[i] - '0';
            if (t >= 10 && t <= 26)
                dp[i] += dp[i - 2];
        }
        return dp[n - 1];
    }
};
class Solution2
{
public:
    //s字符串,能解码,返回解码数,和不能解码,return 0.
    //dp[i]以i为结尾的字符串,能够得到解码的方法数.如果s[i]==0,s[i-1]和s[i]不能合并解码,那么dp[i]=0,以i结尾的字符串不能解码
    //如果能够单独解码,dp[i] += d[i-1];如果能够合并解码,dp[i]+=dp[i-2]
    //dp[i]=dp[i-1]+dp[i-2],就相当于上台阶,想上到第i阶,要么是从i-1一步上来的,要么是从i-2一次性上来的.两种方式互斥,zuo函数
    int numDecodings(string s)
    {
        int n = s.size();
        return zuo(s, n - 1);
    }
    //[0,index]能够解码的个数
    //子问题,决策树: index,1. 自己转化,2. 和前面一个结合
    int zuo(string& s, int index)
    {
        //出口:
        if (index == 0)
            return s[0] == '0' ? 0 : 1;
        if (index == 1)
        {
            int ret = 0;
            if (s[0] != '0' && s[1] != '0') ret += 1;

            int t = (s[0] - '0') * 10 + s[1] - '0';
            if (t >= 10 && t <= 26)
                ret += 1;
            return ret;
        }
        //index>=2
        int p1 = 0, p2 = 0;
        if (s[index] != '0')
            p1 = zuo(s, index - 1);
        int t = (s[index - 1] - '0') * 10 + s[index] - '0';
        if (t >= 10 && t <= 26)
            p2 = zuo(s, index - 2);
        return p1 + p2;
    }
};
class Solution3
{
public:
    int numDecodings(string s)
    {
        //发现dp[1]初始化和后续代码冗余部分,所以优化
        //多开一个空间,让原dp表中数据集体向后挪动一位,
        //但是要注意两点:;
        //1. 你遍历填充的是新的dp表,但是你用一样的下标判断s中字符时,下标可是要-1的
        //2. 多出来的一位就是dp[0]初始化为dp[0]=1,保证后续情况正确
        int n = s.size();
        vector<int>dp(n + 1);
        dp[0] = 1;
        dp[1] = s[0] == '0' ? 0 : 1;//原dp表中0位置的初始化
        //将原dp表中1位置融入到后续循环当中
        for (int i = 2; i <= n; i++)
        {
            if (s[i - 1] != '0') dp[i] += dp[i - 1];
            int t = (s[i - 2] - '0') * 10 + s[i - 1] - '0';
            if (t >= 10 && t <= 26)
                dp[i] += dp[i - 2];
        }
        return dp[n];//原数组中dp[n-1]
    }
};
//int main()
//{
//    string s = "1111111111111111111";
//    Solution1 s1;
//    Solution2 s2;
//    cout << (s1.numDecodings(s) == s2.numDecodings(s));
//
//}