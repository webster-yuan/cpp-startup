#include<iostream>
#include<list>
#include<queue>
using namespace std;

class Pet
{
public:
	Pet() = default;
	string petType;
	Pet(string pt)
		:petType(pt)
	{}
	string getType()
	{
		return petType;
	}
};
class Dog :public Pet
{
public:
	Dog()
		:Pet("dog")
	{}
};
class Cat :public Pet
{
public:
	Cat()
		:Pet("cat")
	{}
};
//1. pollAll 按照先后顺序弹出猫或者狗实例
//2. 可以分别弹出猫或者狗队列中的实例,按照先后顺序
//3. 使用add方式将猫狗实例压入

class PetEnterQueue
{
private:
	Pet pet;
	long count;//时间戳记录先后顺序
public:
	PetEnterQueue(Pet& p, long c)
		:pet(p)
		, count(c)
	{}
	Pet getPet()
	{
		return pet;
	}
	int getCount()
	{
		return count;
	}
	string getEnterPetType()
	{
		return pet.getType();
	}
};
//存放指针版本,但是要手动释放内存
class DogCatQueuePtr
{
private:
	queue<PetEnterQueue*> dogQ;
	queue<PetEnterQueue*> catQ;
	long count;

public:
	DogCatQueuePtr()
		:count(0)
	{}
	Dog* pollDog()
	{
		if (!dogQ.empty())
		{
			Dog* ret = (Dog*) &dogQ.front()->getPet();
			delete (dogQ.front());
			dogQ.pop();
			return ret;
		}
	}
	Cat* pollCat()
	{
		if (!dogQ.empty())
		{
			Cat* ret = (Cat*)&catQ.front()->getPet();
			delete (catQ.front());
			catQ.pop();
			return ret;
		}
	}
	void add(Pet& pet)
	{
		if (pet.getType() == "dog")
			dogQ.push(new PetEnterQueue(pet, count++));
		else if (pet.getType() == "cat")
			catQ.push(new PetEnterQueue(pet, count++));
	}

	Pet* pollAll()
	{
		Pet* ret = nullptr;
		if (!dogQ.empty() && !catQ.empty())
		{
			if (dogQ.front()->getCount() < catQ.front()->getCount())
			{
				ret = &(dogQ.front()->getPet());
				delete dogQ.front(); // Free memory for the dequeued element
				dogQ.pop();
			}
			else
			{
				ret = &(catQ.front()->getPet());
				delete catQ.front(); // Free memory for the dequeued element
				catQ.pop();
			}
		}
		else if (!dogQ.empty())
		{
			ret = &(dogQ.front()->getPet());
			delete dogQ.front(); // Free memory for the dequeued element
			dogQ.pop();
		}
		else if (!catQ.empty())
		{
			ret = &(catQ.front()->getPet());
			delete catQ.front(); // Free memory for the dequeued element
			catQ.pop();
		}
		else
			ret = nullptr;
		return ret;
	}

	~DogCatQueuePtr()
	{
		// Release memory for elements in dogQ
		//如果结束时还队列中还有动态申请的堆空间内存
		while (!dogQ.empty())
		{
			delete dogQ.front();
			dogQ.pop();
		}

		// Release memory for elements in catQ
		//如果结束时还队列中还有动态申请的堆空间内存
		while (!catQ.empty())
		{
			delete catQ.front();
			catQ.pop();
		}
	}
};



//class DogCatQueue
//{
//private:
//	queue<PetEnterQueue> dogQ;
//	queue<PetEnterQueue>catQ;
//	long count;
//public:
//	DogCatQueue()
//		:count(0)
//	{}
//	void add(Pet& pet)
//	{
//		if (pet.getType() == "dog")
//			dogQ.push(PetEnterQueue(pet, count++));
//		else if (pet.getType() == "dog")
//			catQ.push(PetEnterQueue(pet, count++));
//	}
//	Pet pollAll()
//	{
//		if (!dogQ.empty() && !catQ.empty())
//		{
//			if (dogQ.front().getCount() < catQ.front().getCount())
//			{
//				Pet ret = dogQ.front().getPet();
//				dogQ.pop();
//				return ret;
//			}
//			else
//			{
//				Pet ret = catQ.front().getPet();
//				catQ.pop();
//				return ret;
//			}
//		}
//		else if (!dogQ.empty())
//		{
//			Pet ret = dogQ.front().getPet();
//			dogQ.pop();
//			return ret;
//		}
//		else if (!catQ.empty())
//		{
//			Pet ret = catQ.front().getPet();
//			catQ.pop();
//			return ret;
//		}
//		else //两个队列都为空
//			return Pet();
//	}
//	Dog pollDog()
//	{
//		if (!dogQ.empty())
//		{
//			Pet ret = dogQ.front().getPet();
//			dogQ.pop();
//			return (Dog)ret;
//		}
//	}
//};