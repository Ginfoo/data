// 12:53 PM/09/22/2017
//#define VALUE_TYPE char
#include "ds.h"
#include "graph.h"
#include "tools.h"
#include "vector.h"
#include "algor.h"
#include "stack.h"
int main()
{
	graph g(30);
	string filename = "graph.txt";
	createGraphFromTxt(g, filename);
	cout << g << endl;

	DFS(g,'a');
	cout <<endl<< " 广度优先搜索" << endl;
	BFS(g, 'a');
	cout << endl;
	
	stack<int> s(3);
	s.push(3);
	s.push(2);
	s.push(4);
	s.push(6);
	cout << endl << s << endl;
}
