//https://www.nowcoder.com/discuss/556481400451379200
//https://www.luogu.com.cn/problem/P1064#submit
//
// 1. 购买的商品都包含主件和附件,购买附件之前必须先购买主件.
// 2. 每个主件可以带0~2个附件,每个附件都有自己的主件自身并不带有附件
// 3. 每个商品有三个属性,价格vi,pi(重要度),qi(主件编号)
//  if qi==0,代表他就是自己的主件也可能是别人的主件
// 问题: 在规定的钱数n内,想要购买的商品得到的意义最大.意义=Sum(vi*pi),返回最大意义.

// 主件和附件之分,在选择的时候会习惯性的对商品进行判断,然后尝试从附件往主件推导,尝试逆向推导,但是会出现问题
// 所以,我们直接从正向开始分析
// 将是一个"集合"的当做是一个复合商品,复合商品以主件为代表,最后可以得到一个新的商品数组<复合商品>
// 那么就可以直接在这个新的数组中进行01背包问题分析,到底i号"复合商品"要还是不要的问题
// 然后选定某一件复合商品之后,再在他的附件数组follows中,对每一件附件进行01背包问题讨论,要附1?附2?附1+2?
// dp[i][j]:在1...i号主件商品中选择,在花费不超过j时,能够获得的最大意义
// 1. 我们可以再封装一个"复合商品"数组 2. 在原商品数组中,专门针对主件商品进行展开讨论
// 以下代码是针对2

#include <iostream>
#include <vector>
using namespace std;
class DependentKnapsack
{
private:
    int n, m; // n是最大钱数,m是有多少件商品
    // 因为下标是从1位置开始存储,所以多开一个空间
    vector<int> cost;            // 记录商品价格
    vector<int> val;             // 记录购买商品能够带来的价值
    vector<bool> isRoot;         // true:当前商品是主件,false:当前商品是附件
    vector<int> fans;            // 记录每个商品的附件个数
    vector<vector<int>> follows; // 记录附件商品编号
private:
    void init()
    {
        cost = vector<int>(m + 1);
        val = vector<int>(m + 1);
        isRoot = vector<bool>(m + 1);
        fans = vector<int>(m + 1);
        follows = vector<vector<int>>(m + 1, vector<int>(2));
    }
public:
    int Main()
    {
        cin >> n >> m;
        init();
        for (int i = 1, v = 0, p = 0, q = 0; i <= m; i++)
        {
            cin >> v >> p >> q;
            cost[i] = v;
            val[i] = v * p;
            isRoot[i] = q == 0;
            if (q != 0) // q就是i号商品的主件编号
                follows[q][fans[q]++] = i; // 在主件的对应位置放入i号,并注意累加fans[q]
        }
        return func();
    }
    int func1()
    {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        // dp[0][...]: 不选择商品时能够获得的最大利润=0
        int p = 0; // 上一个主件商品的编号,其实就是"复合商品"数组的i-1位置
        for (int i = 1,fan1=0,fan2=0; i <= m; i++)
        {
            if (isRoot[i])
            {
                for (int j = 0; j <= n; j++)
                {
                    // 可能性1: 这个主件商品不要
                    dp[i][j] = dp[p][j];
                    // 可能性2: 这个主件商品要
                    if (j - cost[i] >= 0)
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i]] + val[i]);
                    // 选完这个主件商品之后,展开讨论附件要不要
                    // fan1 : 如果有附1商品，编号给fan1，如果没有，fan1 == -1
                    // fan2 : 如果有附2商品，编号给fan2，如果没有，fan2 == -1
                    fan1 = fans[i] >= 1 ? follows[i][0] : -1;
                    fan2 = fans[i] >= 2 ? follows[i][1] : -1;
                    if (fan1 != -1 && j - cost[i] - cost[fan1] >= 0)
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
                    if (fan2 != -1 && j - cost[i] - cost[fan2 >= 0])
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
                    if (fan1 != -1 && fan2 != -1 && j - cost[i] - cost[fan1] - cost[fan2] >= 0)
                        dp[i][j] = max(dp[i][j], dp[p][j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
                }
            }
            p = i;
        }
        return dp[p][n]; // 此时返回的是最后一个附件商品p
    }
    // 空间压缩版本: 依赖于上一行"复合商品"的左侧: 第j列,j-cost[0],j-cost[1],j-cost[0]-cost[1]列;
    // 所以直接从右往左进行更新即可
    int func()
    {
        vector<int> dp(n + 1);
        for (int i = 1, fan1 = 0, fan2 = 0; i <= m; i++)
        {
            if (isRoot[i])
            {
                for (int j = n; j >= cost[i]; j--)
                {
                    dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
                    fan1 = fans[i] >= 1 ? follows[i][0] : -1;
                    fan2 = fans[i] >= 2 ? follows[i][1] : -1;
                    if (fan1 != -1 && j - cost[i] - cost[fan1] >= 0)
                        dp[j] = max(dp[j], dp[j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
                    if (fan2 != -1 && j - cost[i] - cost[fan2] >= 0)
                        dp[j] = max(dp[j], dp[j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
                    if (fan1 != -1 && fan2 != -1 && j - cost[i] - cost[fan1] - cost[fan2] >= 0)
                        dp[j] = max(dp[j], dp[j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
                }
            }
        }
        return dp[n];
    }
};

int main()
{
    DependentKnapsack d;
    cout << d.Main() << endl;
    return 0;
}
