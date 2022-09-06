#include <array>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
#include "include/graph.h"

ListGraph::ListGraph(int v) {
	n = v;
	m = 0;
	list<int> inner_list(n);
	for (int i = 0; i < n; i++)
		adj_list.push_back(inner_list);
};

ListGraph::ListGraph(MatrixGraph g) {
	n = g.n;
	m = g.m;
	list<int> inner_list;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; ++j) {
			if (g.adj_matrix[i][j]) {
				inner_list.push_back(j);
				m++;
			}
		}
		adj_list.push_back(inner_list);
		inner_list.clear();
	}
};


void ListGraph::insert_edge(int v1, int v2) {
	int j = 1;
	bool control = false;
	if (v1 > n || v2 > n)
		return;
	for (auto &inner_list : adj_list) {
		if (j == v1) {
			for (auto const &val : inner_list) {
  				// control &= val == v2;
				if (val == v2)
					return;
			}
			inner_list.push_back(v2);
			m++;
			return;
		}
		j++;
	}
}

void ListGraph::remove_edge(int v1, int v2) {
	int j = 1;
	if (v1 > n || v2 > n)
		return;
	for (auto &inner_list : adj_list) {
		if (j == v1) {
			int prev_size = inner_list.size();
			inner_list.remove_if([v2](int n) { return n == v2; });

			if (prev_size != inner_list.size()) {
				m--;
				return;
			}
		}
		j++;
	}
}

void ListGraph::display() {
	int j = 0;
	for (auto const &inner_list : adj_list) {
		cout << "Vertex " << j << " - ";
		for (auto const &val : inner_list) {
			cout << val << ", ";
		}
		cout << endl;
		j++;
	}
	cout << "edges: " << m << endl << endl;
}
void ListGraph::reverse() {
}

bool ListGraph::is_equal(ListGraph g) {
	return true;
}

MatrixGraph::MatrixGraph(int v) {
	n = v;
	m = 0;
	vector<int> inner_list(n);
	for (int i = 0; i < n; i++)
		adj_matrix.push_back(inner_list);
};

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
};

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
	return true;
}

bool MatrixGraph::has_cicle() {
	for (int i = 0; i < n; ++i) {
		if (MatrixGraph::indegree(i) == 0) continue;
		if (MatrixGraph::travel_to(i, i)) return true;
	}
	return false;
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
