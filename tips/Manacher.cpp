#include<iostream>
#include<vector>
using namespace std;

//Manacher算法用于求解字符串最长回文子串的长度,将时间复杂度降至O(N)\
// 核心是如何将经典的从i位置向两边扩找最大半径的过程进行加速,直接确定值.
//1. 首先添加特殊字符.解决偶数串无中间轴扩,导致查找丢失情况的问题
//2. 填充pArr数组,pArr[i]记录以i为中心回文的最大半径值
//3. 时刻更新pR(能拓展到右边的最右边界)以及中心index
//更新pArr数组时,pR代表即将到达的位置,pR-1代表已经包含的区域
//1. 如果i>pR-1,继续以i为中心向右扩充
//2. 如果i<pR-1,代表i已经被包含,就根据三种情况更新pArr[i]的值
//	 前两种,i以index为中心对称的点i',i'半径pArr[i']和距离左边距离(==i距离右边距离)pR-i取较小值即可完成两种的覆盖,
//	 实现优化.
//第三种情况还存在可扩充的可能,所以无法直接确定值,还得自己扩充.但是是在有i'的基础之上开始扩充,pArr[i]
// 扩充前存有i'设定的值,只不过此时仍可扩充
//扩充过程中出现更加靠右的边界时,要更新pR,中心点index
class Solution2
{
public:
	int isPalindrome(string& s)
	{
		if (s.size() == 0)return 0;
		string str = opt(s);
		int n = str.size();
		vector<int>pArr(n);
		int index = -1, pR = -1;
		int retMaxLen = 1;
		for (int i = 0; i < n; i++)
		{
			int i_ = 2 * index - i;
			pArr[i] = pR > i ? min(pArr[i_], pR - i) : 1;
			while (i + pArr[i] < n && i - pArr[i] >= 0)//允许向两边扩充,所以注意边界
			{
				if (str[i - pArr[i]] == str[i + pArr[i]])
					pArr[i]++;
				else
					break;
			}
			if (i + pArr[i] > pR)
			{
				pR = i + pArr[i];
				index = i;
			}
			retMaxLen = max(retMaxLen, pArr[i]);//填完一个pArr[i]就记录最大值
		}
		return retMaxLen - 1;
	}
	string opt(string & str)
	{
		int n = str.size();
		string tmp;
		char gap = '#';
		int index = 0;
		for (int i = 0; i < 2 * n + 1; i++)
		{
			if ((i % 2) == 0)//偶数位
				tmp.push_back(gap);
			else
				tmp.push_back(str[index++]);
		}
		//cout << tmp << endl;添加特殊字符没问题
		return tmp;
	}
};
int main()
{
	string str = "12345";
	Solution2 s;
	s.isPalindrome(str);
	return 0;
}





//用经典做法,用一张二维表记录所有起点和终点的区间回文情况,然后在表中记录最长
//dp[i][j]表示字符串[i,j]区间是否是回文子串,
//1. s[i]==s[j],1. i==j 一个字符true 2. i+1==j 两个字符true 3. i+1<j 好多字符,缩小区间dp[i+1][j-1]
//2. s[i]!=s[j]边界都不相同肯定不行
//初始化: 因为约定好的i<j,所以只需要填充半个二维表,并且i=i正斜线代表下标相等只有一个字符,true
//填表顺序: i依赖于i+1,j依赖于j-1,所以从下往上,从左往右
//返回值: 记录最大值,所以边填表边记录
class Solution1
{
public:
	int isPalindrome(string& str)
	{
		int n = (int)str.size();
		vector<vector<int>>dp(n, vector<int>(n));
		int ret = 1;
		int len = 1, begin = 0;//最长长度和起始位置
		for (int i = n-1;i>=0; i--)
		{
			for (int j = i; j < n; j++)
			{
				if (str[i] == str[j])
					dp[i][j] = i + 1 < j ? dp[i + 1][j - 1] : true;
				if (dp[i][j] && j - i + 1 > len)
					len = j - i + 1, begin = i;
			}
		}
		return len;
		//return str.substr(begin,len);返回最长回文子串
	}
};