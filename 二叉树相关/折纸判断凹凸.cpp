#include<iostream>
using namespace std;

//对折n次,从上往下生成二叉树结构,根节点左节点都为凹,右节点都为凸
void printProcess(int i, int n, bool down)
{
	if (i > n)return;
	printProcess(i+1,n,true);
	cout << down ? "凹" : "凸";
	printProcess(i+1,n,false);
}
void print(int n)
{
	printProcess(i, n, true);
}