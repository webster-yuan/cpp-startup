#pragma once
#include<iostream>
#include<vector>
using namespace std;

// 1. HashFunc的设计以及对于string类型的特化
// 2. HashData数据设计,
// 3. 闭散列设计,线性查找,遇到空位置区分(EMPTY DELETE EXIST),约定遇到空就停止
// 4. 类模版的使用
// 5. 扩容时,构建新对象交换表的做法666
// 6. 查找节点时时刻注意EXIST,找空位置时EMPTY和DELETE的点都可以使用,删除节点时只是将标志位设置为DELETE
//
template<class K>
struct Hash
{
	size_t operator()(const K& key)
	{
		return key;
	}
};
template<>
struct Hash<string>
{
	size_t operator()(const string& key)
	{
		size_t res = 0;
		for (auto e : key)
		{
			res *= 31;
			res += e;//字符ASCII码值相乘和=>size_t 类型
		}
		return res;
	}
};
namespace CloseHash
{
	//闭散列,解决哈希冲突时是将冲突的数据放在后面的空位置
	//所谓的线性探测(遍历查找)的过程中,如果x靠近y,和y冲突的y'放在了x后面,连续放置
	// 如果将x删除之后单纯设置为空的话,当下一次查找y'时到x空位直接停了,就造成查找不到y'
	//遇到空就停止,不知道是删除的还是本来就空的,所以设置标志位enum来区分
	enum STATUS
	{
		EMPTY,
		DELETE,
		EXIST
	};
	template<class K,class V>
	struct HashData
	{
	public:
		pair<K, V> _kv;
		STATUS _st = EMPTY;
	};
	template<class K,class V,class HashFunc=Hash<K>>
	class HashTable
	{
	private:
		vector<HashData<K, V>> _tables;
		size_t n = 0;

	public:
		HashData<K,V>* Find(const K & key)
		{
			if (_tables.size() == 0)
				return nullptr;
			HashFunc hf;
			size_t start = hf(key) % _tables.size();
			size_t i = 0;
			size_t index = start + i;
			while (_tables[index]._st != EMPTY)//约定的查找到空就停止
			{
				if (key == _tables[index]._kv.first && _tables[index]._st == EXIST)
					return &_tables[index];
				i++;
				index = start + i;
				index %= _tables.size();
			}
			return nullptr;
		}
		bool Insert(const pair<K, V>& kv)
		{
			//没找到才插入啊!找到了就不插入了
			if (Find(kv.first) != nullptr)
				return false;
			if (_tables.size() == 0 || n * 10 / _tables.size() == 0.7)
			{
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				//创建新的大表,数据插入到新表中
				//将新对象的表交换
				//随着函数栈帧结束,新对象带着之前的旧表一起消失
				HashTable<K, V, HashFunc> newHT;
				newHT._tables.resize(newSize);
				for (int i = 0; i < _tables.size(); i++)
				{
					if (_tables[i]._st == EXIST)
						newHT.Insert(_tables[i]._kv);
				}
				_tables.swap(newHT._tables);
			}

			HashFunc hf;
			size_t i = 0;
			size_t start = hf(kv.first) % _tables.size();
			size_t index = start + i;
			while (_tables[index]._st == EXIST)
			{
				++i;
				index = start + i;//查找的步伐是可以改变的,线性探测就是一个一个来,找到空就停止
				index %= _tables.size();
			}
			//[index].st=EMPTY | DELETE
			_tables[index]._kv = kv;
			_tables[index]._st = EXIST;
			n++;
			return true;
		}
		//删除节点时只是将标志位设置为DELETE
		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret==nullptr)
				return false;
			else
			{
				--n;
				ret->_st = DELETE;
			}
		}
	};
	void TestHashTable1()
	{
		//HashTable<int, int, Hash<int>> ht;
		HashTable<int, int> ht;

		int a[] = { 2, 12, 22, 32, 42, 52, 62 };
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}
		ht.Insert(make_pair(72, 72));

		cout<<ht.Find(2)->_kv.second<<endl;
		ht.Erase(ht.Find(2)->_kv.first);
	}
	void TestHashTable2()
	{
		/*HashStr hs;
		cout << hs("sort")<<endl;
		cout << hs("insert") << endl;
		cout << hs("eat") << endl;
		cout << hs("ate") << endl;
		cout << hs("abcd") << endl;
		cout << hs("aadd") << endl;*/

		HashTable<string, string> ht;
		ht.Insert(make_pair("sort", "排序"));
		ht.Insert(make_pair("string", "字符串"));

		// 当key是一个定义类型时，需要配置一个仿函数，将key转成整形
		//HashTable<Date, string, HashDate> htds;
	}
}
//int main()
//{
//	CloseHash::TestHashTable1();
//}
namespace LinkHash
{
	template<class K,class V>
	struct HashNode
	{
		pair<K,V> _kv;
		HashNode<K,V>* _next;
		HashNode(const pair<K, V>& d)
			:_kv(d)
			, _next(nullptr)
		{}
	};
	template<class K,class V,class HashFunc=Hash<K>>
	struct HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		bool Erase(const K& key)
		{
			HashFunc hf;
			int index = hf(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						_tables[index] = cur->next;
					}
					else
					{
						prev->_next = cur->next;
					}
					--_n;
					delete cur;
					cur = nullptr;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
		Node* find(const K& key)
		{
			if (_tables.size() == 0)
				return nullptr;
			HashFunc hf;
			int index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			while (cur)
			{
				if (cur->_kv.first == key)
					return cur;
				cur = cur->_next;
			}
			return nullptr;
		}
		bool Insert(const pair<K, V>& kv)
		{
			HashFunc hf;
			Node* ret = find(kv.first);
			if (ret)
				return false;
			if (_n == _tables.size())
			{
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				vector<Node* >newHT;
				newHT.resize(newSize);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t index = hf(cur->_kv.first) % newHT.size();
						cur->_next = newHT[index];
						newHT[index] = cur;
						cur = next;
					}
					_tables[i] = nullptr;//每处理完一个就将链表结尾->nullptr
				}
				_tables.swap(newHT);
			}
			size_t index = hf(kv.first) % _tables.size();
			Node* newNode = new Node(kv);
			newNode->_next = _tables[index];
			_tables[index] = newNode;
			++_n;
			return true;
		}
	private:
		vector<Node*> _tables;
		size_t _n = 0;
	};
	void TestHashTable()
	{
		int a[] = { 4, 24, 14,7,37,27,57,67,34,14,54 };
		HashTable<int, int> ht;
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Insert(make_pair(84, 84));
	}
}
int main()
{
	LinkHash::TestHashTable();
}