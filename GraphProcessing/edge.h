#pragma once
#include <iostream>

struct edge
{
	size_t minVertex;
	size_t maxVertex;
	int size;
};

void swapVertex(size_t& first, size_t& second);

edge* createEdge(size_t first, size_t second, int size);