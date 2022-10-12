#include "graph.h"

string getEdgeList(vector<edge>& graph)
{
	string str = "";
	if (graph.empty()) 
	{ 
		str = "Список рёбер пуст.\n"; 
	}
	else
	{
		vector<edge>::iterator iter = graph.begin();
		size_t i = 0;
		while (iter != graph.end())
		{
			str += to_string(i + 1) + ". Ребро между ";
			str += to_string(iter->minVertex) + " и " + to_string(iter->maxVertex);
			str += " имеет вес " + to_string(iter->size) + ".\n";
			i++;
			++iter;
		}
	}
	return str;
}

string getGraphAsString(vector<edge>& graph, size_t N)
{
	string graphStr = "";
	if (N <= 0) 
	{ 
		graphStr = "Граф пуст.\n";
	}
	else
	{
		if (graph.empty())
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					graphStr += "0 ";
				}
				graphStr += "\n";
			}
		}
		else
		{
			int** Arr = new int* [N];
			for (size_t i = 0; i < N; ++i)
			{
				Arr[i] = new int[N]();
			}

			vector<edge>::iterator currentEdge = graph.begin();
			while (currentEdge != graph.end())
			{
				if (Arr[currentEdge->minVertex - 1][currentEdge->maxVertex - 1] != 0)
				{
					string errorMsg = "Встречены повторяющиеся рёбра между вершинами ";
					errorMsg += to_string(currentEdge->minVertex) + " и " + to_string(currentEdge->maxVertex) + ".";
					for (size_t i = 0; i < N; ++i)
					{
						delete[] Arr[i];
					}
					delete[] Arr;
					throw errorMsg;
				}
				else
				{
					Arr[currentEdge->minVertex - 1][currentEdge->maxVertex - 1] = currentEdge->size;
					Arr[currentEdge->maxVertex - 1][currentEdge->minVertex - 1] = currentEdge->size;
				}
				++currentEdge;
			}

			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					graphStr += to_string(Arr[i][j]) + " ";
				}
				graphStr += "\n";
			}
			for (size_t i = 0; i < N; ++i)
			{
				delete[] Arr[i];
			}
			delete[] Arr;
		}
	}
	return graphStr;
}

bool connectivity(vector<edge>& graph, size_t& N)
{
	bool connectivity = false;
	if (N == 2 && !(graph.empty()))
	{ 
		connectivity = true; //если имеется всего две вершины и одно ребро между ними
	}
	else if (N >= 3 && !(graph.empty()))
	{
		bool hasOne = true; //есть ли в массиве элемент с пометкой "1"
		int* Arr = new int[N]();
		size_t currentVertex = 0;
		vector<edge>::iterator currentEdge = graph.begin();
		Arr[0] = 1;
		while (hasOne)
		{
			Arr[currentVertex] = 2;
			currentEdge = graph.begin();
			do
			{
				//если текущая вершина меньше соединяемой
				if ((currentEdge->minVertex - 1 == currentVertex) && (Arr[currentEdge->maxVertex - 1] == 0)) //если найдена нужная вершина
				{ //проверяем, с кем она связана и помечаем вторую, если она ещё не помечена
					Arr[currentEdge->maxVertex - 1] = 1;
				}

				//если текущая вершина больше соединяемой
				if ((currentEdge->maxVertex - 1 == currentVertex) && (Arr[currentEdge->minVertex - 1] == 0)) //если найдена нужная вершина
				{ //проверяем, с кем она связана и помечаем вторую, если она ещё не помечена
					Arr[currentEdge->minVertex - 1] = 1;
				}

				++currentEdge;
			} while (currentEdge != graph.end()); //пока не просмотрены все рёбра

			hasOne = false;
			for (size_t i = 0; i < N; i++)
			{
				if (Arr[i] == 1)
				{
					currentVertex = i;
					hasOne = true;
					break;
				}
			}
		}

		//если остались вершин, помеченные "0", то граф несвязный
		for (size_t i = 0; i < N; i++)
		{
			if (Arr[i] == 0) { connectivity = false; }
		}
		delete[] Arr;
	}
	return connectivity;
}

bool deleteEdge(vector<edge>& graph, size_t minVertex, size_t maxVertex)
{
	bool sucess = false;
	if (!graph.empty()) 
	{
		vector<edge>::iterator iter = graph.end();
		while (iter != graph.begin())
		{
			iter--;
			if (iter->minVertex == minVertex && iter->maxVertex == maxVertex)
			{
				graph.erase(iter);
				sucess = true;
			}
		}
	}
	return sucess;
}

void errorInput(char& sw)
{
	cin.clear();
	cin.sync();
	while (cin.get() != '\n');
	endInputEdge(sw);
}

void inputUser(vector<edge>& graph, size_t& N)
{
	edge* newEdge = NULL; //создаваемое ребро
	size_t minVertex = 0, maxVertex = 0; //вершины
	int x; //вес ребра
	string input; //ввод пользователем
	char sw = '\0';
	cout << "Введите количество вершин: ";
	while (!(cin >> x) || (x <= 0)) //проверка на корректность ввода
	{
		cout << "Ошибка! Количество вершин должно быть числом больше нуля.\n";
		cin.clear();
		cin.sync();
		while (cin.get() != '\n');
		cout << "Введите количество вершин: ";
	}
	cin.ignore(32767, '\n'); //игнор лишних символов после числа, если они есть
	N = x;

	getGraphAsString(graph, N); //вывод пустого графа

	while (sw != 'Y') {
		cout << "Введите две вершины, которые ребро соединяет (например, 1 2): ";
		cin >> x;
		if (!cin || x <= 0) //корректность ввода
		{
			cout << "Ошибка! Вершина должна быть числом больше нуля.\n";
			errorInput(sw);
			if (sw == 'Y') { break; }
			else { continue; }
		}
		else { minVertex = x; }

		cin >> x;
		if (!cin || x <= 0) //корректность ввода
		{
			cout << "Ошибка! Вершина должна быть числом больше нуля.\n";
			errorInput(sw);
			if (sw == 'Y') { break; }
			else { continue; }
		}
		else { maxVertex = x; }
		cin.ignore(32767, '\n'); //игнор лишних символов после числа, если они есть

		if (minVertex <= N && maxVertex <= N && minVertex != maxVertex)
		{
			cout << "Введите вес ребра: ";
			cin >> x;
			if (!cin) //корректность ввода
			{
				cout << "Ошибка! Вводимое значение должно являться числом.\n";
				errorInput(sw);
				if (sw == 'Y') { break; }
				else { continue; }
			}
			if (x != 0)
			{
				swapVertex(minVertex, maxVertex); //проверяем, чтобы первая вершина была меньше второе
				newEdge = createEdge(minVertex, maxVertex, x); //присваиваем указателю новое ребро
				if (newEdge != NULL) { graph.push_back(*newEdge); } //сохраняем его
			}
			else
			{
				if (deleteEdge(graph, minVertex, maxVertex))
				{
					cout << "Ребро было удалено.\n";
				}
				else
				{
					cout << "Ребро не сохранено, так как имеет нулевой вес.\n";
				}
			}
		}
		else //корректность ввода
		{
			cout << "Ошибка! Значение вершины должно являться числом больше нуля, а также не равняться друг другу.\n";
			endInputEdge(sw);
			if (sw == 'Y') { break; }
			else { continue; }
		}
		getGraphAsString(graph, N);
		endInputEdge(sw);
	}

	//проверка на связность
	if (!graph.empty() && connectivity(graph, N)) //если граф получился связным
	{
		cout << "Граф был успешно создан\n";
	}
	else
	{
		cout << "Граф не прошёл проверку на связность, поэтому был удалён\n";
		if (!graph.empty()) { graph.clear(); N = 0; }
	}
}

size_t countRows()
{
	ifstream fin("graph.txt");
	if (fin.is_open())
	{
		size_t temp = 0; //количество строк
		string data;
		while (!fin.eof()) //пока указатель потока не достигнет конца файла
		{
			getline(fin, data); //считывается строка
			if (data != "\0") { temp++; } //в счётчик не попадают пустые строки
		}
		fin.close();
		return temp;
	}
	else return 0;
}

void inputFile(vector<edge>& graph, size_t& N)
{
	ifstream fin("graph.txt");
	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не был открыт.\n"; // сообщить об этом
	else
	{
		N = countRows();
		cout << "Предполагаемое количество вершин: " << N << "\n";
		if (N == 0) { cout << "Файл пуст.\n"; }
		else
		{
			edge* newEdge = NULL; //создаваемое ребро
			//string data; // буфер промежуточного хранения считываемого из файла текста
			int** gr = new int* [N];
			for (size_t i = 0; i < N; ++i) { gr[i] = new int[N](); } //создаём двумерный массив

			for (size_t i = 0; i < N; i++)
			{
				//getline(fin, data); // Считываем очередную строчку
				for (size_t j = 0; j < N; j++)
				{
					fin >> gr[i][j];
					if (!fin) //корректность ввода
					{
						cout << "\nОшибка! Файл содержит некорректные значения.\n";
						return;
					}
				}
				if (gr[i][i] != 0) { cout << "Ошибка! Главная диагональ матрицы должна содержать только нулевые значения.\n"; return; }
			}

			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 1 + i; j < N; j++)
				{
					if (gr[i][j] != gr[j][i]) { cout << "\nОшибка! Вес одного ребра имеет разные значения.\n"; return; }
					else
					{
						if (gr[i][j] != 0)
						{
							newEdge = createEdge(i + 1, j + 1, gr[i][j]); //присваиваем указателю новое ребро
							if (newEdge != NULL) { graph.push_back(*newEdge); } //сохраняем его
						}
					}
				}
			}
			if (!graph.empty() && connectivity(graph, N)) //если граф получился связным
			{
				cout << "Граф был успешно создан\n";
			}
			else
			{
				cout << "Граф не прошёл проверку на связность, поэтому был удалён\n";
				if (!graph.empty()) { graph.clear(); N = 0; }
			}

			bool chk = false;
			do
			{
				chk = true;
				char sw = '\0';
				cout << "\x1b[32m[1]\x1b[0m Вывести получившийся граф на экран\n";
				cout << "\x1b[32m[0]\x1b[0m Выйти\n";
				cin >> sw;
				while (cin.get() != '\n') { sw = ' '; }; //если строка содержит более одного символа, возвращается ошибка

				switch (sw)
				{
				case '0':
					chk = false;
					break;
				case '1':
					getGraphAsString(graph, N);
					break;
				default:
					cout << "Вы ввели некорректное значение. Повторите снова\n";
					break;
				}
			} while (chk);

			for (size_t i = 0; i < N; ++i) { delete[] gr[i]; }
			delete[] gr; //удаляем двумерный массив
		}
		fin.close();
	}
}

void outputFile(vector<edge>& graph, size_t N)
{
	if (graph.empty())
	{
		cout << "Ошибка! Граф пуст\n";
		return;
	}

	ofstream fout("graph.txt");
	if (!fout.is_open()) { cout << "\nОшибка сохранения!\n"; }
	else
	{
		int** Arr = new int* [N];
		for (size_t i = 0; i < N; ++i)
		{
			Arr[i] = new int[N]();
		} //создаём двумерный массив

		//задаём значения для вывода матрицы
		vector<edge>::iterator iter = graph.begin(); //итератор, который перебирает весь список
		do
		{
			Arr[iter->minVertex - 1][iter->maxVertex - 1] = iter->size;
			Arr[iter->maxVertex - 1][iter->minVertex - 1] = iter->size;
			++iter;
		} while (iter != graph.end());

		//вывод
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				fout << Arr[i][j] << " ";
			}
			fout << "\n";
		}

		for (size_t i = 0; i < N; ++i)
		{
			delete[] Arr[i];
		}
		delete[] Arr; //удаляем двумерный массив
		fout.close();
	}
}

void generateGraphNew(vector<edge>& graph, size_t& N)
{
	int x;
	cout << "Введите количество вершин, которое должно быть в сгенерированном графе: ";
	while (!(cin >> x) || (x <= 0)) //проверка на корректность ввода
	{
		cout << "Ошибка! Количество вершин должно быть числом больше нуля.\n";
		cin.clear();
		cin.sync();
		while (cin.get() != '\n');
		cout << "Введите количество вершин: ";
	}
	N = x;
	cout << "Приступаем к генерации графа...\n";

	edge* newEdge = NULL; //создаваемое ребро
	if (!graph.empty()) { graph.clear(); } //очищаем предварительно граф
	for (size_t i = 0; i < N; i++)
	{
		if (i != N - 1)
		{
			newEdge = createEdge(i + 1, i + 2, rand() % 88 + 11); //!! МЕНЯЕМОЕ ЗНАЧЕНИЕ. Влияет на диапазон веса рёбер
			if (newEdge != NULL) { graph.push_back(*newEdge); } //сохраняем его
		}
		size_t max = i + 2000;
		if (max > N) { max = N; }
		for (size_t j = i + 2; j < max; j++) //вторая вершина не должна быть меньше или равно текущей
		{
			if (!(rand() % 3))
			{
				newEdge = createEdge(i + 1, j + 1, rand() % 88 + 11); //!! МЕНЯЕМОЕ ЗНАЧЕНИЕ. Влияет на диапазон веса рёбер
				if (newEdge != NULL) { graph.push_back(*newEdge); } //сохраняем его
			}
		}
		if ((N > 1000) && i % 1000 == 0)
		{
			cout << i / 1000 << " тыс. вершина были сгенерированы\n";
		}
	}

	bool chk = false;
	do
	{
		chk = true;
		char sw = '\0';
		cout << "\x1b[32m[1]\x1b[0m Вывести получившийся граф на экран\n";
		cout << "\x1b[32m[2]\x1b[0m Вывести получившийся граф в файл\n";
		cout << "\x1b[32m[0]\x1b[0m Выйти\n";
		cin >> sw;
		while (cin.get() != '\n') { sw = ' '; }; //если строка содержит более одного символа, возвращается ошибка

		switch (sw)
		{
		case '0':
			chk = false;
			break;
		case '1':
			getGraphAsString(graph, N);
			break;
		case '2':
			outputFile(graph, N);
			break;
		default:
			cout << "Вы ввели некорректное значение. Повторите снова\n";
			break;
		}
	} while (chk);
}

void marksChange(int min, int max, int& m, int*& Arr, size_t& N)
{
	m = 0; //находим новый максимум
	for (size_t i = 0; i < N; i++) //просматриваем все существующие метки
	{
		if (max == Arr[i]) //метки, равные большей
		{
			Arr[i] = min; //заменяем на метки, равные меньшей
		}
		if (Arr[i] > m)
		{
			m = Arr[i]; //запоминаем новый максимум
		}
	}
}

bool compareSize(edge item1, edge item2)
{
	return (item1.size < item2.size);
}

void searchTree(vector<edge>& graph, size_t N)
{
	vector<edge> tree(NULL); //список рёбер итогового дерева
	if (N <= 1 || graph.empty()) { return; }
	if (N == 2 && !(graph.empty())) { tree = graph; return; } //если имеется всего две вершины и одно ребро между ними

	//далее идёт алгоритм, если есть хотя бы 3 вершины
	sort(graph.begin(), graph.end(), compareSize); //сортировка рёбер по весу
	int* Arr = new int[N](); //по умолчанию все вершины имеют пометку "0"
	int m = 0; //самая большая существующая пометка
	for (vector<edge>::iterator iter = graph.begin(); iter < graph.end(); iter++) //проходим каждое ребро
	{
		if ((Arr[iter->minVertex - 1] == 0) && (Arr[iter->maxVertex - 1] == 0)) //если вершины не помечены
		{
			tree.push_back(*iter); //запоминаем ребро в дереве
			m++; //присваиваем метку, больше существующих
			Arr[iter->minVertex - 1] = m; //помечаем, что вершина в дереве
			Arr[iter->maxVertex - 1] = m;
		}
		else
		{
			if (Arr[iter->minVertex - 1] != Arr[iter->maxVertex - 1]) //если вершины не принадлежат одной группе рёбер
			{
				tree.push_back(*iter); //запоминаем ребро в дереве
				if ((Arr[iter->minVertex - 1] == 0) || (Arr[iter->maxVertex - 1] == 0)) //если одна из вершин не помечена
				{
					if (Arr[iter->minVertex - 1] == 0) //выясняем, какая из вершин равна нулю
					{
						Arr[iter->minVertex - 1] = Arr[iter->maxVertex - 1]; //присваивается метка другого ребра
					}
					else
					{
						Arr[iter->maxVertex - 1] = Arr[iter->minVertex - 1]; //присваивается метка другого ребра
					}
				}
				else
				{
					if (Arr[iter->minVertex - 1] < Arr[iter->maxVertex - 1]) //выясняем наименьшую метку
					{
						marksChange(Arr[iter->minVertex - 1], Arr[iter->maxVertex - 1], m, Arr, N); //присваивается наименьшая метка
					}
					else
					{
						marksChange(Arr[iter->maxVertex - 1], Arr[iter->minVertex - 1], m, Arr, N); //присваивается наименьшая метка
					}
				}
			}
		}
	}
	delete[] Arr;
	graph = tree;
	return;
}

void searchTreeTime(vector<edge> graph, size_t N)
{
	int  x;
	cout << "Сколько раз повторять поиск?\n";
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
	start = clock();
	for (int i = 0; i <= x; i++) { searchTree(graph, N); }
	end = clock();

	cout << "Минимальное остовное дерево: \n";
	getGraphAsString(graph, N);
	cout << "Найдено за: " << ((double)end - start) / ((double)CLOCKS_PER_SEC) << "\n";
	return;
}