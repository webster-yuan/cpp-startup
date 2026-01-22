#include<iostream>
using namespace std;
//https://leetcode.cn/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof/description/?envType=study-plan-v2&envId=coding-interviews
//别小瞧了他!!!!
//因为.和eE多次出现时应该得以判断是否定情况,所以无法直接使用find函数,只能采用标记位的形式判断是否是重复出现

class Solution
{
public:
    //1. 去除字符串两端的空格
    string RemoveSpace(string& s)
    {
        int n = s.size();
        int left = 0, right = n - 1;
        while (left < n && s[left] == ' ') left++;
        while (right >= 0 && s[right] == ' ') right--;
        return s.substr(left, right - left + 1);
    }
    bool isNumber(string s)
    {
        s = RemoveSpace(s);
        //2. 使用标记位判断是否特殊字符重复出现
        int epos = -1;
        bool flag = false;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'e' || s[i] == 'E')
            {
                if (epos == -1)//epos如果在一个合法位置,说明之前出现过e
                    epos = i;
                else
                    return false;
            }
        }
        //3. 分两段区间讨论
        if (epos == -1) return isDecimal(s) || isInt(s);

        string left = s.substr(0, epos-1 -0 +1);
        string right = s.substr(epos + 1);
        return (isInt(left) || isDecimal(left)) && isInt(right);
    }
    bool isInt(string& s)
    {
        //4. 字符串是""时return false
        if (s.size() == 0) return false;

        int index = 0;
        if (s[0] == '+' || s[0] == '-')
            index++;

        //查询index到结尾是否都是整数
        int i = index;
        int count = 0;
        //5. right部分必须有数字,避免只有一个 +
        for (; i < s.size() && s[i] != ' '; i++)
        {
            if (!isdigit(s[i]))
                return false;
            count++;
        }
        //6. 因为s[i]可能因为是数字之间中间字符,半路跳出
        return i == s.size()&&count>0;
    }
    bool isDecimal(string& s)
    {
        if (s.size() == 0) return false;

        int index = 0;
        if (s[0] == '+' || s[0] == '-')
            index++;
        bool flag = false;
        //7. 小数的.两边都必须有数字
        int left = 0, right = 0;
        int i = index;
        for (; i < s.size() && s[i] != ' '; i++)
        {
            if (s[i] == '.')
            {
                if (!flag)
                    flag = true;
                else
                    return false;
            }
            else if (isdigit(s[i]))
            {
                if (!flag)left++;
                else right++;
            }
            else
                return false;
        }
        return flag && (left > 0 || right > 0) && i == s.size();
        //数字之间出现空也是false,i会在中间跳出
    }
};

//int main()
//{
//    Solution s;
//    string str1 = "2e0";
//    string str = "4e+";
//    cout<<s.isNumber(str);
//    return 0;
//}