#include<iostream>
#include<list>
using namespace std;
int main1()
{
	list<int> lt1;
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	//1. 只支持迭代器访问
	list<int>::iterator it1 = lt1.begin();
	while (it1 != lt1.end())
	{
		//cout << *it1 << endl;
		it1++;
	}
	//2. splice()函数,将节点移动到链表的其他位置(LRU实现代码中用到)
	list<int> lt2;
	lt2.push_back(2);
	lt2.push_back(2);
	lt2.push_back(2);
	lt2.push_back(2);
	lt2.push_back(3);
	//lt1.splice(lt1.begin(),lt2);//将lt2所有元素移动到lt1.begin()之前
	lt1.splice(lt1.begin(), lt2, find(lt2.begin(),lt2.end(),3));
	list<int>::iterator it = lt1.begin();
	advance(it,3);//让it指向3元素所在节点
	while (it != lt1.end())
	{
		cout << *it << endl;
		it++;
	}
	system("pause");
	return 0;
}
//list是双向链表哦!!!
namespace yuanwei
{
	template<class T>
	class Node
	{
	public:
		T data;
		Node<T> * next;
		Node<T>* prev;
		Node(T d=T())
			:data(d)
			, next(nullptr)
			, prev(nullptr)
		{}
	};
	//因为list并不向vector一样内存空间是连续的,支持指针,所以就自己封装一个迭代器,让他像指针一样,方便操作
	template<class T,class Ref=T&,class Ptr=T*>//T ,T& ,T*
	class __list_iterator
	{
	public:
		typedef Node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> self;
	//private:
		Node* node;
	public:
		__list_iterator(Node* n)
			:node(n)
		{}
		//节点本身不属于迭代器,所以不用释放node
		~__list_iterator()
		{}
		//因为实现的是迭代器,拷贝构造啥的是浅拷贝也没关系,因为想要的就是指向同一块节点,而且资源释放也不归迭代器管,所以
		//用默认生成的浅拷贝没毛病
	public:
		Ref operator*()
		{
			return node->data;
		}
		Ptr operator->()
		{
			return &node->data;
		}
		//前置++,让迭代器指向下一个位置
		self& operator++()
		{
			node = node->next;
			return *this;
		}
		//后置++,返回的还是之前的
		self operator++(int)
		{
			self tmp(*this);
			node = node->next;
			return tmp;
		}
		//前置--,让迭代器指向前一个位置
		self& operator--()
		{
			node = node->prev;
			return *this;
		}
		//后置++,返回的还是之前的
		self operator--(int)
		{
			self tmp(*this);
			node = node->prev;
			return tmp;
		}
		//!=判断的是两个迭代器是否指向的同一个节点,并不是判断值相等!!!
		bool operator!=(const self& it)
		{
			return node != it.node;
		}
		bool operator==(const self& it)
		{
			return node == it->node;
		}
	};
	template<class T>
	class list
	{
	public:
		typedef Node<T> Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef const __list_iterator<T, T&, T*> const_iterator;
	private:
		Node* head;
	public:
		list()
		{
			head = new Node();
			head->next = head;
			head->prev = head;
		}
		~list()
		{
			delete head;
			head = nullptr;
		}
	public:
		//list是双向链表  end()(head)->begin()->.....->tail->end()(head)
		iterator begin()//指向容器的起始位置
		{
			return iterator(head->next);
		}
		iterator end()//指向容器最后一个元素的下一个位置
		{
			return iterator(head);
		}
		const_iterator begin() const
		{
			return const_iterator(head->next);
		}
		const_iterator end()const 
		{
			return const_iterator(head);
		}
	public:
		void push_back(const T& val)
		{
			/*Node* tail = head->prev;
			Node* newNode = new Node(val);
			newNode->prev = tail;
			newNode->next = head;
			head->prev = newNode;
			tail->next = newNode;*/
			insert(end(), val);
		}
		void push_front(const T& x)
		{
			insert(begin(),x);
		}
		void pop_front()
		{
			erase(begin());
		}
		void pop_back()
		{
			erase(--end());
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
	public:
		//默认插在pos位置前
		iterator insert(iterator pos, const T& val)
		{
			Node* newNode = new Node(val);
			Node* cur = pos.node;
			Node* prev = cur->prev;

			newNode->next = cur;
			prev->next = newNode;
			newNode->prev = prev;
			cur->prev = newNode;
			return iterator(newNode);
		}
		//默认将删除节点的后一个节点迭代器返回
		iterator erase(iterator pos)
		{
			assert(pos != end());
			Node* cur = pos.node;
			Node* prev = cur->prev;
			Node* next = cur->next;

			prev->next = next;
			next->prev = prev;
			delete cur;
			return iterator(next);
		}
	public:
		void empty_init()
		{
			head = new Node();
			head->next = head;
			head->prev = head;
		}

		//经典写法->拷贝构造-> 深拷贝
		/*list(const list<T>& lt)
		{
			empty_init();
			for (auto e : lt)
			{
				push_back(e);
			}
		}*/
		//拷贝构造,迭代器区间
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		//现代写法2,使用迭代器区间初始化一个tmp
		list(const list<T>& lt)
		{
			empty_init();//将之前链表置空,交换给tmp之后,调用析构函数完成资源释放.避免交换之后析构函数无法析构随机值

			list<T> tmp(lt.begin(), lt.end());
			swap(head,tmp.head);
		}
		////现代写法1,使用构造函数构造一个tmp
		//list(const list<T>& lt)
		//{
		//	empty_init();
		//	list<T> tmp(lt);///////////error,得在list()哪里添加参数,但是不太行
		//	swap(head, tmp.head);
		//}

		//赋值构造
		list<T>& operator=(const list<T>& lt)
		{
			if (this != &lt)
			{
				empty_init();
				for (auto e : lt)
				{
					push_back(e);
				}
			}
			return *this;
		}
		list<T>& operator=(list<T> lt)
		{
			swap(head, lt.head);
			return *this;
		}
	};
	void printList(const list<int>& lt)
	{
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << "->";
			++it;
		}
		cout << endl;
	}
	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//*it = 20;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		printList(lt);

		list<int>lt2(lt);
		list<int>::iterator it2 = lt2.begin();
		while (it2 != lt2.end())
		{
			//*it = 20;
			cout << *it2 << " ";
			++it2;
		}
		cout << endl;
	}
}
int main()
{
	yuanwei::test_list1();
	return 0;
}