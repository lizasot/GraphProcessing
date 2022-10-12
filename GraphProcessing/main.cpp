#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
#include "graph.h"
#include "sorting_graph.h"

using namespace std;

void endInputEdge(char& sw)
{
	cout << "Введите 'Y', если хотите завершить создание графа\n";
	cin >> sw;
	while (cin.get() != '\n') { sw = ' '; }; //если строка содержит более одного символа, присваивается пробел
}

int main()
{
	setlocale(0, "");
	vector<edge> graph(NULL);
	size_t countVertices = 0;

	bool doesMenuContinue = true;
	bool doesSubMenuContinue = false;
	do {
		//system("cls");
		char switchMenu = ' ';
		char switchSubMenu = ' ';
		cout << "\nВыберите нужный раздел: \n";
		cout << "\x1b[32m[1]\x1b[0m Ввести новый граф\n";
		cout << "\x1b[32m[2]\x1b[0m Сортировка рёбер\n";
		cout << "\x1b[32m[3]\x1b[0m Поиск минимального остовного дерева (Алгоритм Краскала)\n";
		cout << "\x1b[32m[4]\x1b[0m Вывести список рёбер\n";
		cout << "\x1b[32m[5]\x1b[0m Вывести текущий граф\n";
		cout << "\x1b[32m[0]\x1b[0m Закрыть программу\n";
		cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

		cin >> switchMenu;
		while (cin.get() != '\n') { switchMenu = ' '; };

		switch (switchMenu)
		{

		case '1': //[1] Ввести новый граф
			do {
				doesSubMenuContinue = false;
				switchSubMenu = ' ';
				cout << "\n\x1b[32m[1]\x1b[0m Ввести граф самостоятельно\n";
				cout << "\x1b[32m[2]\x1b[0m Ввести количество вершин и соединить их случайно\n";
				cout << "\x1b[32m[3]\x1b[0m Считать граф с файла\n";
				cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
				cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

				cin >> switchSubMenu;
				while (cin.get() != '\n') { switchSubMenu = ' '; };

				switch (switchSubMenu)
				{
				case '1': //[1] Ввести граф самостоятельно
					if (!graph.empty()) { graph.clear(); countVertices = 0; }
					inputUser(graph, countVertices);
					break;
				case '2': //[2] Ввести количество вершин и соединить их случайно
					generateGraphNew(graph, countVertices);
					break;
				case '3': //[3] Считать граф с файла
					if (!graph.empty()) { graph.clear(); countVertices = 0; }
					inputFile(graph, countVertices);
					break;
				case '0': //[0] Назад
					break;
				default:
					cout << "Ошибка! Пожалуйста, попробуйте снова\n";
					doesSubMenuContinue = true;
					break;
				}
			} while (doesSubMenuContinue);
			break;

		case '2': //[2] Сортировка рёбер
			do {
				doesSubMenuContinue = false;
				switchSubMenu = ' ';
				cout << "\n\x1b[32m[1]\x1b[0m Сортировать граф по весу рёбер\n";
				cout << "\x1b[32m[2]\x1b[0m Сортировать граф по вершинам\n";
				cout << "\x1b[32m[3]\x1b[0m Сравнение различных сортировок по скорости\n";
				cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
				cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

				cin >> switchSubMenu;
				while (cin.get() != '\n') { switchSubMenu = ' '; };

				switch (switchSubMenu)
				{
				case '1': //[1] Сортировать рёбра по весу
					if (!graph.empty()) { vectorSizeSort(graph); }
					else { cout << "Ошибка! Создайте граф, прежде чем сортировать его.\n"; }
					break;
				case '2': //[2] Сортировать рёбра по вершинам
					if (!graph.empty()) { vectorVertSort(graph); }
					else { cout << "Ошибка! Создайте граф, прежде чем сортировать его.\n"; }
					break;
				case '3': //[3] Сравнение различных сортировок по скорости
					if (!graph.empty()) { compareSort(graph, countVertices); }
					else { cout << "Ошибка! Создайте граф, прежде чем сортировать его.\n"; }
					break;
				case '0': //[0] Назад
					break;
				default:
					cout << "Ошибка! Пожалуйста, попробуйте снова\n";
					doesSubMenuContinue = true;
					break;
				}
			} while (doesSubMenuContinue);
			break;

		case '3': //[3] Поиск минимального остовного дерева
			do {
				doesSubMenuContinue = false;
				switchSubMenu = ' ';
				cout << "\n\x1b[32m[1]\x1b[0m Найти минимальное остовное дерево и сохранить его\n";
				cout << "\x1b[32m[2]\x1b[0m Определить время нахождения минимального остовного дерева без сохранения\n";
				cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
				cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

				cin >> switchSubMenu;
				while (cin.get() != '\n') { switchSubMenu = ' '; };

				switch (switchSubMenu)
				{
				case '1': //[1] Найти минимальное остовное дерево и сохранить его
					if (!graph.empty())
					{
						searchTree(graph, countVertices);
						cout << "Минимальное остовное дерево: \n";
						cout << getGraphAsString(graph, countVertices);
					}
					else { cout << "Ошибка! Граф пуст.\n"; }
					break;
				case '2': //[2] Определить время нахождения
					if (!graph.empty()) { searchTreeTime(graph, countVertices); }
					else { cout << "Ошибка! Граф пуст.\n"; }
					break;
				case '0': //[0] Назад
					break;
				default:
					cout << "Ошибка! Пожалуйста, попробуйте снова\n";
					doesSubMenuContinue = true;
					break;
				}
			} while (doesSubMenuContinue);
			break;

		case '4': //[4] Вывести список рёбер
			if (!graph.empty()) { cout << getEdgeList(graph); }
			else { cout << "Ошибка! Граф пуст.\n"; }
			break;

		case '5': //[5] Вывод текущего графа
			if (!graph.empty()) { cout << getGraphAsString(graph, countVertices); }
			else { cout << "Ошибка! Граф пуст.\n"; }
			break;

		case '0': //[0] Закрыть программу
			cout << "Выход из программы...\n";
			doesMenuContinue = false;
			break;
		default:
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			break;
		}
	} while (doesMenuContinue);
	return 0;
}