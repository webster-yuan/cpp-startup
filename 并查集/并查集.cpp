#include<vector>
using namespace std;
////并查集
//开始每个元素都是独立的Element<>,经过Union操作后,让B指向A,A作为B的父亲元素,让C指向D
// A作为自己和B的代表元素,D作为自己和C的,因为AB和CD的代表元素不同,所以认为四者不是同一集合
//Union A C时,让size小的集合的代表元素C指向A,此时A就是四个的代表元素,在同一集合了
//可能会存在链表仍然过长的问题导致O()不是O(1)
//那么优化:某一元素x向上找代表元素时,将他向上找过程中遇到的的父亲的parent指向,都改为A(代表元素)
//使得更加扁扁,效率更高.
//扁平=>O(1) 如果调用findHead次数逼近N,或者超过N次时.
//使用数组的方式实现并查集
class UnionFindSet
{
public:
	UnionFindSet(int size)
		:ufSet(size, -1)
	{}
	size_t FindRoot(int x)
	{
		while (ufSet[x] > 0)
			x = ufSet[x];
		return x;
	}
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		if (root1 != root2)
		{
			ufSet[root1] += ufSet[root2];
			ufSet[root2] = root1;
		}
	}
	size_t getCount()
	{
		size_t count = 0;
		for (size_t i = 0; i < ufSet.size(); i++)
		{
			if (ufSet[i] < 0) count++;
		}
		return count;
	}
private:
	std::vector<int> ufSet;
};

void TestUFS()
{
	UnionFindSet u(10);

	u.Union(0, 6);
	u.Union(7, 6);
	u.Union(7, 8);

	u.Union(1, 4);
	u.Union(4, 9);

	u.Union(2, 3);
	u.Union(2, 5);
	printf("%d\n", u.getCount());
}
//int main()
//{
//	TestUFS();
//	return 0;
//}