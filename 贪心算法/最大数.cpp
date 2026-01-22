//https://leetcode.cn/problems/largest-number/
//给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。
//注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。

//将数字转化为字符串,然后按照字典序进行排序,然后直接相连即可
#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;
class Solution
{
    struct Less
    {
        bool operator()( const string& s1,  const string& s2)
        {
            return s1+s2 < s2+s1;
        }
    };
public:
    string largestNumber(vector<int>& nums)
    {
        priority_queue<string, vector<string>, Less>heap;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            heap.push(to_string(nums[i]));
        }
        string ret = "";
        while (!heap.empty())
        {
            ret += heap.top();
            heap.pop();
        }
        //存在0值,导致结果是"00"
        int i = 0;
        while (i < ret.size() && ret[i] == '0') 
            i++;

        return (i == ret.size()) ? "0" : ret.substr(i);
    }
};
int main()
{
    Solution s;
    vector<int>arr{ 3,30,34,5,9 };
    cout << s.largestNumber(arr) << endl;
    return 0;
}