#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include"并查集.hpp"
using namespace std;
template<class V,class W,W MAX_W =INT_MAX,bool Direction =false>
class Graph
{
	typedef Graph<V, W, MAX_W, Direction> self;
private:
	map<V, int> vIndexMap;
	vector<V> vertexs;		  //点集
	vector<vector<W>> matrix; //矩阵存储信息
public:
	struct Edge
	{
		int srci;
		int desti;
		W w;
		Edge(int s, int d, int w1)
			:srci(s)
			, desti(d)
			, w(w1)
		{}
		bool operator>(const Edge& e)
		{
			return w > e.w;
		}
	};
public:
	//单源最短路径-针对有向图-边权值非负
	//dist: 记录srci-其他顶点最短路径权值数组
	//pPath: 记录srci-其他顶点最短路径父顶点数组
	void Dijkstra(const V& src, vector<W>& dist, vector<int>& pPath)
	{
		int srci = GetVertexIndex(src);
		int n = vertex.size();
		dist.resize(n);
		pPath.resize(n, -1);

		dist[srci] = 0;
		dist[srci] = srci;
		vector<bool>S(n, false);//已经确定的最短路径的顶点集合
		//每次从Q 中找出一个起点到该结点代价最小的结点u ，
		//将u 从Q 中移出，并放入S 中，
		//对u 的每一个相邻结点v 进行松弛操作
		for (int j = 0; j < n; j++)
		{
			int u = 0;
			W min = MAX_W;
			for (int i = 0; i < n; i++)
			{
				if (S[i] == false && dist[i] < min)
				{
					min = dist[i];
					u = i;
				}
			}
			S[u] = true;
			//松弛处理: 两条路径选最小,min(src->uParent->u,src->u)
			for (int v = 0; v < n; v++)
			{
				if (!S[v] && matrix[u][v] != MAX_W && 
					dist[u] + matrix[u][v] < dist[v])
				{
					dist[v] = dist[u] + matrix[u][v];
					pPath[v] = u;
				}
			}
		}

	}

public://最小生成树
	// Prim算法: 给定一个src后,选择相连的最小边. 贪心+逐步推导
	W Prim(self& minTree, const V& src)
	{
		int srci = GetVertexIndex(src);
		int sz = vertex.size();
		//1. 初始化
		vertexs = minTree.vertexs;
		vIndexMap = minTree.vIndexMap;
		int m = minTree.matrix.size();
		int n = minTree.matrix[0].size()
			matrix.resize(m);
		for (int i = 0; i < m; i++)
			matrix[i].reize(n, MAX_W);
		//2. 首先将与src相连的所有点的边入小堆,每次获取srci相连的最小边
		priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
		for (int i = 0; i < n; i++)
		{
			if (matrix[srci][i] != MAX_W)
				pq.push(Edge(srci, i, matrix[srci][i]));
		}
		//3. 选边,选择最小边终点没用过的,Y[i]=false,避免出现环
		//	要选够节点-1条边,返回最小生成树的累加total

		vector<int>X(sz, false);//X[i]=true代表i这个点用过
		vector<int>Y(sz, false);//Y[i]=true代表i这个点没用过
		X[srci] = true, Y[srci] = false;
		int size = 0;
		W total = W();

		while (!pq.empty())
		{
			Edge min = pq.top(); pq.pop();
			if (X[min.desti])//最小边目标点在X集合中,代表已经选过了
			{}
			else
			{
				minTree.AddEdge(min.srci, min.desti, min.w);
				X[min.desti] = true, Y[min.desti] = false;
				++ size;
				total += min.w;
				if (size == sz - 1)
					break;
				//
				for (int i = 0; i < n; i++)
				{
					if (matrix[srci][i] != MAX_W && Y[i])
						pq.push(Edge(srci, i, matrix[srci][i]));
				}
			}
		}
		if (size == sz - 1)
			return total;
		else
			return W();
	}
	// Kruskal算法: 在图中的所有边中,选出最小的边. 贪心+逐步推导
	W Kruskal(self& minTree)
	{
		//1. 初始化
		vertexs = minTree.vertexs;
		vIndexMap = minTree.vIndexMap;
		int m = minTree.matrix.size();
		int n= minTree.matrix[0].size()
		matrix.resize(m);
		for (int i = 0; i < m; i++)
			matrix[i].reize(n, MAX_W);
		//2. 根据邻接矩阵的权值构建边,放到小堆中,每次获取整个图中的最小边
		priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i < j && matrix[i][j] != MAX_W)
					pq.push(Edge(i, j, matrix[i][j]));
			}
		}
		//3. 构建最小生成树,为了避免选到重复点,在选择边时使用并查集
		//	 选中节点个数-1条边
		int sz = vertex.size();
		UnionFind ufs(sz);
		int size = 0;//规定选出sz-1条边
		W total = W();

		while (!pq.empty())
		{
			Edge min = pq.top(); pq.pop();
			if (!ufs.IsOneSet(min.srci, min.desti))
			{
				minTree.AddEdge(min.srci, min.desti, min.w);
				ufs.Union(min.srci, min.desti);
				++size;
				total += min.w;
			}
			else {}//说明选中了的最小边两个点是一个集合的,说明已经选过了,就不用选了
		}
		if (size == sz - 1)
			return total;
		else
			return W();
	}
public:
	void dfs(int&index, vector<bool>& visi)
	{
		cout << index << ":" << vertexs[index] << endl;
		visi[index] = true;
		for (int i = 0; i < vertex.size(); i++)
		{
			if (matrix[index][i] != MAX_W && !visi[i])
				dfs(i, visi);
		}
	}
	void DFS(const V& src)
	{
		int srci = GetVertexIndex(src);
		vector<bool> visi;
		int n = vertexs.size();
		visi.resize(n, false);

		dfs(srci,visi);
	}
	//按层输出
	void BFSLevel(const V& src)
	{
		int srci = GetVertexIndex(src);
		vector<bool> visi;
		int n = vertexs.size();
		visi.resize(n, false);
		queue<int>q;
		q.push(srci);
		visi[srci] = true;

		int levelSize = 1;
		while (!q.empty())
		{
			for (int i = 0; i < levelSize; i++)
			{
				int front = q.front(); q.pop();
				cout << front << ":" << vertexs[front] << " ";
				for (int i = 0; i < n; i++)
				{
					if (matrix[front][i] != MAX_W && !visi[i])
					{
						q.push(i);
						visi[i] = true;
					}
				}
			}
			cout << endl;
			levelSize = q.size();
		}
	}
	void BFS(const V&src)
	{
		int srci = GetVertexIndex(src);
		vector<bool> visi;
		int n = vertexs.size();
		visi.resize(n, false);
		
		queue<int>q;
		q.push(srci);
		visi[srci] = true;
		while (!q.empty())
		{
			int front = q.front(); q.pop();
			cout << front << ":" << vertexs[front] << " ";
			//将front的邻接点都放进来
			for (int i = 0; i < n; i++)
			{
				if (matrix[front][i] != MAX_W && !visi[i])
				{
					q.push(i);
					visi[i] = true;
				}
			}
		}
	}
public:
	Graph() = default;

	void AddEdge(const V& src, const V& dest, const W& w)
	{
		int srci = GetVertexIndex(src);
		int desti = GetVertexIndex(dest);
		_AddEdge(srci, desti, w);
	}
	void _AddEdge(int srci, int desti, const W& w)
	{
		matrix[srci][desti] = w;
		if (Direction == false)
			matrix[desti][srci] = w;
	}
	int GetVertexIndex(const V& v)
	{
		auto it = vIndexMap.find(v);
		if (it != vIndexMap.end())
			return it->second;
		else
		{
			cout << "不存在这个点" << endl;
			return -1;
		}
	}
	Graph(const V* a, int n)
	{
		vertexs.reserve(n);
		for (int i = 0; i < n; i++)
		{
			vertexs.push_back(a[i]);
			vIndexMap[a[i]] = i;
		}
		matrix.resize(n);
		for (int i = 0; i < n; i++)
			matrix.resize(n, MAX_W);
	}
};