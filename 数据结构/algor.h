#pragma once
#include "graph.h"
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
	cout << g.getCharByPos(s_pos)<<" ";

	//��������
	int queue[30];
	int front = 0;
	int rear = 0;//��ʼʱfront��rear ��� ��Ϊ��

	//���Ӳ��� 
	queue[rear] = s_pos;
	rear = (rear + 1) % 30;

	while(rear!=front)
	{
		//���Ӳ���
		int cur_pos = queue[front];
		front = (front + 1) % 30;  
		//
		int w = g.getFirstNeighbor(cur_pos);
		while(w!=-1)
		{
			if(visited[w]==false)
			{
				cout << g.getCharByPos(w)<<" ";
				visited[w] = true;
				queue[rear] = w;
				rear = (rear + 1) % 30;
			}
			w = g.getNextNeighbor(s_pos, w);
		}
	}
}
