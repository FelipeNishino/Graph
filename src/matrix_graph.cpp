#include <array>
#include <iostream>
#include <ifstream>
#include <vector>
#include <list>
#include <string>

using namespace std;
#include "include/matrix_graph.h"

MatrixGraph::MatrixGraph(int v) {
	n = v;
	m = 0;
	vector<int> inner_list(n);
	for (int i = 0; i < n; i++)
		adj_matrix.push_back(inner_list);
}

MatrixGraph::MatrixGraph(ListGraph g) {
	n = g.n;
	m = g.m;

	vector<int> inner_vector(n);
	int j = 0;
	for (auto const &inner_list : g.adj_list) {
		for (auto const &val : inner_list) {
			inner_vector[val] = 1;

		}
		adj_matrix.push_back(inner_vector);
		inner_vector.assign(n, 0);
		j++;
	}
}

MatrixGraph::MatrixGraph(string filename) {
	ifstream file(filename);
	if (file.fail()) {
		std::cout << "Erro ao abrir arquivo " << filename;
		return;
	}
	string line;

	int step = 0;
	int v1, v2;
	size_t next;
	while(getline(file, line)) {
		switch (step) {
			case 0:
				n = stoi(line);
				break;
			case 1: break;
			default:
				v1 = stoi(line, &next);
				v2 = stoi(line.substr(next));
				insert_edge(v1, v2);
		}
		step++;
	}

	file.close();
}

void MatrixGraph::insert_edge(int v1, int v2) {
	adj_matrix[v1][v2] = 1;
	m++;
}

void MatrixGraph::remove_edge(int v1, int v2) {
	adj_matrix[v1][v2] = 0;
	m--;
}

int MatrixGraph::indegree(int vertex) {
	int degree = 0;
	for (int i = 0; i < n; i++) {
		if (i == vertex) continue;
		if (adj_matrix[i][vertex]) degree++;
	}
	return degree;
}

int MatrixGraph::outdegree(int vertex) {
	int degree = 0;
	for (int i = 0; i < n; i++) {
		if (i == vertex) continue;
		if (adj_matrix[vertex][i]) degree++;
	}
	return degree;
}

bool MatrixGraph::is_equal(MatrixGraph g) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g.adj_matrix[i][j] != adj_matrix[i][j])
				return false;
		}
	}
	return true;
}

bool MatrixGraph::vertex_is_source(int v) {
	return (indegree(v) == 0 && outdegree(v) > 0);
}

bool MatrixGraph::vertex_is_sink(int v) {
	return (indegree(v) > 0  && outdegree(v) == 0);
}

bool MatrixGraph::is_symmetrical() {
	// {(1, 2), (2, 1), (1, 3), (3, 1), (2, 3), (3, 2), }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g.adj_matrix[i][j] != adj_matrix[j][i])
				return false;
		}
	}
	return true;
}

bool MatrixGraph::travel_to(int o, int t) {
	for (int i = 0; i < n; ++i) {
		if (adj_matrix[o][i]) {
			if (i == t) return true;
			if (travel_to(i, t)) return true;
		}
	}
	return false;
}

bool MatrixGraph::has_cicle() {
	for (int i = 0; i < n; ++i) {
		if (MatrixGraph::indegree(i) == 0) continue;
		if (MatrixGraph::travel_to(i, i)) return true;
	}
	return false;
}

void MatrixGraph::display() {
	for(int i = 0; i < this->n; i++) {
		cout << "Vertex " << i << " - ";
		for (auto const &val : adj_matrix[i]) {
			cout << val << ", ";
		}
		cout << endl;
	}
	cout << endl;
}
