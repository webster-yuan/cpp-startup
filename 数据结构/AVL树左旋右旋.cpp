#include<iostream>
using namespace std;
//https://blog.csdn.net/weixin_58843717/article/details/129297240
class Node
{
public:
	int val;
	Node* left;
	Node* right;
	Node* parent;
	int bf;	//每个节点自带的负载因子
};
class AVLTree
{
private:
	Node* root;
public:
	//因为单旋都是将涉及的两个节点bf置为0,不符合实际
	//例子画图理解平衡因子更新注意:
	//90->left=30 30->right=60; 新增之前90->bf=-1  30->bf=0;
	//60->bf =1 说明60->right=newNode; 60->bf=-1说明60->left=newNode
	//新增之后90->bf=-2 30->bf=1 先以30为中心进行左旋,再以90为中心右旋
	//旋转之后发现30->bf=1不变,60->bf自然为0,
	//if 60->bf=1 ,90->bf=-1 ;if 60->bf=-1,90->bf=1
	void RotateLeftRight(Node* parent)
	{
		Node* subl = parent->left;
		Node* sublr = subl->right;
		int sublr_bf = sublr->bf;
		RotateLeft(subl);
		RotateRight(parent);
		if (sublr_bf == 1)
			parent->bf = -1;
		else if (sublr_bf == -1)
			parent->bf = 1;
		else
		{}
	}
	//记不住状态更新就画图
	//例子理解: 90->right=30,30->left=60;30->bf=0,90->bf=1;
	//60->bf =1 说明60->right=newNode; 60->bf=-1说明60->left=newNode
	//新增之后90->bf=2 30->bf= -1 先以30为中心进行右旋,再以90为中心左旋
	//旋转之后发现不变,60->bf自然为0,
	//if 60->bf=1 ,90->bf=-1; if 60->bf=-1,30->bf=-1
	void RotateRightLeft(Node* parent)
	{
		Node* subr = parent->right;
		Node* subrl = subr->left;
		int subrl_bf = subrl->bf;
		RotateRight(subr);	//subr->bf=-1<0,说明左边高,就右旋
		RotateLeft(parent);//parent->bf=2>0,说明右边高,就左旋
		if (subrl_bf == -1)
		{
			//parent->bf = 0;
			subr->bf = 1;
		}
		else if (subrl->bf == 1)
		{
			parent->bf = -1;
			//subr->bf=0;
		}
		else
		{}
	}
	void RotateLeft(Node* parent)
	{
		Node* subr = parent->right;
		Node* subrl = subr->left;
		//1. 
		subrl->parent = parent;
		parent->right = subrl;
		
		Node* pparent = parent->parent;
		//2.
		subr->left = parent;
		parent->parent = subr;
		//
		if (parent == root)
		{
			subr = root;
			subr->parent = nullptr;
		}
		else
		{
			if (parent == pparent->left)
				pparent->left = subr;
			else
				pparent->right = subr;
			subr->parent = pparent;
		}
		subr->bf = parent->bf = 0;
	}
	void RotateRight(Node* parent)
	{
		Node* subl = parent->left;
		Node* sublr = subl->right;
		//1.
		parent->left = sublr;
		if (sublr)
			sublr->parent = parent;
		Node* pparent = parent->parent;
		//2. 
		subl->right = parent;
		parent->parent = subl;
		//3. 
		if (parent == root)
		{
			subl = root;
			subl->parent = nullptr;
		}
		else
		{
			if (pparent->left == parent)
				pparent->left = subl;
			else
				pparent->right = subl;
			subl->parent = pparent;
		}
		subl->bf = parent->bf = 0;
	}
};