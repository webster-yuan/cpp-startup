#include<iostream>
#include<vector>
using namespace std;

typedef class TreeNode
{
public:
	int val;
	TreeNode* left;
	TreeNode* right;

public:
	TreeNode(int v = -1)
		:val(v)
		, left(nullptr)
		, right(nullptr)
	{}
}Node;

//递归的思路理解一下
//我首先是一个合法的位置,我创建我自己的头结点,我相信createTree()函数能帮我处理好我的子树之后返回在那,
//然后用我的指针连起来,代表以我为头的树建立好了,我再返回我的头指针.
Node* createTree(vector<int>& nums, int n, int index)
{
	if (index > n || nums[index] == -1)
		return nullptr;

	Node*  node = new Node(nums[index]);
	node->left = createTree(nums, n, index * 2 + 1);
	node->right = createTree(nums, n, index * 2 + 2);
	return node;
}