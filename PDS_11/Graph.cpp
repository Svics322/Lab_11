#include"Graph.h"

void Graph::addEdge(unsigned int from, unsigned int to, unsigned int weight) {
	if (from >= 1 && from <= adjList.size() &&
		to >= 1 && to <= adjList.size()) {
		adjList[from - 1].push_back({ to - 1 });
		if (distances[from - 1][to - 1] > weight) {
			distances[from - 1][to - 1] = weight;
			next[from - 1][to - 1] = to - 1;
		}
		else if (distances[from - 1][to - 1] == weight) {
			next[from - 1][to - 1] = to - 1;
		}
	}
	else {
		cerr << "Помилка: невірні індекси при додаванні ребра: "
			<< from << " -> " << to << endl;
	}
}

void Graph::floydWarshall() {
	int n = distances.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (distances[i][j] != INF && i != j) {
				next[i][j] = j;
			}
		}
	}

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (distances[i][k] < INF && distances[k][j] < INF) {
					if (distances[i][j] > distances[i][k] + distances[k][j]) {
						distances[i][j] = distances[i][k] + distances[k][j];
						next[i][j] = next[i][k];
					}
				}
}

PathInfo Graph::getPath(int start, int end) const {
	PathInfo result;
	result.distance = distances[start][end];

	if (result.distance == INF) {
		result.path = {};
		return result;
	}

	result.path.push_back(start + 1);
	int at = start;

	while (at != end) {
		at = next[at][end];
		if (at == -1) {
			result.path.clear();
			return result;
		}
		result.path.push_back(at + 1);
	}

	return result;
}



void Graph::printAdjVertices() const {
	for (int i = 0; i < adjList.size(); i++) {
		cout << "Вершина " << (i + 1);
		if (!adjList[i].empty()) {
			cout << ": [";
			for (size_t j = 0; j < adjList[i].size(); ++j) {
				cout << (adjList[i][j].to + 1);
				if (j < adjList[i].size() - 1) {
					cout << ", ";
				}
			}
			cout << "]";
		}
		cout << endl;
	}
}

void Graph::printDistances() const {
	cout << endl << "Матриця найкоротших відстаней: " << endl;
	for (int i = 0; i < distances.size(); i++) {
		cout << "Вершина " << (i + 1) << ":";
		for (int j = 0; j < distances[i].size(); j++)
			distances[i][j] == INF ? (cout << setw(10) << "INF " << setw(10)) :
			(cout << setw(10) << distances[i][j] << setw(10));
		cout << endl << setw(0);
	}
}