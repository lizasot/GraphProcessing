#pragma once
#include "graph.h"

void vectorSizeSort(vector<edge>& graph);

void bubbleSizeSort(vector<edge>& graph);

void insertSizeSort(vector<edge>& graph);

void shakerSizeSort(vector<edge>& graph);

bool compareVert(edge item1, edge item2);

void vectorVertSort(vector<edge>& graph);

void bubbleVertSort(vector<edge>& graph);

void insertVertSort(vector<edge>& graph);

void shakerVertSort(vector<edge>& graph);

void compareSort(vector<edge> graph, size_t N);