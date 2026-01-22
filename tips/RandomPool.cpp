#include<iostream>
#include<unordered_map>
using namespace std;

//设计RandomPool结构
//【 题目】
//设计一种结构， 在该结构中有如下三个功能 :
//insert(key) : 将某个key加入到该结构， 做到不重复加入
//delete(key) : 将原本在结构中的某个key移除
//getRandom() : 等概率随机返回结构中的任何一个key。
//【 要求】
//Insert、 delete和getRandom方法的时间复杂度都是O(1)
//
//在没有删除的时候, 可以认为是连续26个空间, 等概率返回即可.
//
//有删除行为, 硬删之后会在0~25区间有很多的洞, 要保证连续, 让最后一条记录index = size - 1, 得到str, 让str去填洞, 让他的index = 3(要删除的index), 删掉最后一条和你要删除的那条, 此时空间是连续的.
//
//使用两张哈希表<str, index> <index, str>

template<class Key>
class RandomPool
{
public:
	RandomPool()
	{ 
		size = 0; 
	}
public:
	void Insert(Key key)
	{
		if (keyIndexMap.find(key) == keyIndexMap.end())
		{
			keyIndexMap.insert(make_pair(key,size));
			indexKeyMap.insert(make_pair(size++, key));
		}
	}
	void Delete(Key key)
	{
		if (keyIndexMap.find(key) == keyIndexMap.end())
			return;
		int delIndex = keyIndexMap[key];
		int lastIndex = --size;
		Key lastKey = indexKeyMap[lastIndex];

		keyIndexMap[lastKey] = delIndex;
		indexKeyMap[delIndex] = lastKey;

		keyIndexMap.erase(key);
		indexKeyMap.erase(lastIndex);
	}
	Key GetRandom()
	{
		if (size == 0)
			return Key();
		int randomIndex = (int)(rand() % size);//[0,size-1]
		return indexKeyMap[randomIndex];
	}
private:
	unordered_map<Key, int> keyIndexMap;
	unordered_map<int, Key> indexKeyMap;
	int size;
};
int main()
{
	RandomPool<string> pool;
	pool.Insert("yuanwei1");
	pool.Insert("yuanwei2");
	pool.Insert("yuanwei3");
	cout<<pool.GetRandom()<<endl;
	cout<<pool.GetRandom()<<endl;
	cout<<pool.GetRandom()<<endl;
}