#include "edge.h"

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