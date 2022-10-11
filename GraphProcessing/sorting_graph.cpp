#include "sorting_graph.h"

//== СОРТИРОВКИ ==
//== Сортировка графа по весу рёбер ==
//Сортировка вектором
void vectorSizeSort(vector<edge>& graph)
{
	sort(graph.begin(), graph.end(), compareSize);
}

//Пузырьковая сортировка
void bubbleSizeSort(vector<edge>& graph)
{
	vector<edge>::iterator iter = graph.begin(); //итератор, который перебирает весь список
	vector<edge>::iterator jter = graph.begin();
	edge tmp;
	for (iter = graph.begin(); iter < graph.end(); iter++) {
		for (jter = (graph.end() - 1); jter >= (iter + 1); jter--) {
			if (jter->size < (jter - 1)->size) {
				tmp = *jter;
				*jter = *(jter - 1);
				*(jter - 1) = tmp;
			}
		}
	}
}

//Сортировка вставками
void insertSizeSort(vector<edge>& graph)
{
	vector<edge>::iterator iter = graph.begin(); //итератор, который перебирает весь список
	vector<edge>::iterator jter = graph.begin();
	edge key;
	for (jter = (graph.begin() + 1); jter < graph.end(); jter++) {
		key = *jter;
		iter = jter - 1;
		while (iter >= graph.begin() && iter->size > key.size) {
			*(iter + 1) = *iter;
			*(iter) = key;
			if (iter != graph.begin()) { iter--; }
			else { break; }
		}
	}
}

//Быстрая сортировка
void shakerSizeSort(vector<edge>& graph)
{
	vector<edge>::iterator iter = graph.begin(); //итератор, который перебирает весь список
	edge tmp;
	vector<edge>::iterator right = graph.end() - 1;
	vector<edge>::iterator left = graph.begin();
	while (left <= right)
	{
		for (iter = right; iter > left; iter--)
		{
			if ((iter - 1)->size > iter->size)
			{
				tmp = *iter;
				*iter = *(iter - 1);
				*(iter - 1) = tmp;
			}
		}
		left++;
		for (iter = left; iter < right; iter++)
		{
			if (iter->size > (iter + 1)->size)
			{
				tmp = *iter;
				*iter = *(iter + 1);
				*(iter + 1) = tmp;
			}
		}
		right--;
	}
}

//== Сортировка графа по вершинам ==
//Сортировка вектором
bool compareVert(edge item1, edge item2)
{
	size_t vertex1, vertex2;
	vertex1 = item1.minVertex * 10 + item1.maxVertex;
	vertex2 = item2.minVertex * 10 + item2.maxVertex;
	return (vertex1 < vertex2);
}

void vectorVertSort(vector<edge>& graph)
{
	sort(graph.begin(), graph.end(), compareVert);
}

//Пузырьковая сортировка
void bubbleVertSort(vector<edge>& graph)
{
	vector<edge>::iterator iter = graph.begin(); //итератор, который перебирает весь список
	vector<edge>::iterator jter = graph.begin();
	edge tmp;
	for (iter = graph.begin(); iter < graph.end(); iter++) {
		for (jter = (graph.end() - 1); jter >= (iter + 1); jter--) {
			if ((jter->minVertex * 10 + jter->maxVertex) < ((jter - 1)->minVertex * 10 + (jter - 1)->maxVertex)) {
				tmp = *jter;
				*jter = *(jter - 1);
				*(jter - 1) = tmp;
			}
		}
	}
}

//Сортировка вставками
void insertVertSort(vector<edge>& graph)
{
	vector<edge>::iterator iter = graph.begin(); //итератор, который перебирает весь список
	vector<edge>::iterator jter = graph.begin();
	edge key;
	for (jter = (graph.begin() + 1); jter < graph.end(); jter++) {
		key = *jter;
		iter = jter - 1;
		while (iter >= graph.begin() && ((iter->minVertex * 10 + iter->maxVertex) > (key.minVertex * 10 + key.maxVertex))) {
			*(iter + 1) = *iter;
			*(iter) = key;
			if (iter != graph.begin()) { iter--; }
			else { break; }
		}
	}
}

//Быстрая сортировка
void shakerVertSort(vector<edge>& graph)
{
	vector<edge>::iterator iter = graph.begin(); //итератор, который перебирает весь список
	edge tmp;
	vector<edge>::iterator right = graph.end() - 1;
	vector<edge>::iterator left = graph.begin();
	while (left <= right)
	{
		for (iter = right; iter > left; iter--)
		{
			if (((iter - 1)->minVertex * 10 + (iter - 1)->maxVertex) > (iter->minVertex * 10 + iter->maxVertex))
			{
				tmp = *iter;
				*iter = *(iter - 1);
				*(iter - 1) = tmp;
			}
		}
		left++;
		for (iter = left; iter < right; iter++)
		{
			if ((iter->minVertex * 10 + iter->maxVertex) > ((iter + 1)->minVertex * 10 + (iter + 1)->maxVertex))
			{
				tmp = *iter;
				*iter = *(iter + 1);
				*(iter + 1) = tmp;
			}
		}
		right--;
	}
}

void compareSort(vector<edge> graph, size_t N)
{
	int  x;
	cout << "Сколько раз повторять сортировку?\n";
	cin >> x;
	if (!cin || x <= 0)
	{
		cout << "Ошибка! Количество повторений не должно быть меньше 1. Было установлено значение по умолчанию.\n";
		cin.clear();
		cin.sync();
		while (cin.get() != '\n');
		x = 1;
	}

	clock_t start, end;
	cout << "\x1b[36mСортировка графа по весу рёбер\x1b[0m\n";
	start = clock();
	for (int i = 0; i <= x; i++) { vectorSizeSort(graph); }
	end = clock();
	cout << "Сортировка вектором: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";

	start = clock();
	for (int i = 0; i <= x; i++) { bubbleSizeSort(graph); }
	end = clock();
	cout << "Пузырьковая сортировка: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";

	start = clock();
	for (int i = 0; i <= x; i++) { insertSizeSort(graph); }
	end = clock();
	cout << "Сортировка вставками: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";

	start = clock();
	for (int i = 0; i <= x; i++) { shakerSizeSort(graph); }
	end = clock();
	cout << "Шейкер сортировка: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";

	cout << "\x1b[36mСортировка графа по вершинам\x1b[0m\n";
	start = clock();
	for (int i = 0; i <= x; i++) { vectorVertSort(graph); }
	end = clock();
	cout << "Сортировка вектором: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";

	start = clock();
	for (int i = 0; i <= x; i++) { bubbleVertSort(graph); }
	end = clock();
	cout << "Пузырьковая сортировка: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";

	start = clock();
	for (int i = 0; i <= x; i++) { insertVertSort(graph); }
	end = clock();
	cout << "Сортировка вставками: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";

	start = clock();
	for (int i = 0; i <= x; i++) { shakerVertSort(graph); }
	end = clock();
	cout << "Шейкер сортировка: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";
}