#include <Windows.h>
#include <iostream>

#include "Graph.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Graph graph;

	for (int i = 1; i <= 7; i++)
	{
		graph.addVertex(i);
	}

	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(1, 6);
	graph.addEdge(6, 7);
	graph.addEdge(3, 4);
	graph.addEdge(4, 5);

	graph.printVertexes();
	graph.printEdges();

	return 0;
}