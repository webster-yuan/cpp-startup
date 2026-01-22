
// 给定一个数组nums，含有n个数字，都是非负数
// 给定一个正数k，返回所有子序列中累加和最小的前k个累加和
// 子序列是包含空集的
// 1 <= n <= 10^5
// 1 <= nums[i] <= 10^6
// 1 <= k <= 10^5
// 注意这个数据量，用01背包的解法是不行的，时间复杂度太高了. 需要填写二维表 >> 10^7 10^8
// 对数器验证
// ------------解法1:
// 也就是说,我们得到所有子序列的累加和->nums[]中,按照从小到大排序,截取出前k个组成ans[]返回
// ------------解法2: 使用01背包的方式
// dp[i][j]表示: 在前i个数字中选择,累加和<=j的子序列一共有多少个
// 最后一行都是dp[n][0...sum]的个数,然后截取0<=j<=k这些个数字组成ans[]即可
// 开的二维表 i=n,j=sum,j的大小和数据量有关,时空复杂度都会越界
// ------------解法3: 堆的方式解决 https://www.bilibili.com/video/BV1NN41137jF?t=7664.8
// <A{},sumA>
// 每次弹出堆顶,记录sumA,将数字num = nums[index+1]
// 1. num->A{} ->sumA'
// 2. 删除A{}中元素,然后num->A{} ->sumA ''
// 将sumA' sumA''->heap
//...
// code时只需要记录集合中最后一个元素的下标即可代替维持的 集合类型
//<最右下标,累加和>
// 每弹出堆一次,一共需要弹出K-1个,就会插入两个,然后重新调整O(logK),时间复杂度和K有关. O(k*log(k)).
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
class TopKMinimumSubsequenceSum
{
public:
    vector<int> Main2(vector<int> &nums, int k)
    {
        int sum = 0;
        for (int num : nums)
            sum += num;
        // 1. dp[i][j]=dp[i-1][j]
        // 2. dp[i][j]=dp[i-1][j-nums[i]]
        // 两种情况相加得到最终的总个数
        vector<int> dp(sum + 1);
        dp[0] = 1; // 累加和<=0的,那么就是空集,也是一种
        for (int num : nums)
        {
            for (int j = sum; j >= num; j--)
                dp[j] += dp[j - num];
        }
        vector<int> ans(k);
        int index = 0;
        for (int j = 0; j <= sum && index < k; j++)
        {
            for (int i = 0; i < dp[j] && index < k; i++)
                ans[index++] = j;
        }
        return ans;
    }

public:
    class Node
    {
    public:
        int right;
        int sum;

    public:
        Node(int r, int s)
            : right(r), sum(s)
        {
        }
    };
    struct Less
    {
        bool operator()(const Node &n1, const Node &n2)
        {
            return n1.sum>n2.sum;
        }
    };
    vector<int> Main3(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end());
        priority_queue<Node, vector<Node>, Less> heap;
        heap.push(Node(0, 0));
        vector<int> ans(k);
        for (int i = 1; i < k; i++)
        {
            Node cur = heap.top();
            heap.pop();
            int right = cur.right;
            int sum = cur.sum;
            ans[i] = sum;
            if (i + 1 < nums.size())
            {
                heap.push(Node(right + 1, sum - nums[right] + nums[right + 1]));
                heap.push(Node(right + 1, sum + nums[right + 1]));
            }
        }
        return ans;
    }
};