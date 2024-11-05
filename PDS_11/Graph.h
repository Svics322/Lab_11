#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;

struct Edge {
	unsigned int to;
};

struct PathInfo {
	unsigned int distance;
	vector<int> path;
};

class Graph {
public:
	vector<vector<Edge>> adjList;
	vector<vector<unsigned int>> distances;
	vector<vector<int>> next;
	static const unsigned int INF = numeric_limits<unsigned int>::max();

	Graph(unsigned int n) : adjList(n), distances(n, vector<unsigned int>(n, INF)), next(n, vector<int>(n, -1)) {
		for (int i = 0; i < n; i++)
			distances[i][i] = 0;
	}
	
	void addEdge(unsigned int from, unsigned int to, unsigned int weight);
	void floydWarshall();
	PathInfo getPath(int start, int end) const;

	void printAdjVertices() const;
	void printDistances() const;

};