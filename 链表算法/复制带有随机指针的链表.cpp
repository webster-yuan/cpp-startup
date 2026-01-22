
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;



class Node
{
public:
	int data;
	Node* next;
	Node* randPtr;
	Node(int val)
		:data(val)
		, next(nullptr)
		,randPtr(nullptr)
	{}
};
class CopyList
{
public:
	//1. 比较贼的方式,用哈希表记录<源节点,新建节点>,然后根据原链表连接新链表
	//<O(N),O(N)>使用到额外空间
	Node* copyList1(Node* head)
	{
		unordered_map<Node*, Node*> hashMap;
		Node* cur = head;
		while (cur)
		{
			Node* newNode = new Node(cur->data);
			hashMap[cur] = newNode;
			cur = cur->next;
		}
		cur = head;
		while (cur)
		{
			hashMap[cur]->next = cur->next;
			hashMap[cur]->randPtr = cur->randPtr;
			cur = cur->next;
		}
		return hashMap[head];
	}
	//2. <O(N),O(1)> 将新产生的节点直接连接在每个节点的后面,最后split
	Node* copyList2(Node* head)
	{
		if (head == nullptr)return;
		Node* cur = head;
		while (cur)
		{
			Node* next = cur->next;

			Node* newNode = new Node(cur->data);
			newNode->next = cur->next;
			cur->next = newNode;

			cur = next;
		}
		//连接randPtr
		cur = head;
		Node* copyNode = nullptr;
		while (cur)
		{
			copyNode = cur->next;
			Node* next = cur->next->next;
			copyNode->randPtr = cur->randPtr == nullptr ? nullptr : cur->randPtr->next;
			cur = next;
		}
		//split和重新连接
		Node* res = head->next;
		cur = head;
		while (cur)
		{
			Node* next = cur->next->next;
			copyNode = cur->next;
			cur->next = next;
			copyNode->next = next == nullptr ? nullptr : next->next;
			cur = next;
		}
		return res;
	}
};