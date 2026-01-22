#include<iostream>
using namespace std;
class Node
{
public:
	int data;
	Node* left;
	Node* right;
	Node* parent;
	Node(int d = -1)
		:data(d)
		, left(nullptr)
		, right(nullptr)
		,parent(nullptr)
	{}
};
//1. 如果node节点有右子树,那么他的后继结点就是右子树的最左节点
//2. 如果node节点没有右子树,需要一直往上找,依据就是左子树
Node* getNode(Node* cur)
{
	if (right == nullptr)return nullptr;
	while (cur)
	{
		cur = cur->left;
	}
	return cur;
}
Node* GetSuccessorNode(Node* node)
{
	if (node == nullptr)return nullptr;
	if (node->right)
		return getNode(node->right);
	else
	{
		Node* parent = node->parent;
		while (parent && node != parent->left)
		{
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
}