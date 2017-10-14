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

	friend ostream& operator<<(ostream& os, const graph& g)
	{
		if (g.g_type == GType::UDgrapg)
			cout << "无向图:";
		else
			cout << "有向图:";
		for (int i = 0; i < g.numVers; i++)
		{
			cout << endl << g.verTable[i].data << "    ";
			edge* t_e = g.verTable[i].adj;
			while (t_e != nullptr)
			{
				cout << t_e->dest << "(" << t_e->cost << ")     ";
				t_e = t_e->next;
			}
		}
		return os;
	}

private:
	int maxVers;
	int numVers;
	ver* verTable;

	bool insertOneWayEdge(char s, char d, int cost)
	{
		int s_pos = this->getVerPos(s);
		int d_pos = this->getVerPos(d);
		if (s_pos == -1 || d_pos == -1)return false;
		edge* t_cur_e = this->verTable[s_pos].adj;
		while (t_cur_e != nullptr)
		{
			if (t_cur_e->dest == d_pos)return false;
			t_cur_e = t_cur_e->next;
		}
		edge* n_edge = static_cast<edge*>(malloc(sizeof(edge)));
		n_edge->dest = d_pos;
		n_edge->cost = cost;
		n_edge->next = this->verTable[s_pos].adj;
		this->verTable[s_pos].adj = n_edge;
		return true;
	}

	bool removeOneWayEdge(char s, char d)
	{
		int s_pos = this->getVerPos(s);
		int d_pos = this->getVerPos(d);
		edge* t_cur_e = this->verTable[s_pos].adj;
		if (t_cur_e == nullptr)return false;
		if (t_cur_e->dest == d_pos)
		{
			edge* temp = t_cur_e;
			this->verTable[s_pos].adj = t_cur_e->next;
			free(temp);
			return true;
		}
		else
		{
			while (t_cur_e->next != nullptr)
			{
				if (t_cur_e->next->dest == d_pos)
				{
					edge* temp = t_cur_e->next;
					t_cur_e->next = t_cur_e->next->next;
					free(temp);
					return true;
				}
				t_cur_e = t_cur_e->next;
			}
		}

		return false;
	}
};

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
		this->numVers++;
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
	int s_pos = this->getVerPos(s);
	if (s_pos == -1)return false;
	edge* t_cur_e = this->verTable[s_pos].adj;
	while (t_cur_e != nullptr)
	{
		int d_pos = t_cur_e->dest;
		if (this->g_type == GType::UDgrapg)//如果是无向图
			removeOneWayEdge(d_pos, s_pos);
		edge* temp = t_cur_e;
		this->verTable[s_pos].adj = t_cur_e->next;
		free(temp);
		t_cur_e = t_cur_e->next;
	}
	if (this->g_type == GType::Dgraph)//如果是有向图
	{
		for (int i = 0; i < numVers; i++)
		{
			removeOneWayEdge(this->verTable[i].data, s);
		}
	}
	//用最后一个顶点顶替该顶点
	if (s_pos != numVers - 1)
	{
		int old_pos = numVers - 1;
		int new_pos = s_pos;
		this->verTable[new_pos].data = this->verTable[old_pos].data;
		this->verTable[new_pos].adj = this->verTable[old_pos].adj;
		numVers--;
		for (int i = 0; i < numVers; i++)
		{
			edge* t_e = this->verTable[i].adj;
			while (t_e != nullptr)
			{
				if (t_e->dest == old_pos)
				{
					t_e->dest = new_pos;
				}
			}
		}
	}
	return true;
}

inline int graph::getVerPos(char s) const
{
	for (auto i = 0; i < numVers; i++)
	{
		if (this->verTable[i].data == s)return i;
	}
	return -1;
}
