#include<iostream>
#include<vector>
using namespace std;
//观察者模式（Observer Pattern）的主要作用是实现对象之间的一对多依赖关系，当一个对象的状态发生变化时，所有依赖它的对象都会得到通知并自动更新。
//
//主要作用如下：
//
//1. 解耦观察者和被观察者：观察者模式将观察者和被观察者解耦，使它们之间的关系松散，
//	 观察者不需要知道被观察者的具体细节，只需要关注被观察者的状态变化。
//
//2. 支持广播通知：当被观察者的状态发生改变时，不需要手动通知每个观察者，而是由被观察者自动通知所有注册的观察者。
//   这样可以实现一次通知，多个观察者同时响应的效果，类似于广播通知。
//
//3. 实现事件处理：观察者模式可以用于实现事件处理和发布 - 订阅模型。当某个事件发生时，被观察者可以充当事件的发布者，
//   而观察者可以作为订阅者，通过注册订阅关系来接收事件通知并做出响应。
//
//4. 多级触发：观察者模式可以支持多级触发，即一个观察者的状态改变也可能触发其他观察者的状态改变，
//   从而实现一系列触发和响应。
//
//总的来说，观察者模式在软件设计中是一种非常有用的设计模式，它促进了松耦合、可维护和可扩展的设计。
//通过使用观察者模式，我们可以更好地处理对象之间的依赖关系，从而使代码更加灵活和易于维护。
class Observer;
class Subject
{
//private:
protected:
	vector<Observer*> observers;
public:
	void addObserver(Observer* obs)
	{
		observers.push_back(obs);
	}
	void removeObserver(Observer* obs)
	{
		auto it = find(observers.begin(),observers.end(),obs);
		if (it != observers.end())
			observers.erase(it);
	}
	void notifyObserver()
	{
		for (auto obs : observers)
		{
			obs->update();
		}
	}
	//设置为纯虚函数
	virtual int getState() const = 0;
};
class Observer
{
public:
	virtual void update() = 0;
};
class ConcreteSubject : public Subject
{
private:
	int _state;
public:
	void setState(int state)
	{
		_state = state;
		notifyObserver();
	}
	int getState() const override /*不让重写*/
	{
		return _state;
	}
};
class ConcreteObserver : public Observer
{
private:
	ConcreteSubject* subject;
public:
	ConcreteObserver(ConcreteSubject* sub) :subject(sub) {}
	void update()override
	{
		int state = subject->getState();
		std::cout << "Observer: Received state update. New state is " << state << std::endl;
	}
};
int main() {
	ConcreteSubject subject;

	ConcreteObserver observer1(&subject);
	ConcreteObserver observer2(&subject);

	subject.addObserver(&observer1);
	subject.addObserver(&observer2);

	subject.setState(123);

	subject.removeObserver(&observer1);

	subject.setState(456);

	return 0;
}


