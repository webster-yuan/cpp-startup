//https://leetcode.cn/problems/heaters/
//现在，给出位于一条水平线上的房屋 houses 和供暖器 heaters 的位置，
// 请你找出并返回可以覆盖所有房屋的最小加热半径。
//注意：所有供暖器 heaters 都遵循你的半径标准，加热的半径也一样

//先对两个数组进行排序
//房屋找那个供暖器最值,距离进行判断,选择最小值
//记录所有房屋选择之后的最大值作为加热半径,才能保证所有的房屋都得到供暖
//https://www.bilibili.com/video/BV1V841167Rg?t=5122.1
//相等的时候一定要让他动,贪心,避免多个供暖器在同一个位置时为了避免r一直停留在一个位置(因为判断func的逻辑错误)
//func只是比较两个供暖期距离远近进行比较,如果距离相同,一定要往下动.
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
public:
    //O(n*logn)->排序,两个指针分别在两个数组中都不回退,所以是O(N)
    int findRadius(vector<int>& houses, vector<int>& heaters)
    {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int ans = 0;
        int j = 0;
        for (int i = 0; i < houses.size(); i++)
        {
            while (!best(houses, heaters, i, j))//如果i号房屋选择j号供暖器不是最好的
                j++;
            ans = max(ans, abs(houses[i] - heaters[j]));

        }
        return ans;
    }
    bool best(vector<int>& houses, vector<int>& heaters, int i, int j)
    {
        return j == heaters.size() - 1 ||
            abs(houses[i] - heaters[j]) < abs(houses[i] - heaters[j + 1]);
        //相等的时候返回false,也跳到下一个位置
    }
};