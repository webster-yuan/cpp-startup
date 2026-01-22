#include<iostream>
#include<stack>
using namespace std;

class ReverseStack
{
public:
	void reverseStack(stack<int>& st)
	{
		if (st.empty())
			return;
		else
		{
			int i = getAndRemoveLastElement(st);
			reverseStack(st);
			st.push(i);
		}
	}
	//获取并移除栈底元素,递归函数中return 的一直是last,在empty()之前就是这个栈底元素返回
	int getAndRemoveLastElement(stack<int>& st)
	{
		int result = st.top(); st.pop();
		if (st.empty())
			return result;
		else
		{
			int last = getAndRemoveLastElement(st);
			st.push(result);
			return last;
		}
	}
};
int main()
{
	ReverseStack s;
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	s.reverseStack(st);
	return 0;
}