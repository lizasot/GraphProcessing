#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

#include "edge.h"

using namespace std;

string getEdgeList(vector<edge>& graph);

bool compareSize(edge item1, edge item2);

void outputGraph(vector<edge>& graph, size_t N);

bool connectivity(vector<edge>& graph, size_t& N);

bool delEdge(vector<edge>& graph, size_t minVertex, size_t maxVertex);

void endInputEdge(char& sw);

void errorInput(char& sw);

void inputUser(vector<edge>& graph, size_t& N);

size_t countRows();

void inputFile(vector<edge>& graph, size_t& N);

void outputFile(vector<edge>& graph, size_t N);

void generateGraphNew(vector<edge>& graph, size_t& N);

void marksChange(int min, int max, int& m, int*& Arr, size_t& N);

void searchTree(vector<edge>& graph, size_t N);

void searchTreeTime(vector<edge> graph, size_t N);