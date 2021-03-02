#pragma once

#include <list>

struct Vertex;

struct Edge
{
	Vertex* v{};
};

struct Vertex {
	int key;
	bool visited{};

	Vertex(int key) : key(key)
	{ }
	
	std::list<Edge> edges;
};
