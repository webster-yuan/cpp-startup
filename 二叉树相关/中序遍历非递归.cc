#include<iostream>
#include<stack>
using namespace std;
class TreeNode
{
	public:
	int data;
	TreeNode* left;
	TreeNode* right;
};
typedef TreeNode Node;
void inorderNoRecur(Node* root)
{
	if (root == nullptr)return;
	stack<Node*>st;
	Node* cur = root;
	while (cur || !st.empty())
	{
		//将左边界入栈
		while (cur != nullptr)
		{
			st.push(cur);
			cur = cur->left;
		}
		//此时栈顶是最左节点
		cur = st.top(); st.pop();
		//do thing!
		cout << cur->data << " ";
		cur = cur->right;
	}
}