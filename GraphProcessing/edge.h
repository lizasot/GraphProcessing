#pragma once
#include <iostream>

struct edge
{
	size_t first; //первая вершина всегда меньше второй и не равна ей
	size_t second;
	int size;
};

void swapVertex(size_t& frst, size_t& scnd);

edge* createEdge(size_t frst, size_t scnd, int s);