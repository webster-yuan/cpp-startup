#include<iostream>
#include<stack>
using namespace std;
//1． 如果 stackPush 要往 stackPop 中压入数据，那么必须一次性把 stackPush 中的数据全部压入。
//2． 如果 stackPop 不为空， stackPush 绝对不能向 stackPop 中压入数据。
class MyQueue
{
private:
	stack<int> pushSt;
	stack<int>popSt;
public:
	void pushTopop()
	{
		if (popSt.empty())
		{
			while (!pushSt.empty())
			{
				popSt.push(pushSt.top());
				pushSt.pop();
			}
		}
	}
	void push(int num)
	{
		pushSt.push(num);
	}
	int pop()
	{
		if (popSt.empty() && pushSt.empty())
			return -1;
		pushTopop();
		int ret=popSt.top();
		popSt.pop();
		return ret;
	}
	int top()
	{
		if (popSt.empty() && pushSt.empty())
			return -1;
		pushTopop();
		return popSt.top();
	}
};