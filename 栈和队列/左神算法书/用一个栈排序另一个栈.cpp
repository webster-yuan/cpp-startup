
#include<iostream>
#include<stack>
using namespace std;

class SortStackWithAnotherStack
{
private:
	stack<int>help;
public:
	//1. 要实现st中从栈顶到栈底是从大到小,先让help中是从小到大,然后重新压入st即可
	//2. 如果cur>help.top(), while help.pop(); else help.push(cur)
	void sortStack(stack<int>& st)
	{
		while (!st.empty())
		{
			int cur = st.top(); st.pop();
			while (!help.empty() && cur < help.top())
			{
				st.push(help.top());
				help.pop();
			}
			help.push(cur);
		}
		//别忘了将剩余的放回st
		while (!help.empty())
		{
			st.push(help.top());
			help.pop();
		}
	}
	void f(stack<int>& st)
	{
		while (!st.empty())
		{
			int cur = st.top(); st.pop();
			if (help.empty() || cur < help.top())
				help.push(cur);
			else
			{
				//一直弹栈,并且放入st中
				while (cur > help.top())
				{
					st.push(help.top());
					help.pop();
				}
				help.push(cur);
			}
		}
	}
};