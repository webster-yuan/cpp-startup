#include<iostream>
#include<vector>
#include<stack>
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
// 左右子树都是平衡,height
pair<int, bool> process(Node* head)
{
	if (head == nullptr) return {0,true};
	pair<int, bool> left = process(head->left);
	pair<int, bool> right = process(head->right);
	int height = max(left.first, right.first);
	bool isBalanced = left.second && right.second && abs(left.first - right.first) <= 1?true : false;
	return {height,isBalanced};
}
bool isBalancedTree(Node* head)
{
	return process(head).second;
}