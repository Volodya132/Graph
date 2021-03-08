#pragma once

#include <map>

#include "Vertex.h"

class Graph
{
public:
	Graph() {};
	~Graph();

	void addVertex(int key);
	void printVertexes()const;
	void addEdge(int v1, int v2);
	void printEdges()const;

	std::list<Vertex*> dfs(int key);
	std::list<Vertex*> bfs(int key);

	void setNotVisited();
private:

	std::map<int, Vertex*> vertexes;

	std::list<Vertex*> _dfs(Vertex* v);
};
