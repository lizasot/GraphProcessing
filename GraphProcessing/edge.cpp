#include "edge.h"

void swapVertex(size_t& frst, size_t& scnd)
{
	if (frst < scnd) { return; } //если первая вершина меньше второй - всё ок
	size_t c = frst;
	frst = scnd;
	scnd = c;
}

edge* createEdge(size_t frst, size_t scnd, int s)
{
	if (frst == 0 || scnd == 0 || s == 0)
	{
		return NULL;
	}
	edge* newEdge = new edge;
	newEdge->first = frst;
	newEdge->second = scnd;
	newEdge->size = s;
	return newEdge;
}