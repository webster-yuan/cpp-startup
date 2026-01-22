#include<iostream>
using namespace std;
template<class T>
class my_weak_ptr
{
private:
	T* ptr;
	int* pRefCount;
public:
	my_weak_ptr()
		:ptr(nullptr)
		, pRefCount(nullptr)
	{}
	my_weak_ptr(my_shared_ptr<T*>& sp)
		:ptr(sp.ptr)
		, pRefCount(sp.pRefCount)
	{}//并不会增加循环引用计数
	my_weak_ptr<T*> operator=(my_shared_ptr<T*>& sp)
	{
		_ptr = sp.ptr;
		pRefCount = sp.pRefCount;
	}
public:
	my_shared_ptr<T*> lock()//`lock` 成员函数获取一个有效的 `std::shared_ptr` 对象
	{
		if (expired())
		{
			return my_shared_ptr<T*>(*this);
		}
		else
			return nullptr;
	}
	bool expired()//所管理的对象是否已被销毁
	{
		return ptr == nullptr || *pRefCount == 0;
	}
};
template<class T>
class my_shared_ptr
{
public:
	T* ptr;
	int* pRefCount;
public:
	my_shared_ptr(T* p)
		:ptr(p)
		, pRefCount(new int(1))
	{}
	my_shared_ptr(my_shared_ptr<T*>& sp)
		:ptr(sp.ptr)
		, pRefCount(sp.pRefCount)
	{
		++(*pRefCount);
	}
	my_shared_ptr<T*> operator= (my_shared_ptr<T*>& sp)
	{
		if (this != &sp)
		{
			--(*pRefCount);
			if (*pRefCount == 0)
			{
				delete ptr;
				delete pRefCount;
			}
			ptr = sp.ptr;
			pRefCount = sp.pRefCount;
			++(*pRefCount);
		}
	}
};
//线程安全的shared_ptr
#include<atomic>
template<typename T>
class mySharedPtr
{
private:
	T* ptr;
	std::atomic<int>refCount;
public:
	//禁止单参数的隐士类型转换之后构造
	explicit mySharedPtr(T* p)
				:ptr(p)
				,refCount(1)
	{}
	mySharedPtr(mySharedPtr<T*>& sp)
		:ptr(sp.ptr)
	{
		refCount.store(sp.refCount.load());
		refCount.fetch_add(1);
	}
	mySharedPtr<T*> operator=(mySharedPtr<T*>& sp)
	{
		if (this != sp)
		{
			release();
			ptr = sp.ptr;
			refCount = sp.refCount;
			refCount.fetch_add(1);
			return *this;
		}
	}
private:
	void release()
	{
		if (refCount.fetch_sub(1) == 0)
		{
			delete ptr;
		}
	}
};
#include<mutex>
template<class T>
class ThreadSafe
{
public:
	ThreadSafe(T* p)
		:ptr(p)
		, pRef(new int(1))
	{}
	ThreadSafe(ThreadSafe<T*>& sp)
	{
		std::lock_guard<std::mutex> lock(sp.mtx);//因为要修改sp的引用计数,所以确保他的线程安全
		ptr = sp.ptr;
		pRef = sp.pRef;
		++(*pRef);
	}
	ThreadSafe<T*> operator=(ThreadSafe<T*>& sp)
	{
		if (this != sp)
		{
			ThreadSafe tmp(sp);
			my_swap(sp);
			return *this;
		}
	}
	~ThreadSafe()
	{
		release();
	}
private:
	void release()
	{
		std::lock_guard<std::mutex>lock(mtx);
		if (--(*pRef) == 0)
		{
			delete ptr;
			delete pRef;
		}
	}
	my_swap(ThreadSafe<T*>& sp)
	{
		std::lock_guard<mutex>lock1(mtx);//它访问我时我的资源安全
		std::lock_guard<mutex>lock2(sp.mtx);//我访问它时他的资源安全

		std::swap(ptr, sp.ptr);
		std::swap(pRef, sp.pRef);
	}
private:
	T* ptr;
	int* pRef;
	std::mutex mtx;
};