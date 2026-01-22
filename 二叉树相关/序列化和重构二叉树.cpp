#include<iostream>
#include<list>
using namespace std;
class Node
{
public:
	string data;
	Node* left;
	Node* right;
	Node(string d = "")
		:data(d)
		, left(nullptr)
		, right(nullptr)
	{}
};
//中序序列化二叉树
string Serialize(Node* head)
{
	if (head == nullptr)return "#!";
	string res = head->data + "!";
	Serialize(head->left);
	Serialize(head->right);
	return res;
}
//重构二叉树,返回头结点
Node* ReConstruct(string &str)
{
	list<string> res = my_split(str,"!");
	return process(res);
}
Node* process(list<string>& str)
{
	string val = str.front(); str.pop_front();
	if (val == "#")
		return nullptr;
	Node* node = new Node(val);
	node->left = process(str);
	node->right = process(str);
	return node;
}
list<string> my_split(string& str,const string& sep)
{
	list<string> res;
	char* tmp = new char(str.size()+1);
	strcpy(tmp,str.c_str());
	char* s = strtok(tmp, sep.c_str());
	while(s)
	{
		res.push_back(s);//string 内置char*单参数构造函数,所以可以实现隐士构造
		s = strtok(NULL, sep.c_str());
	}
	return res;
	delete tmp;
}