#include<iostream>
#include<vector>
using namespace std;
//给定一个非负整数数组 nums，  nums 中一半整数是 奇数 ，一半整数是 偶数 。
//对数组进行排序，以便当 nums[i] 为奇数时，i 也是 奇数 ；当 nums[i] 为偶数时， i 也是 偶数 。
//你可以返回 任何满足上述条件的数组作为答案 。
//也就是奇数放在奇数下标位置,偶数放在偶数下标位置.

//使用双指针,even标记偶数下标,odd标记奇数下标,盯着最后一位看x = nums[n-1],
//if x是奇数,就和odd标记的数字进行交换,else 和even标记的数字交换,
//交换之后将对应指针跳到下一个奇(偶)数下标位置,直到其中一个超过边界,代表奇(偶)数已经安排完毕
class Solution1
{
public:
    vector<int> sortArrayByParityII(vector<int>& nums)
    {
        int n = nums.size();
        int even = 0, odd = 1;
        while (even < n && odd < n)
        {
            if ((nums[n - 1] & 1) == 1)
            {
                swap(nums[odd], nums[n - 1]);
                odd += 2;
            }
            else
            {
                swap(nums[even], nums[n - 1]);
                even += 2;
            }
        }
        return nums;
    }
};