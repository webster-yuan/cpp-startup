#pragma once
#include<iostream>
#include<vector>
using namespace std;
namespace LinkHash
{
	template<class T>
	struct Hash
	{
		int operator()(const T& data)
		{
			return data;
		}
	};
	template<>
	struct Hash<string>
	{
		int operator()(const string& d)
		{
			int res = 0;
			for (auto e : d)
			{
				res += e;
				res *= 31;
			}
			return res;
		}
	};
	template<class T>
	class HashData
	{
	public:
		T _data;
		HashData<T>* _next;

		HashData(T d)
			:_data(d)
			, _next(nullptr)
		{}
	};

	template<class K, class T, class KeyOfT, class HashFunc = Hash<T>>
	class HashTable;

	template<class K,class T,class Ptr,class Ref,class KeyOfT,class HashFunc>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef __HTIterator<K, T, Ptr, Ref, KeyOfT, HashFunc> Self;
		//迭代器支持需要节点指针,哈希表指针

		Node* _node;
		HashTable<K, T, KeyOfT, HashFunc>* _pht;

		__HTIterator(Node* node, HashTable<K, T, KeyOfT, HashFunc>* pht)
			:_node(node)
			, _pht(pht)
		{}
	public:
		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}
		Self& operator++()
		{
			if (_node->_next)//此哈希桶还没有结束
				_node = _node->_next;
			else
			{
				//重新确立index
				HashFunc hf;
				KeyOfT kot;
				int index = hf(kot(_node->_data)) % _pht->_tables.size();
				++index;
				//找下一个不是空的桶
				while (index < _pht->_tables.size())
				{
					if (_pht->_tables[index])
						break;
					else
						++index;
				}
				if (index == _pht->_tables.size())
					_node = nullptr;
				else
					_node = _pht->_tables[index];
			}
			return *this;
		}
		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}
		bool operator==(const Self& s) const
		{
			return _node == s._node;
		}
	};
	//KeyOfT模版参数就是为了区分是Key还是pair<Key,Val>
	template<class K,class T,class KeyOfT,class HashFunc=Hash<T>>
	class HashTable
	{
		typedef HashData<T> Node;

		template<class K,class T,class Ptr,class Ref,class KeyOfT,class HashFunc>
		friend struct __HTIterator;

		typedef HashTable<K, T, KeyOfT, HashFunc> Self;
	public:
		//实例化迭代器各种模版类参数
		typedef __HTIterator<K, T, T*, T&, KeyOfT, HashFunc> iterator;
	public:
		HashTable(const Self& ht)
		{
			_tables.resize(ht._tables.size());
			for (int i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					//大小已经和你一样了,只需要创建新节点然后直接连就行了
					Node* copy = new Node(cur->_data);
					copy->_next = _tables[i];
					_tables[i] = copy;

					cur = cur->_next;
				}
			}
		}
		~HashTable()
		{
			for (int i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = nullptr;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
	public:
		Self& operator=(Self& s)
		{
			swap(s._n);
			_tables.swap(s._tables);
			return *this;
		}
		iterator begin()
		{
			//头一个不为空的哈希桶才是begin,不是_tables[0]
			for (int i = 0; i < _tables.size(); i++)
			{
				if (_tables[i])
				{
					return iterator(_tables[i],this);
				}
			}
			return end();
		}
		iterator end()
		{
			return iterator(nullptr,this);
		}
	public:
		bool Erase(const K& key)
		{
			HashFunc hf;
			size_t index = hf(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[index];
			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					if (prev == nullptr)//说明是头删
					{
						_tables[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					--_n;
					delete cur;
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
		iterator find(const K& key)
		{
			if (_tables.size() == 0)
				return iterator(nullptr,this);

			HashFunc hf;
			int index = hf(key) % _tables.size();
			Node* cur = _tables[index];
			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
					return iterator(cur,this);
				cur = cur->_next;
			}
			return end();
		}
		size_t GetNextPrime(size_t num)
		{
			static const unsigned long __stl_prime_list[28] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};
			for (size_t i = 0; i < 28; ++i)
			{
				if (__stl_prime_list[i] > num)
				{
					return __stl_prime_list[i];
				}

			}
			return __stl_prime_list[27];

		}
		pair<iterator,bool> Insert(const T &data)
		{
			HashFunc hf;
			KeyOfT kot;
			iterator ret = find(kot(data));
			if (ret!=end())
				return make_pair(ret,false);

			if (_n == _tables.size())
			{
				int newSize = GetNextPrime(_tables.size());
				if (newSize == _tables.size())//无法再扩容,大小没法大了
					return make_pair(end(), false);
				vector<Node* >newHT;
				newHT.resize(newSize);
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t index = hf(kot(cur->_data)) % newHT.size();
						cur->_next = newHT[index];
						newHT[index] = cur;
						cur = next;
					}
					_tables[i] = nullptr;//每处理完一个就将链表结尾->nullptr
				}
				_tables.swap(newHT);
			}
			size_t index = hf(kot(data)) % _tables.size();
			Node* newNode = new Node(data);
			newNode->_next = _tables[index];
			_tables[index] = newNode;
			++_n;
			return true;
		}
	private:
		vector<Node*> _tables;
		int _n = 0;
	};
}