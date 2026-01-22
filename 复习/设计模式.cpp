#include<iostream>
#include<vector>
using namespace std;
//工厂模式
//实现工厂创建对象和客户端代码解耦.当之后新增其他图形时,只需要修改工厂的代码,客户端直接传参用就行
class Shape
{
public:
	virtual void draw() = 0;
};
class Circle :public Shape
{
public:
	void draw()
	{}
};
class Rectangle :public Shape
{
public:
	void draw()
	{}
};
class ShapeFactory
{
public:
	static Shape* getShape(const string& s)
	{
		if (s == "Circle")
			return new Circle();
		else if (s == "Rectangle")
			return new Rectangle();
		else
			return nullptr;
	}
};
void test_Factory()
{
	Shape* circle = ShapeFactory::getShape("Cirlce");
}
//观察者模式: 
//实现对象之间一对多的依赖关系,当一个对象发生变化时,依赖他的要进行状态更新
//1. 只需要关注被观察者的状态
//2. 被观察者有观察者的注册表,方便增加和删除观察者和广播观察者更新状态
//3. 这种机制可以抽象为订阅模型,被观察者负责事件的发布,观察者作为订阅者通过注册订阅关系接收事件并做出相应
class Observer
{
public:
	virtual void update() = 0;
};
class Subject
{
public:
	void add(Observer* ob)
	{
		observers.push_back(ob);
	}
	void erase(Observer* ob)
	{
		auto it = find(observers.begin(), observers.end(),ob);
		if (it != observers.end())
			observers.erase(it);
	}
	virtual int getState()const = 0;
public:
	void notify()//广播机制
	{
		for (auto e : observers)
		{
			e->update();
		}
	}
private:
	vector<Observer*> observers;
};
class CncrectSub : public Subject
{
public:
	int state;
	void set()
	{}
	void reset()
	{}
	int getState() const override
	{}
};
class ConcrectObs : public Observer
{
public:
	CncrectSub* cb;
	ConcrectObs(CncrectSub* sb)
		:cb(sb)
	{}
public:
	virtual void update() override
	{
		int s = cb->getState();
		std::cout << "Observer: Received state update. New state is " << s << std::endl;
	}
};
//单例模式
//饿汉模式
class Single
{
public:
	static Single* getInstance()
	{
		return ins;
	}
private:
	Single()
	{}
	Single(Single& sp) = delete;
	Single operator=(Single& sp) = delete;
private:
	int a;
	static Single* ins;
};
Single* Single::ins = new Single();
//懒汉模式:
class Single
{
public:
	static Single* getInstance()
	{
		return new Single();
	}
private:
	Single()
	{}
	Single(Single& sp) = delete;
	Single operator=(Single& sp) = delete;
private:
	int a;
	static Single* ins;
};
Single* Single::ins = nullptr;

//特殊类的设计
//1. 只能在堆上申请空间
template<class T>
class HeapOnly
{
public:
	HeapOnly<T>* get()
	{
		return new HeapOnly<T>();
	}
private:
	HeapOnly()
	{}
	HeapOnly(const HeapOnly<T>& sp) = delete;
private:
	T a;
};
//2. 只能在栈上申请空间
//屏蔽operator new operator delete的同时,将构造函数也设置为私有
//new = operator new+构造函数
//构造函数私有不能实例化出对象,就得给人家一个可以不通过对象就可以调用的函数,来创建一个对象static成员函数
class StackOnly
{
public:
	static StackOnly get()
	{
		return StackOnly();
	}
private:
	StackOnly()
		:a(1)
	{}
	void* operator new(size_t x) = delete;
	void operator delete(void* p) = delete;
private:
	int a;
};
//3. 不能被继承的类
//C++11使用final C++98将构造函数设置为私有
class B final
{};
class A
{
public:
	static A getA()
	{
		return A();
	}
private:
	A()
	{}
};
