
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#define  N 10
typedef struct Node
{
	int data;
	struct Node* next;
}Node;
Node* AllocNode(int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		printf("malloc failed");
		exit(1);
	}
	node->data = data;
	node->next = NULL;
}
void InsertNode(Node* head,int val)
{
	assert(head);
	Node* newnode = AllocNode(val);
	newnode->next = head->next;
	head->next = newnode;
}
void ShowList(Node* cur)
{
	assert(cur);
	cur = cur->next;
	while (cur)
	{
		printf("%d ",cur->data);
		cur = cur->next;
	}
	printf("->NULL\n");
}
void DeleteNode(Node* head)
{
	assert(head);
	Node* p = head->next;
	head->next = p->next;
	free(p);
	p = NULL;
}
int main()
{
	Node* head = AllocNode(0);
	printf("插入开始:\n");
	for (int i = 1; i < 10; i++)
	{
		InsertNode(head,i);
		ShowList(head);
		Sleep(1000);
	}
	printf("删除开始:\n");
	for (int i = 1; i < 10; i++)
	{
		DeleteNode(head);
		ShowList(head);
		Sleep(1000);
	}
	system("pause");
	return 0;
}