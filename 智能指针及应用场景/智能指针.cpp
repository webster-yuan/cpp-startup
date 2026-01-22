#include<iostream>
using namespace std;
//处理方式: 构建auto_ptr对象时,将T*指针置空,即发生资源管理权转移
//潜在问题:1. 将T*sp=nullptr之后,对象外面并不知晓,可能滥用之后造成野指针问题
//		   2. 没有解决当多个auto_ptr对象指向同一块空间时的调度问题
template<class T>
class my_auto_ptr
{
public:
	//不支持隐士类型转化即 auto_ptr<string> ptr=new string("yuanwei");error
	//						 auto_ptr<string> ptr(string("yuanwei"));success
	explicit my_auto_ptr(T* p)
		_ptr(p)
	{}
	//拷贝构造
	my_auto_ptr(auto_ptr<T>& sp)
		:_ptr(sp._ptr)
	{
		sp._ptr = nullptr;
	}
	~my_auto_ptr()()
	{
		delete _ptr;
		_ptr = nullptr;
	}
public:
	T* operator->()const
	{
		return _ptr;
	}
	T& operator*()const 
	{
		return *_ptr;
	}
private:
	T* _ptr;
};

//处理方式: 1. 为了处理多个对象指向统一空间,不让产生多个对象即将拷贝构造函数赋值构造函数都delete达到防拷贝的效果
//			2. 并不将原来指针置空,避免野指针
//问题: 仍然存在多个对象指向统一空间,比如我就用T*p构造多个对象,那么如何解决多对象的调度问题呢?
template<typename T>
class my_unique_ptr
{
public:
	my_unique_ptr(T* p)
		:_ptr(p)
	{}
	~my_unique_ptr() { delete _ptr; _ptr = nullptr; }

	my_unique_ptr(my_unique_ptr<T>& sp) = delete;
	my_unique_ptr<T>& operator=(my_unique_ptr<T>& sp) = delete;

public:
	T* operator->()
	{
		return _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
private:
	T* _ptr;
};

//处理: 使用计数指针保证一个对象类shared_ptr<T>采用一块资源进行引用计数,
//      为什么不用static类型呢?static类型的属于整个shared_ptr类,也就是说不同T类型的,比如实例化出的string int 都得用着一个,就乱了.
template<typename T>
class my_shared_ptr
{
//private:
	T* _ptr;
	int* _pRefCount;//指向引用计数那块资源的指针,一个shared_ptr<int>类保证只有一个引用计数.但是不同T可以有多块引用计数记录
public:
	my_shared_ptr(T* p)
		:_ptr(p)
		,pRefCount(1)
	{}
	~my_shared_ptr() { delete _ptr;_ptr=nullptr }

	my_shared_ptr(my_shared_ptr<T>& sp)
		:_ptr(sp._ptr)
		,_pRefCount(sp._pRefCount)
	{
		++(*pRefCount);
	}
	my_shared_ptr<T>& operator=(my_shared_ptr<T>& sp)
	{
		if (this != &sp)//避免同一个对象赋值
		{
			//虽然都是shared_ptr类,但是T的不同导致实例化出的对象不是一个,比如share_ptr<int> = share_ptr<string>
			//就需要考虑原来的share_ptr<int>指向的空间是否被释放的问题.
			//所以多这一步
			*_pRefCount--;
			if (*_pRefCount == 0)
			{
				delete _ptr;
				delete _pRefCount;
			}
			//赋值
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			(_pRefCount)++;
		}
		return *this;
	}
public:
	T* operator->()
	{
		return _ptr;
	}
	T& operatpr* ()
	{
		return *_ptr;
	}
	int GetRefCount()
	{
		return *_pRefCount;
	}
};
//问题: 循环引用:node1节点有一个ptr1指向,还有ptr2节点的next指针指向,此时引用计数为2
//		         node2节点有一个ptr2指向,还有ptr1节点的next指针指向,此时引用计数为2
//如果要删除node1节点,让自身ptr1=nullptr,count--,但是count=1,!=0,资源无法delete释放
//同理node2节点,也无法释放,只有一方先释放另一方才能释放.
class Node
{
public:
	std::shared_ptr<Node> next;
	~Node()
	{
		cout << "析构函数" << endl;
	}
};
int main()
{
	std::shared_ptr<Node> ptr1 = std::make_shared<Node>();
	std::shared_ptr<Node> ptr2 = std::make_shared<Node>();

	ptr1->next = ptr1;
	ptr2->next = ptr1;
	system("pause");
	return 0;
}
//`std::weak_ptr` 是用于解决循环引用问题的工具，它可以打破 `std::shared_ptr` 形成的强引用环。`std::weak_ptr` 允许观察（而非拥有）被 `std::shared_ptr` 管理的对象，而不会增加对象的引用计数。
//
//`std::weak_ptr` 主要用于解决循环引用导致的内存泄漏问题。
// 当存在循环引用时，对象间的 `std::shared_ptr` 引用计数无法归零，导致对象无法被正确地销毁，
// 从而造成内存泄漏。通过使用 `std::weak_ptr`，可以将其中一个或多个对象的引用设置为弱引用，
// 这样它们不会增加引用计数，也不会阻止对象的销毁。
//`std::weak_ptr` 具有以下特性和用法：
//1. 创建 `std::weak_ptr`：可以通过将 `std::weak_ptr` 初始化为 `std::shared_ptr` 
// 或通过 `std::shared_ptr` 的 `weak_ptr` 成员函数创建。
// 
//2. 使用 `std::weak_ptr`：可以使用 `std::weak_ptr` 的 `lock` 成员函数获取一个有效的 `std::shared_ptr` 对象
// ，以便访问所管理的对象。`lock` 会检查 `std::shared_ptr` 是否仍然有效，
// 如果有效则返回一个持有对象的 `std::shared_ptr`，否则返回一个空的 `std::shared_ptr`。
//
//3. 判断 `std::weak_ptr` 是否过期(空,或者计数为0)：可以使用 `expired` 成员函数检查 `std::weak_ptr` 是否过期
// （即所管理的对象是否已被销毁）。如果 `expired` 返回 `true`，表示 `std::shared_ptr` 已经被销毁，
// 对象不再可用；如果返回 `false`，则仍有有效的 `std::shared_ptr` 对象可以访问。
//
//通过使用 `std::weak_ptr`，可以打破循环引用的强引用环，允许对象在不再被使用时正常地销毁，避免内存泄漏。
template <typename T>
class my_weak_ptr
{
private:
	T* _ptr;
	int* _pRefC;
public:
	//不是RAII指针,所以不会单独创建对象只用,所以不传T*p.只是针对shared_ptr使用
	my_weak_ptr()
		:_ptr(nullptr)
		, _pRefC(nullptr)
	{}
	~my_weak_ptr() {}

	my_weak_ptr(my_shared_ptr<T>& sp)
		:_ptr(sp._ptr)
		, _pRefC(sp._pRefCount)
	{}
	my_weak_ptr<T>& operator=(my_shared_ptr<T>& sp)
	{
		_ptr = sp.ptr;
		_pRefC = sp._pRefCount;
		return *this;
	}
public:
	my_shared_ptr<T> lock() const {
		if (expired()) {
			return my_shared_ptr<T>();
		}
		else {
			return my_shared_ptr<T>(*this);
		}
	}
	bool expired() const {
		return _pRefC == nullptr || *_pRefC == 0;
	}
public:
	T* operator->() { return _ptr; }
	T& operator*() { return *_ptr; }
};

class Node1
{
public:
	std::weak_ptr<Node1> next;
	~Node1()
	{
		cout << "析构函数" << endl;
	}
};
int main()
{
	std::shared_ptr<Node1> ptr1 = std::make_shared<Node1>();
	std::shared_ptr<Node1> ptr2 = std::make_shared<Node1>();

	ptr1->next = ptr1;
	ptr2->next = ptr1;
	system("pause");
	return 0;
}