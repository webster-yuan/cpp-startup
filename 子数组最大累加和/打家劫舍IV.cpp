//https://leetcode.cn/problems/house-robber-iv/description/
//至少偷够K个房屋,并且偷得时候不能相连,还是只能偷能力值ret >nums[i]的,
//返回能力的最小值

//二分答案法,构建单调性
//首先确定范围,(minVal,maxVal)
//如果能力ret=50时就能够偷够K间房屋,那么ret>50时肯定也能偷够K间,我们要的是满足条件的最小值
//所以去左侧区间中寻找,这就是单调性
//所以需要一个函数func()告诉我,在能力为ret时,在nums数组中能不能偷够K间房屋
//需要注意的是,此时就不是求解最大累加和的问题,而是求解最大投多少间房的问题,如果nums[i]>ability,+1即可不是求和了
//下面是采用空间压缩版本实现的.
//优化: 贪心,能偷赶紧偷,然后跳过下一个格子即可,越早偷越好,收益都是一样的就是+1,不存在累加和时收益不同的情况
#include<iostream>
#include<vector>
using namespace std;
class Solution 
{
    int n;
public:
    int minCapability(vector<int>& nums, int k)
    {
        n = nums.size();

        int l = nums[0], r = nums[0];
        for (int i = 1; i < n; i++)
        {
            l = min(l, nums[i]);
            r = max(r, nums[i]);
        }
        int ret = 0;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (func(nums, mid) >= k)
            {
                ret = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        return ret;
    }
    int func(vector<int>& nums, int ability)
    {
        if (n == 1)
            return nums[0] <= ability ? 1 : 0;
        if (n == 2)//以为相邻不能选择
            return (nums[0] <= ability || nums[1] <= ability) ? 1 : 0;

        int pprev = nums[0] <= ability ? 1 : 0;
        int prev = (nums[0] <= ability || nums[1] <= ability) ? 1 : 0;
        for (int i = 2; i < n; i++)
        {
            int cur = max(prev, pprev + (nums[i] <= ability ? 1 : 0));
            pprev = prev;
            prev = cur;
        }
        return prev;
    }
    int func2(vector<int>& nums, int ability)
    {
        int ans = 0;
        for (int i = 0; i < n; i++) 
        {
            if (nums[i] <= ability) 
            {
                ans++;
                i++;//跳过下一个格子,因为不能相邻
            }
        }
        return ans;
    }
};

