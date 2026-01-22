//使用二分答案法,范围在[1,n*min(a,b)]之间.
//如果a<b,只考虑a时,那么第n个神奇的数字就是n*a,当有b的加入时,在[1,n*a]的区间中会有更多的
//神奇的数字,那么就意味着第n个数字的区间会缩小.
//如果我们有函数func(k)告诉我们[1,k]上一共有多少个神奇的数字,
//如果ret < n,说明这个k取的不够,k=mid+1,如果ret>= n,说明取的靠右了,k=mid
//那么func函数如何实现?
// 根据容斥原理:
//1~k上有多少个神奇的数字,k/a + k/b - k/lcm(a,b)最小公倍数

/// https://leetcode.cn/problems/nth-magical-number/submissions/
#include<iostream>
using namespace std;

class Solution
{
public:
    int nthMagicalNumber(int n, int a, int b)
    {
        long long ret = lcm(a, b);
        long long ans = 0;
        for (long long l = 0, r = (long long)n * min(a, b), m = 0; l <= r;)
        {
            m = l+(r-l)/ 2;
            if ((m / a) + (m / b) - (m / ret) >= n)
            {
                ans = m;
                r = m - 1;
            }
            else
                l = m + 1;
        }
        return (int)(ans % 1000000007);
    }
    //求解最大公约数,a>b时,时间复杂度是O(log(a)^3),复杂度足够好.
    //欧几里得算法: 辗转相除法
    long long gcd(long long a, long long b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    //求解最小公倍数
    long long lcm(long long a, long long b)
    {
        return (long long)a / gcd(a, b) * b;
    }
};