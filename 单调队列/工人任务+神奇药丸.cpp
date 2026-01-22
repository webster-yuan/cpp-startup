//https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/
//最多有多少个任务可以被完成
//二分答案+贪心+双端队列(想到数组排序支持单调性)
// 
//完成任务的范围可以被确定,最少0个,最多都可以完成,那么最多可以完成多少个任务?
//单调性: 完成8个任务肯定比完成7个任务要更难,所以使用二分答案法,尝试mid个任务能否完成,
//如果mid完不成,那么mid,right肯定也完不成,就去左侧区间二分,如果mid能完成,记录答案,到右侧区间尝试
//所以需要func函数,判断mid个任务能否被完成
//如果只要求完成k个任务,那么在完成一个任务带来的收益是一样时,肯定选择需要能力最小的k个任务,排序
//一定选择能力最强的k个工人去完成最小的k个任务,贪心思想.
//func完成与否完全取决于工人吃的药丸数量够不够
//最后,当来到一个工人时,先看一眼在不吃药的情况下能够完成的任务,将他们放入到dq中,
//当dq中存在自己能做的任务时,选择dq队头任务,也就是最小的任务完成,一定能保证不亏.让要求更高的任务交给能力更大的人
//当dq中没有自己能做的任务时,要吃药了,吃完药之后,看自己解锁了哪些任务,放到队列中,
//在保证最不亏的情况下,应该让吃完药的自己去完成自己能力范围内要求最大的任务,也就是弹出此时队尾的元素.
//一定是使用药丸最省的,看看给定药丸够不够.
//因为事先都排过序了,如果吃了药之后都没有可以匹配的任务,直接返回false
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Solution
{
    vector<int>tasks;
    vector<int>workers;
    int MAXLEN = 100001;
    vector<int>dq;
    int h, t;
public:
    int maxTaskAssign(vector<int>& t, vector<int>& w, int pills, int strength)
    {
        tasks = t;
        workers = w;
        dq = vector<int>(MAXLEN);
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int tsz = tasks.size(), wsz = workers.size();
        int ans = 0;
        for (int l = 0, r = min(tsz, wsz); l <= r;)
        {
            int mid = (l + r) / 2;
            if (func(mid, pills, strength, 0, mid - 1, wsz - mid, wsz - 1))
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        return ans;
    }
    bool func(int count, int p, int s, int tl, int tr, int wl, int wr)
    {
        h = t = 0;
        int cnt = 0;
        for (int i = wl,j=tl; i <= wr; i++)
        {
            //i: 工人编号,j:任务编号
            //1. 将i号工人能够解锁的任务放到队列中
            for (; j <= tr && workers[i] >= tasks[j]; j++)
                dq[t++] = j;
            //2. 如果不吃药有任务可以做
            if (h<t && workers[i] >= tasks[dq[h]])
                h++;
            else
            {
                //3. 必须得吃药,将吃完药之后能够解锁的任务放到队列中
                for (; j <= tr && workers[i] + s >= tasks[j]; j++)
                    dq[t++] = j;
                if (h < t)
                {
                    cnt++;
                    t--;
                }
                else
                    return false;
            }
        }
        return cnt <= p;
    }
};