
//https://leetcode.cn/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/
//https://www.bilibili.com/video/BV11h4y1w7Bu?t=2863.6
//先形成长度为k-1的窗口,之后每次的操作都是
//1. 入窗口,2. 收集最大值,3. 弹出左侧窗口
//插入和形成窗口时要保证窗口内的单调性,使得每时每刻想要获取的值都是队列的头部
//队列中放下标,可以保证值不重复
//尾插时,保证前面的数字比我大,否则一直弹出.
//自己实现双端队列,使用数组加双指针的方式,效率会更高
//头删时,要考虑此时队头元素是否过期,如果队头元素的下标>即将++的l,代表并不过期

#include<iostream>
#include<vector>
using namespace std;
class Solution
{
    static const  int N = 100001;
    int h, t;
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        h = t = 0;
        //int* myDeque = new int(N);
        int myDeque[N] = { 0 };
        int n = nums.size();
        //先生成k-1大小的窗口大小
        for (int i = 0; i < k - 1; i++)
        {
            //保证窗口内的有序
            while (h < t && nums[myDeque[t-1]] <= nums[i])
                t--;
            myDeque[t++] = i;
        }
        vector<int>ans;
        int l = 0, r = k - 1;
        while (r < n)
        {
            while (h < t && nums[myDeque[t-1]] <= nums[r])
                t--;
            myDeque[t++] = r;
            ans.push_back(nums[h]);
            if (myDeque[h] == l)
                h++;
            l++;
            r++;
        }
        //delete[] myDeque;
        return ans;
    }
};
class Solution1
{
    int N = 100001;
    int h, t;
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        h = t = 0;//代表此时没有值
        vector<int>myDeque(N);
        int n = nums.size();
        //首先,先形成k-1大小的窗口
        for (int i = 0; i < k - 1; i++)
        {
            while (h < t && nums[myDeque[t - 1]] <= nums[i])
                t--;
            myDeque[t++] = i;
        }
        int m = n - k + 1;
        vector<int>ans(m);
        for (int l = 0, r = k - 1; r < n; l++, r++)
        {
            while (h < t && nums[myDeque[t - 1]] <= nums[r])
                t--;
            myDeque[t++] = r;
            ans[l] = nums[myDeque[h]];
            //涉及到下标过期的问题,因为下次循环马上l++了
            if (myDeque[h] == l)
                h++;
        }
        return ans;
    }
};
//int main()
//{
//    char* ptr = new char[19];
//    delete[] ptr;
//    cout << "ok" << endl;
//    //虽然delete没有出现崩溃,但是并不意味着你可以混着用
//    const int N = 10;
//    int arr[N] = { 0 };
//	return 0;
//}