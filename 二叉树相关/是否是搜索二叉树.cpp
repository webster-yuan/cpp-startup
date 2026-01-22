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
		,left(nullptr)
		,right(nullptr)
	{}
};
//中序遍历肯定是有序的
int preVal = INT_MIN;
struct Func1
{
	bool checkBST(Node* head)
	{
		if (head == nullptr)return true;
		bool isLeftBST = checkBST(head->left);
		if (isLeftBST == false) return false;
		if (head->data < preVal)return false;
		else preVal = head->data;
		bool isRightBST = checkBST(head->right);
		return isRightBST;
	}
};

struct Func2
{
	void process(Node* head, vector<Node*>& arr)
	{
		if (head == nullptr)return;
		process(head->left, arr);
		arr.push_back(head);
		process(head->right, arr);
	}
	bool checkBST2(Node* head)
	{
		vector<Node*>arr;
		process(head, arr);
		//遍历检查是否是升序
		for (auto e : arr)
		{
			if (preVal > e->data)
				return false;
			preVal = e->data;
		}
		return true;
	}
};
//非递归的方式检查是否是搜索二叉树,一层层的左边界进入栈中,然后弹栈比较大小
struct Func3
{
	bool checBSTUnRecur(Node* head)
	{
		if (head == nullptr) return true;
		stack<Node*> st;
		while (head && !st.empty())
		{
			if (head != nullptr)
			{
				st.push(head);
				head = head->left;
			}
			else
			{
				//到最左节点了,需要弹出他的父亲节点进行比较,如果还有右孩子,就再进右一层的左边界
				head=st.top(); st.pop();
				if (preVal > head->data)
					return false;
				preVal = head->data;
				head = head->right;
			}
		}
		return true;
	}
};
//使用左神二叉树递归套路
//左子树是否搜索+maxVal 右子树是否搜索+minVal,并集元素
struct Func4
{
	struct ReturnData
	{
		int maxVal;
		int minVal;
		bool isBST;
		ReturnData(bool a, int b, int c)
			:isBST(a)
			, maxVal(b)
			, minVal(c)
		{}
	};
	bool checkBST(Node* head)
	{
		return process(head)->isBST;
	}
	ReturnData* process(Node* head)
	{
		if (head == nullptr)return nullptr;

		ReturnData* left = process(head->left);
		ReturnData* right = process(head->right);

		int maxVal = head->data;
		int minVal = head->data;

		if (left)
		{
			maxVal = max(maxVal, head->data);
			minVal = min(minVal,head->data);
		}
		if (right)
		{
			maxVal = max(maxVal, head->data);
			minVal = min(minVal, head->data);
		}
		bool isBST = true;
		if (left && (left->isBST == false || left->maxVal > head->data))
			return false;
		if (right && (right->isBST == false || right->minVal < head->data))
			return false;
		return &ReturnData(isBST,maxVal,minVal);
	}
};