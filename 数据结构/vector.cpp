#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;
namespace yuanwei
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
	public:
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}
	public:
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		iterator begin() 
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
	public:
		//[]使用的是断言,at()使用的是抛异常
		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}
		T& operator[](size_t i)
		{
			return _start[i];
		}
		size_t size()
		{
			return _finish - _start;
		}
		size_t capacity()
		{
			return _endofstorage - _start;
		}
	public:
		//memcpy是浅拷贝,将_start内容完全拷贝到tmp中,
		//包括每个_str的各个指针_Ptr也浅拷贝下来,在析构函数进行释放的时候就会造成释放两次相同的空间造成崩溃.
		//实现深拷贝,新创建一块空间,让_start指向过去
		void reserve(int n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				//异地扩容
				T* tmp = new T[n];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * size());
					delete[] _start;
				}
				//更新指针指向新空间各个位置
				_start = tmp;
				_finish = _start + sz;
				_endofstorage = _start + n;
			}
		}
		void resize(size_t n, T val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
					reserve();
				//在新开辟的空间初始化
				while (_finish != _start + n)
				{
					*_finish = val;
					_finish++;
				}
			}
		}
		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			*_finish = x;
			++_finish;
		}
		void pop_back()
		{
			if (_finish > _start)
				--_finish;
		}
		void clear()
		{
			_finish = _start;
		}
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start && pos <= _finish);
			//扩容
			if (_finish == _endofstorage)
			{
				int n = pos - _start;
				int newCap = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCap);
				//涉及到异地扩容导致pos原来迭代器失效
				pos = _start + n;
			}
			//挪动数据
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = val;
			++_finish;
			return pos;
		}
		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);
			//vector删除元素使用向前覆盖的方式
			iterator it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				++it;
			}
			--_finish;
			return pos;
		}
	public:
		//拷贝构造
		//1. 开空间,memcpy初始化
		vector(vector<T>& v)
		{
			_start = new T[v.size()];
			_finish = _start + v.size();
			_endofstorage = _start + v.capacity();
			memcpy(_start, v._start, v.size() * sizeof(T));
		}
		//2. 支持迭代器区间初始化
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		//3. 拷贝构造一个,交换,但是注意析构函数不能析构随机值
		/*vector(vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			vector<T>tmp(v.begin(), v.end());
			swap(_start, tmp._start);
			swap(_finish, tmp._finish);
			swap(_endofstorage, tmp._endofstorage);
		}*/
	public:
		//赋值构造
		vector<T>& operator=(vector<T> v)//使用传值传参,参数本身就是一分拷贝构造,直接交换
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endofstorage, v._endofstorage);
			return *this;
		}
	public:
		vector(int n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(n);
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
	void test_vector1()
	{
		vector<int >v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		auto it = v.begin();
		while (it != v.end())
		{
			cout << *it << endl;
			it++;
		}
	}
	void test_vector3()
	{
		// 在所有的偶数的前面插入20
		vector<int> v;
		//v.reserve(10);
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);

		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				it = v.insert(it, 20);
				++it;
			}

			++it;
		}

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
	void test_vector4()
	{
		vector<int> v;
		//v.reserve(10);
		v.push_back(1);
		v.push_back(2);
		v.push_back(2);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(4);
		v.push_back(5);
		cout << v.size() << ":" << v.capacity() << endl;
		auto pos = find(v.begin(), v.end(), 4);
		if (pos != v.end())
		{
			v.erase(pos);
		}

		cout << *pos << endl;
		*pos = 10;
		cout << *pos << endl << endl;

		cout << v.size() << ":" << v.capacity() << endl;

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}
int main()
{
	yuanwei::test_vector4();
}
//int main2()
//{
//	int sz = 0;
//	vector<int>v1;
//	sz = v1.size();
//	for (int i = 0; i < 100; i++)
//	{
//		v1.push_back(i);
//		if (sz != v1.capacity())
//		{
//			sz = v1.capacity();
//			cout << sz << endl;
//		}
//	}
//	return 0;
//}
//int main1()
//{
//	string name = "yuanweiyuanweiyunawei ";
//	auto it1 = name.find("yuan");
//	cout << it1 << endl;//0
//
//	vector<char> v1(name.begin(), name.end());
//
//	cout << sizeof(v1) << endl;
//	return 0;
//}