#include "edge.h"

void sortVertex(size_t& first, size_t& second)
{
	if (first < second) { return; } //если первая вершина меньше второй - всё ок
	size_t c = first;
	first = second;
	second = c;
}

edge* createEdge(size_t first, size_t second, int size)
{
	if (first == 0 || second == 0 || size == 0)
	{
		return NULL;
	}
	edge* newEdge = new edge;
	newEdge->minVertex = first;
	newEdge->maxVertex = second;
	newEdge->size = size;
	return newEdge;
}