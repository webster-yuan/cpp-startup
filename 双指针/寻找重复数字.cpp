//https://leetcode.cn/problems/find-the-duplicate-number/description/
//只用有限几个变量找到这个重复的数字

//解法:
//x=nums[i],那么下一个指针就到x位置,一直进行下去,画出图来,如果存在重复值就会造成类似链表中出现环的情况
//使用快慢指针的方式模拟,然后找到类似链表中的入环节点就是重复值.
//快指针一次跳两步,慢指针一次跳一步,注意初始化.最终会在环上的节点相遇
//之后两个指针中一个从头,同样都走一步,就会在入环节点相遇.
#include<iostream>
#include<vector>
using namespace std;

class Solution2
{
public:
    int findDuplicate(vector<int>& nums) 
    {
        if (nums.size() < 2)
            return -1;
        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;//回到开头
        while (slow != fast)
        {
            fast = nums[fast];
            slow = nums[slow];
        }
        return slow;
    }
};