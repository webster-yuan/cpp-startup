// https://leetcode.cn/problems/reverse-nodes-in-k-group/

// k个一组翻转链表,然后就涉及到指针的变换了.不足k个的节点们不用动
// 1. 先求出需要翻转x组,x=n/k
// 2. 重复n次k个节点一组的翻转即可 (结合题意,使用头插的方式逆序更简洁)
// O(N)
#include "Header.hpp"
class Solution
{
public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        int n = 0;
        ListNode *cur = head;
        while (cur)
        {
            n++;
            cur = cur->next;
        }
        n /= k;
        ListNode *dummy = new ListNode(-1);
        ListNode *prev = dummy; // 指定头插的前驱结点
        cur = head;
        while (n--)
        {
            ListNode *tmp = cur;
            for (int i = 0; i < k; i++)
            {
                ListNode *next = cur->next;
                cur->next = prev->next; // 头插的方式逆序链表
                prev->next = cur;
                cur = next;
            }
            prev = tmp;
        }
        prev->next = cur;
        cur = dummy->next;
        delete dummy;
        return cur;
    }
};