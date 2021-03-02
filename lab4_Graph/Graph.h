#pragma once

#include <map>

#include "Vertex.h"

class Graph
{
public:
	Graph() {};
	~Graph() {};

	void addVertex(int key);
	void printVertexes()const;
	void addEdge(int v1, int v2);
	void printEdges()const;
private:
	std::map<int, Vertex*> vertexes;
};
