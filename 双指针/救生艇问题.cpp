//https://leetcode.cn/problems/boats-to-save-people/description/
//排序与否都不影响结果,所以先排个序
//
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution 
{
public:
    int numRescueBoats(vector<int>& people, int limit) 
    {
        sort(people.begin(), people.end());
        int ans = 0;
        int n = people.size();
        int l = 0, r = n - 1;
        int sum = 0;
        while (l <= r)
        {
            sum = l == r ? people[l] : people[l] + people[r];
            if (sum > limit)
            {
                r--;
            }
            else
            {
                l++;
                r--;
            }
            ans++;
        }
        return ans;
    }
};
//新增限制: 如果两个人做一个船,体重和必须是偶数
//只能是奇数奇数一起,偶数偶数一起,把奇数偶数数组分出来,然后走上面过程相加即可.