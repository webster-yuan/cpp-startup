//当一个表达式中类型取余值时,避免中间值出现溢出的场景,就可以依靠同余原理
//用string类型拼数字时,如果位数过长,会出现算不完的场景.
// 因为int类型,longlong类型在底层都是固定位数,int->32位,longlong64位,所以计算是O(1)
// 但是每个中间结果是k位,那么做四则运算的时间复杂度是+-是O(k),*/是O(k^2)
// 导致越算越慢
//四则运算同余原理公式: 
// (a+b)%m = (a%m + b%m )%m
// (a*b)%m = (a%m * b%m )%m
// (a-b)%m = (a%m - b%m +m)%m
// 
class Solution
{
	//计算((a + b)* (c - d) + (a * c - b * d)) % mod 的非负结果
public:
	int f2(long long a, long long b, long long c, long long d, int mod) 
	{
		int o1 = (int)(a % mod); // a
		int o2 = (int)(b % mod); // b
		int o3 = (int)(c % mod); // c
		int o4 = (int)(d % mod); // d
		int o5 = (o1 + o2) % mod; // a + b
		int o6 = (o3 - o4 + mod) % mod; // c - d
		int o7 = (int)(((long long)o1 * o3) % mod); // a * c
		int o8 = (int)(((long long)o2 * o4) % mod); // b * d
		int o9 = (int)(((long long)o5 * o6) % mod); // (a + b) * (c - d)
		int o10 = (o7 - o8 + mod) % mod; // (a * c - b * d)
		int ans = (o9 + o10) % mod; // ((a + b) * (c - d) + (a * c - b * d)) % mod
		return ans;
	}
};
