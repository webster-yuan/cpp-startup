// https://leetcode.cn/problems/reorder-list/description/

// 给定一个单链表 L 的头节点 head ，单链表 L 表示为：
// L0 → L1 → … → Ln - 1 → Ln
// 请将其重新排列后变为：
// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
// 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

// 其实就是两个链表的合并
// 所以只需要1. 将两个链表进行拆分,然后得到两个链表,(快慢指针)
// 2. 将后面的那个链表进行逆序(三指针逆序,直接改变指向即可)
// 3. 实现两个链表的合并即可(双指针合并)
#include "Header.hpp"
class Solution
{
public:
    ListNode *reverseList(ListNode *l2)
    {
        if (l2 == nullptr)
            return l2;
        ListNode *prev = nullptr, *cur = l2, *next = nullptr;
        while (cur)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
    void reorderList(ListNode *head)
    {
        //没节点/一个节点/两个节点都没必要,可直接返回
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return;
        // 1. 快慢指针分割链表
        ListNode *fast = head, *slow = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *l1 = head, *l2 = slow->next;
        slow->next = nullptr;
        // 2. 执行l2的逆序操作
        l2 = reverseList(l2);
        // 3. 合并两个链表
        ListNode *dummy = new ListNode(-1);
        ListNode *tail = dummy;
        while (l1 && l2)
        {
            tail->next = l1;
            tail = tail->next;
            if (l1)
                l1 = l1->next;
            tail->next = l2;
            tail = tail->next;
            if (l2)
                l2 = l2->next;
        }
        if (l1)
            tail->next = l1;
        if (l2)
            tail->next = l2;
        head = dummy->next;
        return ;
    }
};