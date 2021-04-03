#pragma once

#include <map>
#include <string>

#include "Vertex.h"

class Graph
{
public:
	Graph() {};
	~Graph();

	void addVertex(int key, std::string name = "No label");
	void printVertexes()const;
	void addEdge(int v1, int v2, size_t weight = 1);
	void printEdges()const;

	std::list<Vertex*> dfs(int key);
	std::list<Vertex*> bfs(int key);
	bool vertexIsConnected(int start, int finish);
	void printShortestDistance(int start, int finish);
	std::list<Vertex*> hamCycle(int &pathDistance);

	void setNotVisited();


private:
	std::map<int, Vertex*> vertexes;

	std::list<Vertex*> _dfs(Vertex* v);
	int searchVertexId(Vertex* searchedV);
};
