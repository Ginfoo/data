#pragma once
#include <cstdlib>
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

typedef struct edge
{
	int dest;
	int cost;
	edge* next;
} edge;

typedef struct ver
{
	char data;
	edge* adj;
} ver;

class graph
{
public:
	enum GType { Dgraph, UDgrapg };

	explicit graph(int maxVers, GType g_t = GType::UDgrapg);
	graph(const graph& g);
	graph(graph&&) = delete;
	graph& operator=(const graph& g);
	graph& operator=(graph&&) = delete;
	~graph();

	bool insertEdge(char s, char d, int cost);
	bool insertVer(char s);
	bool removeEdge(char s, char d);
	bool removeVer(char s);
	int getVerPos(char s) const;

	GType g_type;

	friend ostream& operator<<(ostream& os, const graph& g);


private:
	int maxVers;
	int numVers;
	ver* verTable;
	bool insertOneWayEdge(const char s, const char d, const int cost);
	bool insertOneWayEdge(int s_pos, int d_pos, int cost = 1);
	bool removeOneWayEdge(int s_pos, int d_pos);
	bool isSafePos(int pos) const;
	bool removeOneWayEdge(char s, char d);
	bool removeVer(int s_pos);
};

inline ostream& operator<<(ostream& os, const graph& g)
{
	if (g.g_type == graph::GType::UDgrapg)
		cout << "无向图:";
	else
		cout << "有向图:";
	for (int i = 0; i < g.numVers; i++)
	{
		cout << endl << i<<" : "<<g.verTable[i].data << "    ";
		edge* t_e = g.verTable[i].adj;
		while (t_e != nullptr)
		{
			cout << t_e->dest << "(" << t_e->cost << ")     ";
			t_e = t_e->next;
		}
	}
	return os;
}

inline graph::graph(int maxVers, GType g_t): maxVers(maxVers), g_type(g_t), numVers(0)
{
	this->verTable = new ver[maxVers];
	for (int i = 0; i < maxVers; i++)
	{
		verTable[i].data = '0';
		verTable[i].adj = nullptr;
	}
}

inline graph::graph(const graph& g)
{
	this->g_type = g.g_type;
	this->maxVers = g.maxVers;
	this->numVers = g.numVers;
	this->verTable = new ver[maxVers];

	for (int i = 0; i < maxVers; i++)
	{
		ver t_ver = this->verTable[i];
		edge* t_cur_e = t_ver.adj;//这里疑问 

		edge* g_cur_e = g.verTable[i].adj;
		while (g_cur_e != nullptr)
		{
			edge* n_edge = static_cast<edge*>(malloc(sizeof(edge)));
			n_edge->dest = g_cur_e->dest;
			n_edge->cost = g_cur_e->cost;
			n_edge->next = nullptr;
			if (t_ver.adj == nullptr)
			{
				t_ver.adj = n_edge;
			}
			else
			{
				t_cur_e->next = n_edge;
				t_cur_e = t_cur_e->next;
			}
			g_cur_e = g_cur_e->next;
		}
	}
}

inline graph& graph::operator=(const graph& g)
{
	if (this == &g)return *this;
	if (this->verTable != nullptr) delete[] verTable;
	this->g_type = g.g_type;
	this->maxVers = g.maxVers;
	this->numVers = g.numVers;
	this->verTable = new ver[maxVers];

	for (int i = 0; i < maxVers; i++)
	{
		ver t_ver = this->verTable[i];
		edge* t_cur_e = t_ver.adj;

		edge* g_cur_e = g.verTable[i].adj;
		while (g_cur_e != nullptr)
		{
			edge* n_edge = static_cast<edge*>(malloc(sizeof(edge)));
			n_edge->dest = g_cur_e->dest;
			n_edge->cost = g_cur_e->cost;
			n_edge->next = nullptr;
			if (t_ver.adj == nullptr)
			{
				t_ver.adj = n_edge;
			}
			else
			{
				t_cur_e->next = n_edge;
				t_cur_e = t_cur_e->next;
			}
			g_cur_e = g_cur_e->next;
		}
	}
	return *this;
}

inline graph::~graph()
{
	for (int i = 0; i < maxVers; i++)
	{
		edge* t_cur_e = this->verTable[i].adj;
		while (t_cur_e != nullptr)
		{
			edge* temp = t_cur_e;
			t_cur_e = t_cur_e->next;
			free(temp);
		}
	}
	delete[] verTable;
}

inline bool graph::insertEdge(char s, char d, int cost)
{
	if (this->g_type == UDgrapg)
	{
		bool b1 = insertOneWayEdge(s, d, cost);
		bool b2 = insertOneWayEdge(d, s, cost);
		if (b1 || b2)return true;
		else return false;
	}
	else
	{
		return insertOneWayEdge(s, d, cost);
	}
}

inline bool graph::insertVer(char s)
{
	if (this->getVerPos(s) != -1)return false;
	else
	{
		int s_pos = numVers;
		this->verTable[s_pos].data = s;
		this->verTable[s_pos].adj = nullptr;
		this->numVers += 1;
		return true;
	}
}

inline bool graph::removeEdge(char s, char d)
{
	if (this->g_type == GType::Dgraph)
	{
		return removeOneWayEdge(s, d);
	}
	else
	{
		bool b1 = removeOneWayEdge(s, d);
		bool b2 = removeOneWayEdge(d, s);
		if (b1 || b2)return true;
		else return false;
	}
}

inline bool graph::removeVer(char s)
{
	int s_pos = this->getVerPos(s);//找到该定点位置
	if (s_pos == -1)return false;

	return removeVer(s_pos);
}

inline int graph::getVerPos(char s) const
{
	for (auto i = 0; i < numVers; i++)
	{
		if (this->verTable[i].data == s)return i;
	}
	return -1;
}

inline bool graph::insertOneWayEdge(const char s, const char d, const int cost)
{
	const auto s_pos = this->getVerPos(s);
	const auto d_pos = this->getVerPos(d);
	return insertOneWayEdge(s_pos, d_pos, cost);
}

inline bool graph::insertOneWayEdge(int s_pos, int d_pos, int cost)
{
	if (!isSafePos(s_pos) || !isSafePos(d_pos))return false;
	edge* t_edge = this->verTable[s_pos].adj;
	while (t_edge != nullptr && t_edge->dest != d_pos)
	{
		t_edge = t_edge->next;
	}
	if (t_edge != nullptr)return false;
	else
	{
		edge* e = static_cast<edge*>(malloc(sizeof(edge)));
		e->dest = d_pos;
		e->cost = cost;
		e->next = this->verTable[s_pos].adj;
		this->verTable[s_pos].adj = e;
		return true;
	}
}

inline bool graph::removeOneWayEdge(int s_pos, int d_pos)
{
	if (!isSafePos(s_pos) || !isSafePos(d_pos))return false;
	edge* t_edge = this->verTable[s_pos].adj;
	edge* t_edge_prior = nullptr;//标记前一个节点
	while (t_edge != nullptr && t_edge->dest != d_pos)
	{
		t_edge_prior = t_edge;
		t_edge = t_edge->next;
	}
	if (t_edge == nullptr)return false;//没有找到 返回false
	else
	{
		if (t_edge_prior == nullptr)//找到，但前一个节点为nullptr 说明该节点为首节点
		{
			this->verTable[s_pos].adj = t_edge->next;//链接该节点下一个
			free(t_edge);
		}
		else
		{
			t_edge_prior->next = t_edge->next;
			free(t_edge);
		}
		return true;
	}
}

inline bool graph::isSafePos(int pos) const
{
	if (pos < 0 || pos > numVers - 1)return false;
	return true;
}

inline bool graph::removeOneWayEdge(char s, char d)
{
	int s_pos = this->getVerPos(s);//获取s 的下标
	int d_pos = this->getVerPos(d);//获取d 的下标

	return removeOneWayEdge(s_pos, d_pos);//调用私有函数
}

inline bool graph::removeVer(int s_pos)
{
	if (!isSafePos(s_pos))return false;
	else
	{
		/*
		 * 删除该顶点出边
		 * 删除该顶点的入边
		 * 用最后一个顶点顶替该位置
		 * 修改原指向最后一个顶点的边的dest
		 */
		int last_pos = numVers - 1;//最后一个顶点的下标
		//删除该顶点的出边
		edge* t_edge = this->verTable[s_pos].adj;
		this->verTable[s_pos].adj = nullptr;//方便后面操作
		edge* p;
		while (t_edge != nullptr)
		{
			p = t_edge;
			t_edge = t_edge->next;
			free(p);
		}
		//删除该顶点的入边
		for (int i = 0; i < numVers; i++)
		{
			removeOneWayEdge(i, s_pos);
		}
		numVers -= 1;

		if (last_pos != s_pos)//如果删除的不是最后一个节点
		{
			//把最后一个节点转移到要删除的地方
			this->verTable[s_pos].adj = this->verTable[last_pos].adj;
			this->verTable[s_pos].data = this->verTable[last_pos].data;
			this->verTable[last_pos].adj = nullptr;
			//修改原指向last_pos的边
			int new_pos = s_pos;
			for (int i = 0; i < numVers; i++)
			{
				edge* c_edge = this->verTable[i].adj;
				while (c_edge != nullptr)
				{
					if (c_edge->dest == last_pos)
					{
						c_edge->dest = new_pos;
						break;
					}
					c_edge = c_edge->next;
				}
			}
		}

		return true;
	}
}
