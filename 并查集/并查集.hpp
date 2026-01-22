#include<iostream>
#include<vector>
using namespace std;
//并查集的建立:
//1. 数组的下标对应集合中元素的编号
//2. 数组中如果为负数，负号代表根，数字代表该集合中元素个数
//3. 数组中如果为非负数，代表该元素双亲在数组中的下标

//并查集一般可以解决一下问题：
//1. 查找元素属于哪个集合: 沿着数组表示树形关系以上一直找到根(即：树中中元素为负数的位置)
//2. 查看两个元素是否属于同一个集合: 
//		沿着数组表示的树形关系往上一直找到树的根，如果根相同表明在同一个集合，否则不在
//3. 将两个集合归并成一个集合,将两个集合中的元素合并,将一个集合名称改成另一个集合的名称
//4. 集合的个数.遍历数组，数组中元素为负数的个数即为集合的个数。

class UnionFind
{
private:
	vector<int> ufs;
public:
	//1. 首先提供你想描述多少元素之间的关系吧!
	UnionFind(int n)
		:ufs(n, -1)
	{}
	int FindRoot(int index)
	{
		//往前找的过程中发现还没到负数,也就是说明还没到根
		while (ufs[index]>=0)
			index = ufs[index];
		return index;
	}
	//联合的过程只需要将集合的头指向另一个集合的头即可,注意数目得累加上
	bool Union(int x1,int x2)
	{
		//1. 先找头
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		//2. 如果是一家的,就不用合并
		if (root1 == root2)
			return false;
		//3. 不是一家的,先让root2集合个数累加到root1上,然后让root2指向root1
		ufs[root1] += ufs[root2];
		ufs[root2] = root1;
		return true;
	}
	int Count()
	{
		int count = 0;
		for (int i = 0; i < ufs.size(); i++)
			if (ufs[i] < 0)
				count++;
		return count;
	}
	bool IsOneSet(int x, int y)
	{
		return FindRoot(x) == FindRoot(y);
	}
};