#include<iostream>
#include<vector>
#include<unordered_map>
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
class ListSplitData
{
public:
	//使用6个指针变量标识三块区域
	Node* listSplit2(Node* head, int pivot)
	{
		Node* sHead = nullptr;
		Node* sTail = nullptr;
		Node* eHead = nullptr;
		Node* eTail = nullptr;
		Node* bHead = nullptr;
		Node* bTail = nullptr;

		Node* next = nullptr;
		while (head)
		{
			next = head->next;
			if (head->data < pivot)
			{
				if (sHead == nullptr)
					sHead = sTail = head;
				else
				{
					sTail->next = head;
					sTail = head;
				}
			}
			else if (head->data > pivot)
			{
				if (bHead == nullptr)
					bHead = bTail = head;
				else
				{
					bTail->next = head;
					bTail = head;
				}
			}
			else
			{
				if (eHead == nullptr)
					eHead = eTail = head;
				else
				{
					eTail->next = head;
					eTail = head;
				}
			}
			head = head->next;
		}
	}
public:
	//1. 借用数组,将链表划分->数组划分,根据数组内容再重新拼接新链表
	Node* listSplit1(Node* head, int pivot)
	{
		if (head == nullptr)return nullptr;
		int n = 0;
		Node* cur = head;
		while (cur)
		{
			n++;
			cur = cur->next;
		}
		vector<Node*>arr(n);
		cur = head;
		int i = 0;
		while (cur)
		{
			arr[i++] = cur;
			cur = cur->next;
		}
		arrPatition(arr, pivot);

		//后竟发现,如果数组存的是节点指针,就可以直接连接,不用再像int类型那样再开空间
		for (int i = 1; i < arr.size(); i++)
		{
			arr[i - 1]->next = arr[i];
		}
		arr[i - 1]->next = nullptr;
		return arr[0];
	}
	void arrPatition(vector<Node*>& arr, int pivot)
	{
		//划分为三个区域 less equal more
		int less = -1, more = arr.size();
		int index = 0;
		while (index < more)
		{
			if (arr[index]->data > pivot)
			{
				swap(arr[more - 1], arr[index]);
				more--;
			}
			else if (arr[index]->data < pivot)
			{
				swap(arr[less + 1], arr[index]);
				index++;
				less++;
			}
			else
				index++;
		}
	}
};