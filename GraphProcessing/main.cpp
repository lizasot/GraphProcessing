#include <time.h>

#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
#include "graph.h"
#include "sorting_graph.h"

using namespace std;

int main()
{
	setlocale(0, "");
	vector<edge> graph(NULL); //список рёбер графа
	size_t N = 0; //количество вершин графа

	bool doesMenuContinue = true; //выход из меню
	bool doesSubMenuContinue = false; //выход из подменю
	do {
		//system("cls");
		char sw = ' '; //переключатель главного меню
		char sw1 = ' '; //переключатель саб-меню
		cout << "\nВыберите нужный раздел: \n";
		cout << "\x1b[32m[1]\x1b[0m Ввести новый граф\n";
		cout << "\x1b[32m[2]\x1b[0m Сортировка рёбер\n";
		cout << "\x1b[32m[3]\x1b[0m Поиск минимального остовного дерева (Алгоритм Краскала)\n";
		cout << "\x1b[32m[4]\x1b[0m Вывести список рёбер\n";
		cout << "\x1b[32m[5]\x1b[0m Вывести текущий граф\n";
		cout << "\x1b[32m[0]\x1b[0m Закрыть программу\n";
		cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

		cin >> sw;
		while (cin.get() != '\n') { sw = ' '; }; //если строка содержит более одного символа, возвращается ошибка

		switch (sw)
		{

		case '1': //[1] Ввести новый граф
			do {
				doesSubMenuContinue = false;
				sw1 = ' ';
				cout << "\n\x1b[32m[1]\x1b[0m Ввести граф самостоятельно\n";
				cout << "\x1b[32m[2]\x1b[0m Ввести количество вершин и соединить их случайно\n";
				cout << "\x1b[32m[3]\x1b[0m Считать граф с файла\n";
				cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
				cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

				cin >> sw1;
				while (cin.get() != '\n') { sw1 = ' '; };

				switch (sw1)
				{
				case '1': //[1] Ввести граф самостоятельно
					if (!graph.empty()) { graph.clear(); N = 0; }
					inputUser(graph, N);
					break;
				case '2': //[2] Ввести количество вершин и соединить их случайно
					generateGraphNew(graph, N);
					break;
				case '3': //[3] Считать граф с файла
					if (!graph.empty()) { graph.clear(); N = 0; }
					inputFile(graph, N);
					break;
				case '0': //[0] Назад
					break;
				default:
					cout << "Ошибка! Пожалуйста, попробуйте снова\n";
					doesSubMenuContinue = true; //цикл пойдёт заново
					break;
				}
			} while (doesSubMenuContinue);
			break;

		case '2': //[2] Сортировка рёбер
			do {
				doesSubMenuContinue = false;
				sw1 = ' ';
				cout << "\n\x1b[32m[1]\x1b[0m Сортировать граф по весу рёбер\n";
				cout << "\x1b[32m[2]\x1b[0m Сортировать граф по вершинам\n";
				cout << "\x1b[32m[3]\x1b[0m Сравнение различных сортировок по скорости\n";
				cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
				cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

				cin >> sw1;
				while (cin.get() != '\n') { sw1 = ' '; };

				switch (sw1)
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
					if (!graph.empty()) { compareSort(graph, N); }
					else { cout << "Ошибка! Создайте граф, прежде чем сортировать его.\n"; }
					break;
				case '0': //[0] Назад
					break;
				default:
					cout << "Ошибка! Пожалуйста, попробуйте снова\n";
					doesSubMenuContinue = true; //цикл пойдёт заново
					break;
				}
			} while (doesSubMenuContinue);
			break;

		case '3': //[3] Поиск минимального остовного дерева
			do {
				doesSubMenuContinue = false;
				sw1 = ' ';
				cout << "\n\x1b[32m[1]\x1b[0m Найти минимальное остовное дерево и сохранить его\n";
				cout << "\x1b[32m[2]\x1b[0m Определить время нахождения минимального остовного дерева без сохранения\n";
				cout << "\x1b[32m[0]\x1b[0m Вернуться назад\n";
				cout << "Пожалуйста, введите число, чтобы выполнить нужное действие: ";

				cin >> sw1;
				while (cin.get() != '\n') { sw1 = ' '; };

				switch (sw1)
				{
				case '1': //[1] Найти минимальное остовное дерево и сохранить его
					if (!graph.empty())
					{
						searchTree(graph, N);
						cout << "Минимальное остовное дерево: \n";
						outputGraph(graph, N);
					}
					else { cout << "Ошибка! Граф пуст.\n"; }
					break;
				case '2': //[2] Определить время нахождения
					if (!graph.empty()) { searchTreeTime(graph, N); }
					else { cout << "Ошибка! Граф пуст.\n"; }
					break;
				case '0': //[0] Назад
					break;
				default:
					cout << "Ошибка! Пожалуйста, попробуйте снова\n";
					doesSubMenuContinue = true; //цикл пойдёт заново
					break;
				}
			} while (doesSubMenuContinue);
			break;

		case '4': //[4] Вывести список рёбер
			if (!graph.empty()) { outputEdgeList(graph); }
			else { cout << "Ошибка! Граф пуст.\n"; }
			break;

		case '5': //[5] Вывод текущего графа
			if (!graph.empty()) { outputGraph(graph, N); }
			else { cout << "Ошибка! Граф пуст.\n"; }
			break;

		case '0': //[0] Закрыть программу
			cout << "Выход из программы...\n";
			doesMenuContinue = false; //выход из цикла
			break;
		default: //в случае, если введено что-то иное
			cout << "Ошибка! Пожалуйста, попробуйте снова\n";
			break;
		}

	} while (doesMenuContinue);

	return 0;

}