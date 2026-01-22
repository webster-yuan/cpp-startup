//https://leetcode.cn/problems/sort-the-people/submissions/475474672/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//一.绑定映射关系
//1. 构建新的类Node,放到堆中提供比较规则
//2. 记录到哈希表中,根据身高排序之后查询对应名字
//二.对下标进行排序,使得身高和名字的映射关系并不发生变化,不修改原数组
//1. 新建下标数组index
//2. 在数组中重写比较方法
class Solution
{
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights)
    {
        int n = names.size();
        vector<int>index(n);
        for (int i = 0; i < n; i++)
            index[i] = i;
        sort(index.begin(), index.end(), [&heights](int i,int j)->bool{
            return heights[i] > heights[j];
        });
        vector<string>ret;
        for (int i = 0; i < n; i++)
        {
            ret.push_back(names[index[i]]);
        }
        return ret;
    }
};