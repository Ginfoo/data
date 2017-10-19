#pragma once
#include "graph.h"
#include "vector.h"
#include <memory>
/*
 * ͼ������㷨
 */
void DFS(graph&, int s_pos, bool*&);

inline void DFS(graph& g, const char s)//�����������������
{
	int s_pos = g.getVerPos(s);
	int g_num = g.getNumVers();
	bool* visited = new bool[g_num];
	for (int i = 0; i < g_num; i++)visited[i] = false;
	DFS(g, s_pos, visited);
	delete[] visited;
}

inline void DFS(graph& g, int s_pos, bool*& visited)//�ӳ���
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


//������������㷨
inline void BFS(graph& g, const char s)
{
	int g_num = g.getNumVers();
	int s_pos = g.getVerPos(s);
	//��ʵunique_ptr ��delete[]   �������Ϊ����ϰһ��д��
	std::unique_ptr<bool[], void(*)(bool*)> visited(new bool[g_num], [](bool* p)
                                                {
	                                                delete[] p;
                                                });
	for (int i = 0; i < g_num; i++)
	{
		visited[i] = false;
	}

	//��ʼ����
	visited[s_pos] = true;
	cout << g.getCharByPos(s_pos) << " ";

	//��������
	int queue[30];
	int front = 0;
	int rear = 0;//��ʼʱfront��rear ��� ��Ϊ��

	//���Ӳ��� 
	queue[rear] = s_pos;
	rear = (rear + 1) % 30;

	while (rear != front)
	{
		//���Ӳ���
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

//�����㷨
//����������
//ֱ�Ӳ���
template<class T>
void insertSort(vector<T>& v)
{
	int left = 0;
	int right = v.size() - 1;
	for (int i = left + 1; i <= right; i++)
	{
		if (v[i] < v[i - 1])//�����ǰ������ı�ǰһ��С
		{
			int key = v[i];//��ǰ�ĸ�key
			int j = i - 1; //ǰһ���±�
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

//�۰����
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

//ϣ������
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
//ѡ��������
