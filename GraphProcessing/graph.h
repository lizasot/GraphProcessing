#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "edge.h"

using namespace std;

string getEdgeList(vector<edge>& graph);

string getGraphAsString(vector<edge>& graph, size_t N);

bool connectivity(vector<edge>& graph, size_t& N);

bool deleteEdge(vector<edge>& graph, size_t minVertex, size_t maxVertex);

void endInputEdge(char& sw);

void errorInput(char& sw);

void inputGraphByUser(vector<edge>& graph, size_t& N);

size_t countRows();

void inputGraphByFile(vector<edge>& graph, size_t& N);

void outputFile(vector<edge>& graph, size_t N);

void generateGraphNew(vector<edge>& graph, size_t& N);

void marksChange(int min, int max, int& m, int*& Arr, size_t& N);

bool compareSize(edge item1, edge item2);

void searchTree(vector<edge>& graph, size_t N);

void searchTreeTime(vector<edge> graph, size_t N);