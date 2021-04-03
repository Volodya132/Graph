#include "Graph.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

void Graph::addVertex(int key, std::string name)
{
	Vertex* v = new Vertex(key, name);
	vertexes.insert(std::pair<int, Vertex*>(key, v));
}

void Graph::printVertexes()const
{
	for (auto it = vertexes.begin(); it != vertexes.end(); it++)
	{
		std::cout << it->second->key << ". " <<it->second->name << std::endl;
	}
}

void Graph::addEdge(int v1, int v2, size_t weight)
{
	Vertex* vertex1 = vertexes[v1];
	Vertex* vertex2 = vertexes[v2];

	Edge edge;
	edge.weight = weight;

	edge.v = vertex2;
	vertex1->edges.emplace(edge);
	//vertex1->edges.emplace_back(edge);

	edge.v = vertex1;
	vertex2->edges.emplace(edge);
}

void Graph::printEdges()const
{
	for (auto it = vertexes.begin(); it != vertexes.end(); it++)
	{
		if (!(it->second->edges.empty()))
		{
			std::cout << "Місто: " << it->second->key << ". " << it->second->name << " з'єднане з містами: " << std::endl;
			for (auto currentEdge : it->second->edges)
			{
				std::cout << (*(currentEdge.v)).key << ". " << (*(currentEdge.v)).name;
				std::cout << ". Відстань: " << currentEdge.weight << std::endl;
			}
			std::cout << std::endl;
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

int Graph::searchVertexId(Vertex* searchedV)
{
	for (std::pair<int, Vertex*> v : vertexes)
	{
		if (v.second == searchedV)
			return v.first;
	}

	return -1;
}

std::list<Vertex*> Graph::bfs(int key)
{
	std::list<Vertex*> visitedGroup;
	visitedGroup.push_back(vertexes[key]);

	std::list<Vertex*> queue;
	vertexes[key]->visited = true;
	queue.push_back(vertexes[key]);
	
	while (!queue.empty())
	{
		int currvertex = queue.front()->key;
		for (Edge currentEdge : queue.front()->edges)
		{
			if (!currentEdge.v->visited)
			{
				currentEdge.v->visited = true;
				queue.push_back(currentEdge.v);
				visitedGroup.push_back(currentEdge.v);
			}
		}

		queue.pop_front();
	}

	return visitedGroup;
}

bool Graph::vertexIsConnected(int start, int finish)
{
	std::list<Vertex*> visitedGroup;
	visitedGroup.push_back(vertexes[start]);

	std::list<Vertex*> queue;
	vertexes[start]->visited = true;
	vertexes[start]->dist = 0;
	queue.push_back(vertexes[start]);

	while (!queue.empty())
	{
		int currvertex = queue.front()->key;
		for (Edge currentEdge : queue.front()->edges)
		{
			if (!currentEdge.v->visited)
			{
				currentEdge.v->visited = true;
				currentEdge.v->dist = vertexes[currvertex]->dist + 1;
				currentEdge.v->pred = currvertex;
				queue.push_back(currentEdge.v);
				visitedGroup.push_back(currentEdge.v);

				if (currentEdge.v->key == finish)
				{
					return true;
				}
			}
		}

		queue.pop_front();
	}

}

void Graph::printShortestDistance(int start, int finish)
{
	if (vertexIsConnected(start, finish))
	{
		std::cout << "Шлях існує, кількість зупинок: " << vertexes[finish]->dist << std::endl;
		std::vector<std::string> path; 
		int currentKey = vertexes[finish]->key;
		while (currentKey != -1)
		{
			path.push_back(vertexes[currentKey]->name);
			currentKey = vertexes[currentKey]->pred;
		} 
		std::cout << "Шлях: ";
		for (int i = path.size() - 1; i >= 0; i--)
		{
			std::cout << path[i];
			if (i != 0)
			{
				std::cout << " -> ";
			}
		}

	}
	else
	{
		std::cout << "Вершини не зєднані! " << std::endl;
	}
}

std::list<Vertex*> Graph::hamCycle(int& pathDistance)
{
	Vertex* minVertexStart = vertexes.begin()->second;
	Vertex* minVertexFinish= vertexes.begin()->second->edges.begin()->v;
	std::list<Vertex*> path;
	pathDistance = vertexes.begin()->second->edges.begin()->weight;

	for (std::pair<int, Vertex*> v : vertexes)
	{
		if (v.second->edges.begin()->weight < minVertexStart->edges.begin()->weight)
		{
			minVertexStart = v.second;
			minVertexFinish = v.second->edges.begin()->v;
			pathDistance = minVertexStart->edges.begin()->weight;
		}
	}
	path.push_back(minVertexStart);
	path.push_back(minVertexFinish);
	minVertexStart->visited = true;
	minVertexFinish->visited = true;
	int key = searchVertexId(minVertexFinish);
	while (true)
	{
		bool flag = false;
		for (Edge e : vertexes[key]->edges)
		{	
			if (e.v->visited == false)
			{
				path.push_back(e.v);
				key = searchVertexId(e.v);
				flag = true;
				pathDistance += e.weight;
				e.v->visited = true;
				break;
			}
		}
		if (!flag)
		{
			for (Edge e : vertexes[key]->edges)
			{
				if (std::find(path.begin(), path.end(), e.v) == path.begin())
				{
					path.push_back(e.v);
					pathDistance += e.weight;
					break;
				}
			}
			break;
		}
	}

	return path;
}


void Graph::setNotVisited()
{
	for (std::pair<int, Vertex*> currentVertex : vertexes)
	{
		currentVertex.second->visited = false;
	}
}


Graph::~Graph()
{
	for (auto currentVertex : vertexes) {
		delete currentVertex.second;
	}
}