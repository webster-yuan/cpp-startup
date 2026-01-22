//https://leetcode.cn/problems/lemonade-change/
//5元的作用很大,贪心的角度就是在两种选择中,尽可能保留更多的5元
//当用户给定20元时,可以选择返还一张10元,一张5元,也可以选择返还三张5元,
//贪心的选择第一种方式,以达到更多的保留5元的目的

//找零只涉及到5元和10元,所以只要统计这两张纸币的个数
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    bool lemonadeChange(vector<int>& bills)
    {
        int five = 0, ten = 0;
        //for (int& x : bills)//使用范围for的效率很低
        int n = bills.size();
        for (int i = 0; i < n; i++)
        {
            int x = bills[i];
            if (x == 5)
                five++;
            else if (x == 10)
            {
                if (five == 0)
                    return false;
                else
                {
                    ten++;
                    five--;
                }
            }
            else
            {
                if (ten && five)
                {
                    ten--, five--;
                }
                else if (five >= 3)
                {
                    five -= 3;
                }
                else
                    return false;
            }
        }
        return true;
    }
};