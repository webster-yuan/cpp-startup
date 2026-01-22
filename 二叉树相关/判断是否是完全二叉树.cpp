#include<iostream>
#include<queue>
using namespace std;
class Node
{
public:
	int data;
	Node* left;
	Node* right;
	Node(int d = -1)
		:data(d)
		, left(nullptr)
		, right(nullptr)
	{}
};
bool isCompleteBT(Node* head)
{
	queue<Node*> q;
	q.push(head);
	Node* left = nullptr, *right = nullptr;
	bool isLeafNode = false;
	while (!q.empty())
	{
		Node* front = q.front(); q.pop();
		left = front->left;
		right = front->right;
		//之前已经到达叶子结点了,那么这个节点必须是叶子结点才能是完全二叉树
		if (isLeafNode && (front->left != nullptr && front->right != nullptr) || (front->left == nullptr && front->right != nullptr))
			return false;
			if (left)
			q.push(left);
		if (right)
			q.push(right);
		if (left == nullptr && right == nullptr)
			isLeafNode = true;
	}

}