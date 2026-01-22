#include "Header.hpp"

// 解法1. 使用递归的方式实现
// 子问题: 相信func函数能够将两个节点之后的链表完成交换,然后返回头结点指针
// 只需要处理 head ->next ->ret三个节点之间的指向关系即可,并将next返回
// 出口: 只剩下一个节点的时候就不需要交换了
class TwoNodeSwapList_1th
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *ret = swapPairs(head->next->next);
        ListNode *next = head->next;
        head->next = ret;
        next->next = head;
        return next;
    }
};
// 解法2: 使用循环的方式
// 定义四个节点指针变量,指向节点,更改变量之间的指向关系即可
// 此时,采用多加一个头结点的方式可以最大程度将所有情况覆盖到整体代码中
// prev cur next nnext
// 注意添加dummy头结点之后链表节点奇数偶数个的时候的结束条件
// 1. 交换完成之后,cur==nullptr,代表是偶数
// 2. 交换完成之后,next==nullptr,只剩下cur 一个节点,没有交换的必要
class TwoNodeSwapList_2th
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;

        ListNode *prev = dummy, *cur = head, *next = head->next, *nnext = head->next->next;
        while (cur && next)
        {
            // 交换节点
            prev->next = next;
            cur->next = nnext;
            next->next = cur;
            // 移动指针1
            prev = cur;
            cur = nnext;
            // 移动指针2
            if (cur)
                next = cur->next;
            if (next)
                nnext = next->next;
        }
        cur = dummy->next;
        delete dummy;
        return cur;
    }
};