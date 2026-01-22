#include<iostream>
#include<algorithm>
using namespace std;
string to_string1(int a)
{
	string str;
	while (a)
	{
		int val = a % 10;
		str += '0' + val;//+=后面是右值,string operator+=(string && s) 走右值引用实现的移动构造
							//实现资源转移,减少拷贝
		a /= 10;
	}
	reverse(str.begin(),str.end());
	return str;//无编译器优化:返回值调用拷贝构造生成临时变量(右值)如果有ret接收,直接调用移动构造->ret
}
int main()
{
	//左值引用
	int a = 10;
	int& b = a;
	//右值引用本身就是左值,可以&
	int x = 10, y = 20;
	int&& a = 10 + 20; 
	int* ptr = &a;
	int b = max(10,20);

	//左值引用+const 可以引用右值
	const int& c = 10 + 20;
	//右值引用move之后的左值
	int&& d = move(a);
}

//1. 移动构造相对于拷贝构造: 
// 传参:移动构造,右值引用,可以直接交给新构建的对象swap()(一次资源转移)
//      拷贝构造,左值引用,仍需要生成新的临时变量tmp(拷贝构造),然后swap()
//2. 函数返回值,本身是右值
// 编译器不优化且有string ret接收:
//	如果没有移动构造,一次拷贝构造生成临时变量tmp(右值),另一次拷贝构造用tmp->ret,两次拷贝构造
//	如果没有移动构造,一次拷贝构造生成临时变量tmp(右值),接下来直接调用移动构造,走一次资源转移
// 
//3. 有移动赋值:走两次资源转移,移动构造+移动赋值
//   无移动赋值:一次资源转移,一次深拷贝,移动构造->临时变量,走拷贝构造->ret
//
//传参的时候是引用,不发生什么拷贝构造临时变量啥的.