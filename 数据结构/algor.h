#pragma once
#include "graph.h"
/*
 * 图的相关算法
 */
void DFS(graph&, int s_pos, bool*&);
inline void DFS(graph&g,char s)//深度优先搜索主程序
{
	int s_pos = g.getVerPos(s);
	int g_num = g.getNumVers();
	bool* visited = new bool[g_num];
	for (int i = 0; i < g_num; i++)visited[i] = false;
	DFS(g, s_pos, visited);
	delete[] visited;
}
inline void DFS(graph&g,int s_pos,bool*&visited)//子程序
{
	if(s_pos!=-1)
	{
		visited[s_pos] = true;
		cout << g.getCharByPos(s_pos) << "  ";
		
		int next_pos = g.getFirstNeighbor(s_pos);
		while(next_pos!=-1)
		{
			if (visited[next_pos] == false)
			DFS(g, next_pos, visited);
			next_pos = g.getNextNeighbor(s_pos, next_pos);
		}
	}
}
