#pragma once

#include <list>
#include <map>
#include <string>
#include <set>
#include <iterator> 

struct Vertex;

struct Edge
{
	Vertex* v{};
	size_t weight = 1;
	friend bool operator< (const Edge& e1, const Edge& e2)
	{
		return e1.weight < e2.weight;
	}
};

struct Vertex {
	int key;
	std::string name;
	bool visited;
	int dist;
	int pred;

	Vertex(int key, std::string name = "No label") : key(key), name(name), visited(false), dist(INT_MAX), pred(-1)
	{ 
	}

	std::set<Edge> edges;


};
