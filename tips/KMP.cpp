#include<iostream>
#include<vector>
using namespace std;

//获取[0,i]区间中前缀和后缀最大匹配长度.范围: 前缀[0,i-1] 后缀[1,i]
//next[cn]代表[0,cn]前缀和后缀匹配的最大字符数是next[cn]个,在字符串的前缀表示就是[0,next[cn]-1]
//那么下一个字符就是next[cn],就是我们想要的和pos-1位置匹配的下标,重新赋值cn=next[cn],循环往复
//实现向前跳的功能,不断向前寻找匹配.直到到达第一个为止还没成功的话,next[pos]=0;代表[0,pos]真没那命!
//匹配就是cn+1个,next[pos]=cn+1,前缀和后缀都cn+1个这么多字符匹配
class KMP
{
public:
	//O(M)得到next数组,M=matchStr.size()
	vector<int> getNextArr(string& matchStr)
	{
		if (matchStr.size() == 1)return {};
		vector<int> next(matchStr.size());
		next[0] = -1;
		next[1] = 0; //前缀[0,i-1]=>[0,0],后缀为[1,i]=>[1,1],前缀后缀匹配长度为0
		int pos = 2;
		int cn=0;
		while (pos < matchStr.size())
		{
			if (matchStr[cn] == matchStr[pos-1])
			{
				next[pos] = ++cn;
				pos++;
			}
			else if (cn > 0)
				cn = next[cn];
			else
			{
				next[pos] = 0;
				pos++;
			}
		}
	}
	//KMP意义: 返回matchStr在str中的起始位置Index的T升级为O(N) N>M
	int getIndexOfStr(string& str, string& matchStr)
	{
		if (str.size() == 0 || matchStr.size() == 0 || str.size() < matchStr.size())
			return -1;
		int si = 0, mi = 0;
		vector<int> nextArr = getNextArr(matchStr);//O(M)
		while (si < str.size() && mi < matchStr.size()) //O(N)
		{
			if (str[si] == matchStr[mi])
				si++, mi++;
			else if (nextArr[mi] != -1)//还能往前回退
				mi = nextArr[mi];
			else
				si++;
		}
		return mi == matchStr.size() ? si - mi : -1;
	}
	//相比与暴力求解,两层for循环,i,j升级之处在于,不用每次匹配到s[j]位置失败时,j回退到i+1的位置,mi回退到0位置重新匹配
	//寻求让 next[mi] 和 s[j]匹配,具体看next数组意义.
	//这样si一直往右不回头O(N),matchStr一直向右移不回头O(M),T=O(N)
	//返回值: 如果循环结束mi到达最后匹配成功,开头位置就是si-mi,否则说明没匹配成功
};