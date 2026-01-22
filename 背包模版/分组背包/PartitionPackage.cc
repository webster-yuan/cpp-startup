// 给定一个正数m表示背包的容量，有n个货物可供挑选
// 每个货物有自己的体积(容量消耗)、价值(获得收益)、组号(分组)
// 同一个组的物品只能挑选1件，所有挑选物品的体积总和不能超过背包容量
// 怎么挑选货物能达到价值最大，返回最大的价值
// 测试链接 : https://www.luogu.com.cn/problem/P1757

// dp[i][j]表示在[1...i]组上,每组只能选择1个商品,容量不超过j时,能够获取到的最大价值
// i是组号并不是商品编号
// 1. i组商品一个都不选,dp[i][j]=dp[i-1][j]
// 2. i组商品选择,那么选哪一个呢? 全试一遍,得到选择哪个能够获取到最大利润
//  dp[i][j]=dp[i-1][j-a]+val[a]
// 时间复杂度: 组的个数*(组1+组2+组3+...)即商品总个数

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class PartitionedKnapsack
{
    vector<vector<int>> arr;
    int n, m; // m代表总重量,n代表商品的个数
private:
    void init()
    {
        // arr[i][0] i号物品的体积
        // arr[i][1] i号物品的价值
        // arr[i][2] i号物品的组号
        arr = vector<vector<int>>(n + 1, vector<int>(3));
    }
    struct Compare
    {
        bool operator()(vector<int> &a1, vector<int> &a2)
        {
            return a1[2] < a2[2]; // 升序排列
        }
    };
    // 严格位置依赖,二维dp数组
    int func1()
    {
        // 1. 计算组数,因为dp[i][j]代表的就是[1...i]组中选择
        int teams = 1; // 注意初始化一定是1,具体原因由数的策略决定
        for (int i = 2; i <= n; i++)
        {
            if (arr[i][2] != arr[i - 1][2])
                teams++;
        }
        // 2. dp背包问题讨论
        vector<vector<int>> dp(teams + 1, vector<int>(m + 1));
        // dp[0][...]: 在0组中选择,也就是不选择,那么得到的最大价值肯定就是0
        for (int i = 1, start = 1, end = 2; start <= n; i++)
        {
            // 2.1 使用[start,end),来标识相同组内元素进行枚举讨论
            while (end <= n && arr[end][2] == arr[start][2])
                end++;
            for (int j = 0; j <= m; j++)
            {
                // 2.1.1 i组商品一个都不选
                dp[i][j] = dp[i - 1][j];
                // 2.1.2 i组商品需要选择,规定只能选一个,那么到底选择哪个商品获取的价值最大? 枚举一遍
                for (int k = start; k < end; k++)
                {
                    if (j - arr[k][0] >= 0)
                        dp[i][j] = max(dp[i][j], dp[i - 1][j - arr[k][0]] + arr[k][1]);
                }
            }
            start = end;
            end++;
        }
        return dp[teams][m];
    }
    //空间压缩版本,因为依赖于左侧数据,所以为了避免左侧数据被覆盖,所以从右往左进行更新
    int func()
    {
        // 因为不再定义数组,所以数组的个数是没有必要的
        vector<int> dp(m + 1);
        for (int start = 1, end = 2; start <= n;)
        {
            while (end <= n && arr[end][2] == arr[start][2])
                end++;
            for (int j = m; j >= 0; j--)
            {
                for (int k = start; k < end; k++)
                {
                    if (j - arr[k][0] >= 0)
                        dp[j] = max(dp[j], dp[j - arr[k][0]] + arr[k][1]);
                }
            }
            start = end;
            end++;
        }
        return dp[m];
    }

public:
    int Main()
    {
        cin >> m >> n;
        init();
        for (int i = 1; i <= n; i++)
            cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
        sort(arr.begin(), arr.end(), Compare()); // 根据组号进行从小到大排序,所有一个组号的都放在一起了
        return func();
    }
};

int main()
{
    PartitionedKnapsack p;
    cout << p.Main() << endl;
    return 0;
}