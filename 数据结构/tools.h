#pragma once
#include "graph.h"
#include <fstream>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <iterator>
using std::set;
using std::multimap;
using std::string;
using std::ifstream;

inline void createGraphFromTxt(graph& g, string fileName)
{
	ifstream ifs(fileName.c_str());
	set<char> vers;
	char a[30];
	while (ifs.peek()!='\n')
	{
		ifs.get(a, 2);
		vers.insert(a[0]);
	}
	for (char s : vers)
	{
		cout << s << " ";
		g.insertVer(s);
	}

	multimap<char, char> edges;
	std::pair<char, char> edge;
	while (!ifs.eof())
	{
		while (ifs.peek() == '\n')
		{
			ifs.ignore(1);
		}
		if (ifs.good())
		{
			ifs.get(a, 3,'\n');
			edge.first = a[0];
			edge.second = a[1];
			edges.insert(edge);
		}
	}
	//delete[] a;
	for (std::pair<char, char> s : edges)
	{
		cout << s.first << "-->" << s.second << "  " << endl;
		g.insertEdge(s.first, s.second, 1);
	}
	ifs.close();
}
