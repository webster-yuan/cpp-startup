#include<iostream>
using namespace std;
//https://leetcode.cn/problems/ba-zi-fu-chuan-zhuan-huan-cheng-zheng-shu-lcof/description/?envType=study-plan-v2&envId=coding-interviews
class Solution2
{
public:
    string RemoveSpace(string& str)
    {
        int left = 0;
        while (left < str.size() && str[left] == ' ')
            left++;
        return str.substr(left);
    }
    int strToInt(string str)
    {
        str = RemoveSpace(str);
        int index = 0;
        if (str[0] == '+' || str[0] == '-')
            index++;
        char opt = index==1?str[0]:'0';
        if (!isdigit(str[index]))
            return 0;
        int right = 0;//记录第一个不为数字的位置
        str = index == 1 ? str.substr(1) : str;
        for (int i = 0; i < str.size(); i++)
        {
            if (!isdigit(str[i]))
            {
                right = i;
                break;
            }
        }
        str = right==0? str:str.substr(index, right - index);
        //right记录的是连续数字后面的那个空格位置,所以截取right-index个
        //将str转化为整数 1. 不能超过32位,等于32位时特判 2. 负数index=1
        long long  ret = 0;
        int end = str.size() - 1;
        for (int i = 0; i < str.size(); i++)
        {
            ret += (str[end] - '0') * pow(10, i);
            end--;
        }
        //判断极大值
        if ((opt=='+'||index==0) && ret > INT_MAX)return INT_MAX;
        if (opt=='-' && ret > (long long)-1 * (INT_MIN)) return INT_MIN;
        return opt=='-' ? -1 * ret : ret;
    }
};
class Solution {
public:
    int strToInt(string str) {
        long long res = 0;
        int start = 0;
        int n = str.size();
        //消除空格
        while (start < n && isspace(str[start])) ++start;
        if (start == n) return 0;
        bool flag = true;
        //判断符号
        if (str[start] == '-' || str[start] == '+') {
            flag = str[start] == '+' ? true : false;
            ++start;
        }
        int end = start;
        //找到尾端
        while (end < n && isdigit(str[end])) ++end;
        if (start == end) return 0;

        //计算结果
        for (; start < end; ++start) {
            res = (str[start] - '0') + res * 10;
            //res=(str[start]-'0') +res*10;
            //判断边界
            if (res > INT_MAX) {
                return flag ? INT_MAX : INT_MIN;
            }
        }
        return (int)(flag ? res : -res);
    }
};
int main()
{
    Solution s;
    string str1 = "-2147483649";
    string str2 = "4193 with words";
    string str3 = "words and 987";
    string str = "234551";
    cout<<s.strToInt(str)<<endl;
    //2147483647 -2147483648
    return 0;
}