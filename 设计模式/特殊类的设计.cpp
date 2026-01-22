#include<iostream>
using namespace std;
//一.只能在堆上设计对象
//1. 构造函数肯定私有化,拷贝构造也删除
//2. 静态成员函数返回对象,并使用new实现在堆上.调用类内函数就得有对象,有对象的前提是有构造函数,
//为了避免套娃使用静态成员函数属于整个类,使用类名调用
class HeapOnly
{
public:
	static HeapOnly* get()
	{
		return new HeapOnly();
	}
	void print()
	{
		cout << _a << endl;
	}
private:
	HeapOnly():_a(0) {}
	HeapOnly(const HeapOnly& hp) = delete;
private:
	int _a;
};
int main1()
{
	HeapOnly* ins = HeapOnly::get();
	ins->print();
	return 0;
}
//二. 只能在栈上创建对象.屏蔽new,底层调用的是operator new
//1. 为甚要将构造函数私有化呢?
//		确保对象的构造函数和析构函数不执行任何动态内存分配（例如使用new）或其他需要手动释放的资源。
//		因为new就是调用类的构造函数+初始化
//2. 将对象的成员变量和方法设计为不依赖于 动态内存分配 的类型和操作。
//3. 避免在对象的构造函数和析构函数中调用其他可能导致动态内存分配的函数。
//4. 在需要创建对象的作用域中，直接声明对象的变量。例如，可以在函数内部声明对象的局部变量。
class StackOnly
{
public:
	static StackOnly get()
	{
		return StackOnly();
	}
	void print()
	{
		cout << _a << endl;
	}
private:
	StackOnly() :_a(0) {};
	void* operator new(size_t x) = delete;//分配函数第一个参数必须是size_t 类型
	void operator delete(void *p) = delete;
private:
	int _a;
};
int main2()
{
	StackOnly obj = StackOnly::get();
	obj.print();
	system("pause");
}
//三.该类不能发生拷贝
//饿汉模式单例模式:程序开始的时候就预备好了.使用饿汉模式的单例模式可以保证在程序启动时就创建实例，
// 因此是线程安全的。
//然而，它可能会导致程序启动时的性能开销，因为实例会在程序开始时就被创建，无论是否需要使用该实例。
class NoCopy
{
public:
	NoCopy* getInstance()
	{
		return ins;
	}
private:
	NoCopy() {};//设置为私有,否则无法使用new
	NoCopy(const NoCopy& np) = delete;
	NoCopy operator=(const NoCopy& np) = delete;
private:
	int _a;
	static NoCopy* ins;
};
NoCopy* NoCopy::ins = new NoCopy();
//懒汉模式单例模式:等到类调用的时候再创建,涉及到线程安全问题
class Single
{
public:
	Single* getIns()
	{
		ins = new Single();
		return ins;
	}
private:
	Single() {};//设置为私有别delete,否则无法使用new
	Single(const Single& np) = delete;
	Single operator=(const Single& np) = delete;
private:
	int _a;
	static Single* ins;
};
 Single* Single::ins=nullptr;

//四.设计类不能被继承
//阻止其他类从该类派生 C++11使用final C++98将构造函数设置为私有,子类无法看见就无法实现初始化无法派生
 class NoInherit final
 {
 public:

 };
 class A
 {
 public:
	 static A* get()
	 {}
 private:
	 A() {}
 };