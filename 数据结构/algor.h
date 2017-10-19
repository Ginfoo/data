#pragma once
#include "graph.h"
#include "vector.h"
#include <memory>
/*
 * 图的相关算法
 */
void DFS(graph&, int s_pos, bool*&);

inline void DFS(graph& g, const char s)//深度优先搜索主程序
{
	int s_pos = g.getVerPos(s);
	int g_num = g.getNumVers();
	bool* visited = new bool[g_num];
	for (int i = 0; i < g_num; i++)visited[i] = false;
	DFS(g, s_pos, visited);
	delete[] visited;
}

inline void DFS(graph& g, int s_pos, bool*& visited)//子程序
{
	if (s_pos != -1)
	{
		visited[s_pos] = true;
		cout << g.getCharByPos(s_pos) << "  ";

		int next_pos = g.getFirstNeighbor(s_pos);
		while (next_pos != -1)
		{
			if (visited[next_pos] == false)
				DFS(g, next_pos, visited);
			next_pos = g.getNextNeighbor(s_pos, next_pos);
		}
	}
}


//广度优先搜索算法
inline void BFS(graph& g, const char s)
{
	int g_num = g.getNumVers();
	int s_pos = g.getVerPos(s);
	//其实unique_ptr 有delete[]   这里就是为了练习一下写法
	std::unique_ptr<bool[], void(*)(bool*)> visited(new bool[g_num], [](bool* p)
                                                {
	                                                delete[] p;
                                                });
	for (int i = 0; i < g_num; i++)
	{
		visited[i] = false;
	}

	//开始访问
	visited[s_pos] = true;
	cout << g.getCharByPos(s_pos) << " ";

	//借助队列
	int queue[30];
	int front = 0;
	int rear = 0;//初始时front与rear 相等 即为空

	//进队操作 
	queue[rear] = s_pos;
	rear = (rear + 1) % 30;

	while (rear != front)
	{
		//出队操作
		int cur_pos = queue[front];
		front = (front + 1) % 30;
		//
		int w = g.getFirstNeighbor(cur_pos);
		while (w != -1)
		{
			if (visited[w] == false)
			{
				cout << g.getCharByPos(w) << " ";
				visited[w] = true;
				queue[rear] = w;
				rear = (rear + 1) % 30;
			}
			w = g.getNextNeighbor(s_pos, w);
		}
	}
}

//排序算法
//插入类排序
//直接插入
template<class T>
void insertSort(vector<T>& v)
{
	int left = 0;
	int right = v.size() - 1;
	for (int i = left + 1; i <= right; i++)
	{
		if (v[i] < v[i - 1])//如果当前待插入的比前一个小
		{
			int key = v[i];//当前的给key
			int j = i - 1; //前一个下标
			do
			{
				v[j + 1] = v[j];
				j = j - 1;
			}
			while (j >= left && key < v[j]);
			v[j + 1] = key;
		}
	}
}

//折半插入
template<class T>
inline void binaryInsertSort(vector<T>& v)
{
	int left = 0;
	int right = v.size() - 1;
	for (int i = left + 1; i <= right; i++)
	{
		if (v[i] < v[i - 1])
		{
			int key = v[i];
			int low = left;
			int high = i - 1;
			int mid;
			while (low <= high)
			{
				mid = (low + high) / 2;
				if (key < v[mid])high = mid - 1;
				else low = mid + 1;
			}
			for (int k = i; k > low; k--)
			{
				v[k] = v[k - 1];
			}
			v[low] = key;
		}
	}
}

//希尔排序
template<class T>
void shellSort(vector<T>& v)
{
	int left = 0;
	int right = v.size() - 1;
	int gap = right - left + 1;
	do
	{
		gap = gap / 3 + 1;
		for (int i = left + gap; i <= right; i++)
		{
			if (v[i] < v[i - gap])
			{
				int key = v[i];
				int j = i - gap;
				do
				{
					v[j + gap] = v[j];
					j = j - gap;
				}
				while (j >= 0 && key < v[j]);
				v[j + gap] = key;
			}
		}
	}
	while (gap > 1);
}
//选择类排序
