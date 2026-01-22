// https://leetcode.cn/problems/merge-k-sorted-lists/description/

#include "Header.hpp"

// 解法一:暴力方式
// 两两合并得到一个新的,然后再和一个链表合并...
// 时间复杂度: K个链表的平均长度是N,假设每个链表长度都是N
// 估计时间复杂度时第一个想法遇到的问题是一个链表合并之后长度是在增加的,变成了2n
// 再合并一次变成3n,O(3n+n)...
// 那么换一个角度,合并归纳给一个链表之后变成i*n之后还需要再遍历,不如认为是每个长度为n的链表
// 都和其他剩余的链表合并一次遍历一次,即如下:
// 只针对第一个链表,需要和剩余的k-1个链表分别执行一次合并,两两合并的时间复杂度是O(n),
// 所以第一个链表在整体合并中占据的时间复杂度是(k-1)*n
// 针对第二个链表在整体合并中占据的时间复杂度为(k-2)*n
//...
//(k-1)*n+(k-2)*n+(k-3)*n+...+n
// O(k^2 * n),如果k也就是个数接近n,则O(n^3)
// leetCode : 132~140ms
class MergeKLists_1
{
private:
    ListNode *func(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;
        ListNode *dummy = new ListNode(-1);
        ListNode *tail = dummy;
        while (l1 && l2)
        {
            if (l1->val < l2->val)
            {
                tail->next = l1;
                tail = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                tail = l2;
                l2 = l2->next;
            }
        }
        if (l1)
            tail->next = l1;
        if (l2)
            tail->next = l2;
        return dummy->next;
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *ans = nullptr;
        for (int i = 0; i < lists.size(); i++)
        {
            ans = func(ans, lists[i]);
        }
        return ans;
    }
};

// 解法二: 利用堆做优化
// k个指针,将k个节点的值放到堆中,然后获取较小值加入到答案链表中
// 小根堆一次O(logk),需要进行n次,所以是O(n*logk)
// leetCode : 24ms
class MergeKLists_2
{
    struct Less
    {
        bool operator()(ListNode *&l1, ListNode *&l2)
        {
            return l1->val > l2->val;
            // 思考方式1: 建立小根堆考虑向下调整操作时,肯定是父 > 孩子中大值时向下走,所以是>
            // 思考方式2: 小根堆完成的是降序,所以是>方向
        }
    };

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        // 1. 创建小根堆
        priority_queue<ListNode *, vector<ListNode *>, Less> heap;
        // 2. 将所有头结点入小根堆
        for (auto &l : lists)
        {
            if (l != nullptr)
                heap.push(l);
        }
        // 3. 操作
        ListNode *dummy = new ListNode(-1);
        ListNode *tail = dummy;
        while (!heap.empty())
        {
            ListNode *top = heap.top();
            heap.pop();
            tail->next = top;
            tail = top;
            if (top->next != nullptr)
                heap.push(top->next);
        }
        tail = dummy->next;
        delete dummy;
        return tail;
    }
};
// 解法三: 分治+递归的方式
// 区间划分
// 左侧多个链表合并+右侧多个链表合并
//...持续划分,画出决策树,划分出子问题处理即可
// 然后使用递归的方式处理
// 时间复杂度: 每个链表只执行合并了高度次即可,高度就是O(logk)=>O(n*logk)
// leetCode : 24ms
class MergeKLists_3
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return func(lists, 0, lists.size() - 1);
    }
    ListNode *func(vector<ListNode *> &lists, int left, int right)
    {
        if (left > right)
            return nullptr;
        if (left == right)
            return lists[left];
        // 区间划分
        int mid = (left + right) >> 1;
        ListNode *l1 = func(lists, left, mid);
        ListNode *l2 = func(lists, mid + 1, right);
        return merge(l1, l2);
    }
    ListNode *merge(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;
        ListNode *dummy = new ListNode(-1);
        ListNode *tail = dummy;
        while (l1 && l2)
        {
            if (l1->val < l2->val)
            {
                tail->next = l1;
                tail = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                tail = l2;
                l2 = l2->next;
            }
        }
        if (l1)
            tail->next = l1;
        if (l2)
            tail->next = l2;
        return dummy->next;
    }
};