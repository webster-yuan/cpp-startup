#include<iostream>
#include<stack>
using namespace std;
//1. 压入时,如果比min_st顶更小,就两个栈都压入
//2. 弹出时,如果和min_st栈顶相同,就需要两个都弹出
//1_: 维持min_st中从底到顶是逐渐减小的 
//2_: 避免出现最小栈中含有已经应该弹出的元素
class MinStack
{
private:
	stack<int>data_st;
	stack<int>min_st;
public:
	void push(int num)
	{
		data_st.push(num);
		if (min_st.empty())
			min_st.push(num);
		else
		{
			int top_ = min_st.top();
			if (num <= top_)
				min_st.push(top_);
		}
	}
	int pop()
	{
		if (!data_st.empty())
		{
			int top_ = data_st.top();
			data_st.pop();
			if (top_ == min_st.top())
				min_st.pop();
			return top_;
		}
	}
	int getMin()
	{
		if (!min_st.empty())
			return min_st.top();
	}
};