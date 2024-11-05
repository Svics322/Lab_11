#include"Graph.h"
#include<Windows.h>
#include <fstream>


bool readGraphFromFile(const string& filePath, Graph& graph) {
	ifstream file(filePath);
	if (!file.is_open()) {
		cerr << "�� ������� ������� ����. �������� ����." << endl;
		return false;
	}

	unsigned int n, m;
	file >> n >> m;

	if (n <= 0 || m <= 0) {
		cerr << "ʳ������ ������ � ����� ������ ���� ����� ����." << endl;
		return false;
	}

	graph = Graph(n);

	for (int i = 0; i < m; i++) {
		unsigned int begin, end, weight;
		if (!(file >> begin >> end >> weight)) {
			cerr << "������� ��� ��������� �����." << endl;
			return false;
		}
		if (begin < 1 || begin > n || end < 1 || end > n) {
			cerr << "�������: ����� ������� �����: "
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

	cout << "������ ���� �� �����, ��� ���������� ����������� "
		<< "�������� �� ���� ������ ������ � ����� �� ��������� "
		<< "��������� ������-��������:";

	getline(cin, graphReadPath);

	if (readGraphFromFile(graphReadPath, graph))
		graph.printAdjVertices();
	else {
		cerr << "������� ��� ��������� �����." << endl;
		return -1;
	}

	graph.floydWarshall();
	graph.printDistances();

	unsigned int start, end;

	cout << "������ ��������� �������: ";
	cin >> start;
	if (cin.fail()) {
		cout << "��������� ������� ����������� �������." << endl;
		return -2;
	}

	cout << "������ ����� �������: ";
	cin >> end;
	if (cin.fail()) {
		cout << "ʳ����� ������� ����������� �������." << endl;
		return -3;
	}

	if (start < 1 || start > graph.adjList.size()
		|| end < 1 || end > graph.adjList.size()
		) {
		cout << "��������� ��� ������ ������� ���"
			<< "������ �������� �� ��� ���������� ������� �����." << endl;
		return -4;
	}
	PathInfo pathInfo = graph.getPath(start - 1, end - 1);
	if (!pathInfo.path.empty()) {
		cout << "����������� ���� �� ��������� "
			<< start << " �� " << end << " � �������� "
			<< pathInfo.distance << " � ��������� ����:" << endl
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
		cout << "���� ����� �� ��������� "
			<< start << " �� " << end << endl;
	}
	return 0;
}