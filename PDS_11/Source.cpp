#include"Graph.h"
#include<Windows.h>
#include <fstream>


bool readGraphFromFile(const string& filePath, Graph& graph) {
	ifstream file(filePath);
	if (!file.is_open()) {
		cerr << "Не вдалося відкрити файл. Перевірте шлях." << endl;
		return false;
	}

	unsigned int n, m;
	file >> n >> m;

	if (n <= 0 || m <= 0) {
		cerr << "Кількість вершин і ребер повинні бути більше нуля." << endl;
		return false;
	}

	graph = Graph(n);

	for (int i = 0; i < m; i++) {
		unsigned int begin, end, weight;
		if (!(file >> begin >> end >> weight)) {
			cerr << "Помилка при зчитуванні ребра." << endl;
			return false;
		}
		if (begin < 1 || begin > n || end < 1 || end > n) {
			cerr << "Помилка: невірні індекси ребра: "
				<< begin << " -> " << end << endl;
		}
		graph.addEdge(begin, end, weight);
	}
	file.close();
	return true;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string graphReadPath;
	Graph graph(0);

	cout << "Введіть шлях до графу, для визначення найкоротших "
		<< "відстаней між усіма парами вершин в графі за допомогою "
		<< "алгоритму Флойда-Уоршелла:";

	getline(cin, graphReadPath);

	if (readGraphFromFile(graphReadPath, graph))
		graph.printAdjVertices();
	else {
		cerr << "Помилка при зчитуванні файлу." << endl;
		return -1;
	}

	graph.floydWarshall();
	graph.printDistances();

	unsigned int start, end;

	cout << "Введіть початкову вершину: ";
	cin >> start;
	if (cin.fail()) {
		cout << "Початкова вершина неправильно введена." << endl;
		return -2;
	}

	cout << "Введіть кіцеву вершину: ";
	cin >> end;
	if (cin.fail()) {
		cout << "Кінцеву вершину неправильно введено." << endl;
		return -3;
	}

	if (start < 1 || start > graph.adjList.size()
		|| end < 1 || end > graph.adjList.size()
		) {
		cout << "Початкова або кінцева вершина для"
			<< "пошуку виходить за межі дозволених границь графу." << endl;
		return -4;
	}
	PathInfo pathInfo = graph.getPath(start - 1, end - 1);
	if (!pathInfo.path.empty()) {
		cout << "Найкоротший шлях між вершинами "
			<< start << " та " << end << " з довжиною "
			<< pathInfo.distance << " є наступний шлях:" << endl
			<< "[";
		for (size_t i = 0; i < pathInfo.path.size(); i++) {
			cout << pathInfo.path[i];
			if (i < pathInfo.path.size() - 1) {
				cout << " -> ";
			}
		}
		cout << "]" <<  endl;
	}
	else {
		cout << "Немає шляху між вершинами "
			<< start << " та " << end << endl;
	}
	return 0;
}