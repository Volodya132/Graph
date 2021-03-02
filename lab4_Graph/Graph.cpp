#include "Graph.h"

#include <iostream>

void Graph::addVertex(int key)
{
	Vertex* v = new Vertex(key);
	vertexes.insert(std::pair<int, Vertex*>(key, v));
}

void Graph::printVertexes()const
{
	for (auto it = vertexes.begin(); it != vertexes.end(); it++)
	{
		std::cout << it->second->key << std::endl;
	}
}

void Graph::addEdge(int v1, int v2)
{
	Vertex* vertex1 = vertexes[v1];
	Vertex* vertex2 = vertexes[v2];

	Edge edge;

	edge.v = vertex2;
	vertex1->edges.emplace_back(edge);

	edge.v = vertex1;
	vertex2->edges.emplace_back(edge);
}

void Graph::printEdges()const
{
	for (auto it = vertexes.begin(); it != vertexes.end(); it++)
	{
		if (!(it->second->edges.empty()))
		{
			std::cout << "�������: " << it->second->key << " �'������ � ���������: " << std::endl;
			for (auto currentEdge : it->second->edges)
			{
				std::cout << (*(currentEdge.v)).key << std::endl;
			}
		}
	}
}

std::list<Vertex*> Graph::dfs(int key)
{
	Vertex* v = vertexes[key];
	if (v)
		return _dfs(v);

	return std::list<Vertex*>();
}

std::list<Vertex*> Graph::_dfs(Vertex* v)
{
	std::list<Vertex* > visitedGroup;
	v->visited = true;

	visitedGroup.push_back(v);

	for (Edge currentEdge : v->edges)
	{
		if (!currentEdge.v->visited)
		{
			for (Vertex* currentVertex : _dfs(currentEdge.v))
				visitedGroup.push_back(currentVertex);
		}
	}

	return visitedGroup;
}