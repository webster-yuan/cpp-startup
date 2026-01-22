#pragma once

template<class K, size_t M>
struct BTreeNode
{
	//应该是M-1个关键字,M个孩子.为了方便插入再分裂,就都多给了一个空间
	K _keys[M];
	BTreeNode<K, M>* _subs[M + 1];
	BTreeNode<K, M>* _parent;
	size_t _n;
	BTreeNode()
	{
		for (int i = 0; i < M; i++)
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[M] = nullptr;
		_parent = nullptr;
		_n = 0;
	}
};
template<class K, size_t M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	pair<Node*, int> Find(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			size_t i = 0;//某一节点的下标
			while (i < cur->_n)//节点现有关键字数
			{
				if (key < cur->_keys[i])
				{
					break;
				}
				else if (key > cur->_keys[i])
				{
					++i;//往右走找更大的值去比
				}
				else
				{
					return make_pair(cur, i);
				}
			}
			//每次向下一层走记录父亲节点,便于当Insert时返回需要应该在哪里插入
			parent = cur;
			cur = cur->_subs[i];
			//1. 是break出来的,就指定往下走
			//2. 是i==_n即此节点遍历完了,需要往下一层走,此时i=n,正好是孩子的最后一个节点下标
		}
		return make_pair(parent, -1);//没找到
	}
	void InsertKey(Node* cur, const K& key, Node* child)
	{
		int end = cur->_n - 1;
		while (end >= 0)
		{
			if (key < cur->_keys[end])
			{
				cur->_keys[end + 1] = cur->_keys[end];//挪动数据的时候孩子也得跟着走
				cur->_subs[end + 2] = cur->_subs[end + 1];
				--end;
			}
			else
			{
				break;
			}
		}
		//end=-1,在0位置插入
		//break出来,在比较的下一个位置直接插入就行
		cur->_keys[end + 1] = key;
		cur->_subs[end + 2] = child;//插入的时候将孩子也连上
		cur->_n++;
		if (child)
		{
			child->_parent = cur;
		}
	}
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_n++;
			return true;
		}
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)
		{
			return false;
		}

		Node* cur = ret.first;
		K newKey = key;
		Node* child = nullptr;
		while (1)
		{
			InsertKey(cur, newKey, child);
			if (cur->_n < M)//M 个关键字时就满了
			{
				return true;
			}
			else
			{
				//分裂一半值给bro keys[mid+1,M-1]以及subs[]
				size_t mid = M / 2;
				Node* broNode = new Node;
				int j = 0;
				size_t i = mid + 1;
				for (i; i <= M - 1; i++)
				{
					//带着左孩子一起走(还剩最后一个右孩子)
					broNode->_keys[j] = cur->_keys[i];
					broNode->_subs[j] = cur->_subs[i];
					//换爹了别忘了
					if (cur->_subs[i])
						cur->_subs[i]->_parent = broNode;
					++j;
					cur->_keys[i] = K();//清理一下
					cur->_subs[i] = nullptr;
				}
				//还剩最后一个右孩子
				broNode->_subs[j] = cur->_subs[i];
				if (cur->_subs[i])
					cur->_subs[i]->_parent = broNode;
				cur->_subs[i] = nullptr;

				broNode->_n = j;
				cur->_n -= j + 1;//还有一个给了父亲
				//更新的是根节点,就新产生新的根
				if (cur->_parent == nullptr)
				{
					_root = new Node;
					_root->_keys[0] = cur->_keys[mid];
					cur->_keys[mid] = K();

					_root->_subs[0] = cur;
					_root->_subs[1] = broNode;
					_root->_n = 1;
					cur->_parent = _root;
					broNode->_parent = _root;
					break;
				}
				else
				{
					//向上继续调整
					//往cur->parent去插入cur->keys[mid] 和broNdoe节点
					newKey = cur->_keys[mid];
					cur->_keys[mid] = K();
					child = broNode;
					cur = cur->_parent;
				}
			}
		}
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	void _InOrder(Node* cur)
	{
		if (cur == nullptr)
			return;
		size_t i = 0;
		for (i; i < cur->_n; i++)
		{
			_InOrder(cur->_subs[i]);
			cout << cur->_keys[i] << " ";
		}
		_InOrder(cur->_subs[i]);
	}
private:
	Node* _root = nullptr;
};



void TestBtree()
{
	int a[] = { 53, 139, 75, 49, 145, 36, 101 };
	BTree<int, 3> t;
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
}
