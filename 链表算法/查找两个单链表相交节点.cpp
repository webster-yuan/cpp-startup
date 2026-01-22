#include<iostream>
#include<vector>
using namespace std;


class Node
{
public:
	int data;
	Node* next;
	Node(int val)
		:data(val)
		, next(nullptr)
	{}
};

class findFirstInteractNode
{
public:
	//返回两个链表第一个相交点
	//1. 两个单链表不构成环 1.1 无交点返回nullptr 2. 返回唯一交点
	//2. 两个单链表构成环&&入环节点是同一个 
	//3. 两个单链表构成环&&入环节点不是同一个,返回哪个入环节点均可
	//注:注意单链表单指向的特性,构成环的肯定是公用一个环,获取一个单链表入环节点使用快慢指针方法
	Node* getFirstInteractNode(Node* head1, Node* head2)
	{
		if (head1 == nullptr || head2 == nullptr)return;
		Node* loop1 = getLoopNode(head1);
		Node* loop2 = getLoopNode(head2);
		if (loop1 == nullptr && loop2 == nullptr)
			return noloop(head1,head2);
		if (loop1 != nullptr && loop2 != nullptr)
			return bothLoop(head1,head2,loop1,loop2);
		return nullptr;
	}
	Node* bothLoop(Node* head1, Node* head2,Node*loop1,Node* loop2)
	{
		Node* cur1 = nullptr, * cur2 = nullptr;
		if (loop1 == loop2)
		{
			Node* cur1 = head1, * cur2 = head2;
			int n = 0;
			while (cur1)
			{
				n++;
				cur1 = cur1->next;
			}
			while (cur2)
			{
				n--;
				cur2 = cur2->next;
			}
			cur1 = n < 0 ? head2 : head1;
			cur2 = cur1 == head1 ? head2 : head1;
			int del = abs(n);
			while (del--) cur1 = cur1->next;
			while (cur1 != cur2) cur1 = cur1->next, cur2 = cur2->next;
			return cur1;
		}
		else
		{
			Node* cur1 = loop1->next;
			while (cur1 != loop1)//环上走一圈,肯定和另一个入环节点相遇
			{
				if (cur1 == loop2)
					return loop2;
				cur1 = cur1->next;
			}
			return nullptr;
		}
	}
	Node* getLoopNode(Node* head)
	{
		//至少三个成环
		if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
			return nullptr;
		Node* n1 = head->next;
		Node* n2 = head->next->next;
		while (n1 != n2)
		{
			if (n2->next == nullptr || n2->next->next == nullptr)
				return nullptr;
			n1 = n1->next;
			n2 = n2->next->next;
		}
		//此时n1n2在环上的某一个节点处,其中一个从头走,一定在入环节点相遇
		n1 = head;
		while (n1 != n2)
		{
			n1 = n1->next;
			n2 = n2->next;
		}
		return n1;
	}
	Node* noloop(Node* head1, Node* head2)
	{
		Node* cur1 = head1, * cur2 = head2;
		int n = 0;
		while (cur1)
		{
			cur1 = cur1->next;
			n++;
		}
		while (cur2)
		{
			n--;
			cur2 = cur2->next;
		}
		if (cur1 != cur2)//尾巴不是一个,说明没有相交
			return nullptr;
		//有交点
		cur1 = n < 0 ? head2 : head1;
		cur2 = cur1 == head1 ? head2 : head1;
		int dis = abs(n);
		while (dis--)
		{
			cur1 = cur1->next;
		}
		//cur1,cur2此时距离交点相同
		while (cur1 != cur2)
		{
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;//返回交点
	}
};