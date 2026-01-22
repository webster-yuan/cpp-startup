#include "Header.hpp"
// https://leetcode.cn/problems/add-two-numbers/
// 因为链表存储的是两个数字每一位的逆序状态,
// 新建dummy头结点,然后进行两个数字相加,用一个变量记录进位供给下一位进行运算
// 得到的每一位的结果放到一个节点中,然后进行尾插即可
// 注意: 如果两个链表中的数字足够长,用数据类型存储肯定是不行的,就会考虑到字符串
// 但是将数字->字符串->逆序->加法运算时空复杂度都比较高

class AddNodeOfList
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *cur1 = l1, *cur2 = l2;
        ListNode *dummy = new ListNode(-1);
        ListNode *tail = dummy;
        int carry = 0; // 进位,最后一位进位之后可能为10,要处理最后一位,所以cary!=0
        while (cur1 != nullptr || cur2 != nullptr || carry != 0)
        {
            if (cur1 != nullptr)
            {
                carry += cur1->val;
                cur1 = cur1->next;
            }
            if (cur2 != nullptr)
            {
                carry += cur2->val;
                cur2 = cur2->next;
            }
            ListNode *newNode = new ListNode(carry % 10);
            tail->next = newNode;
            tail = newNode;
            carry /= 10;
        }
        tail = dummy->next;
        delete dummy;
        return tail;
    }
};