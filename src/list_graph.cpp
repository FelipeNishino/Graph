#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;
#include "include/matrix_graph.h"
#include "include/list_graph.h"

ListGraph::ListGraph(int v) {
	n = v;
	m = 0;
	list<int> inner_list(n);
	for (int i = 0; i < n; i++)
		adj_list.push_back(inner_list);
}

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
}

ListGraph::ListGraph(string filename) {
	std::ifstream file;
	file.open(filename);
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

int ListGraph::indegree(int vertex) {
	int degree = 0;
	for (auto const &inner_list : adj_list) {
		for (auto const &val : inner_list) {
			if (val == vertex)
				degree++;
		}
	}
	return degree;
}

int ListGraph::outdegree(int vertex) {
	int j = 0;
	for (auto const &inner_list : adj_list) {
		if (j == vertex) 
			return inner_list.size();
		j++;
	}
	return 0;
}

bool ListGraph::is_equal(ListGraph g) {
	int j = 0;
	for (auto const &inner_list : adj_list) {
		for (auto const &val : inner_list) {
			if (!g.vertex_is_connected_to(j, val)) return false;
		}
		j++;
	}
	return true;
}

bool ListGraph::vertex_is_source(int v) {
	return (indegree(v) == 0 && outdegree(v) > 0);
}

bool ListGraph::vertex_is_sink(int v) {
	return (indegree(v) > 0 && outdegree(v) == 0);
}

bool ListGraph::vertex_is_connected_to(int v1, int v2) {
	int j = 0;
	for (auto const &inner_list : adj_list) {
		if (v1 != j) continue;
		for (auto const &val : inner_list)
			if (val == v2) return true;
		break;
	}
	return false;
}

bool ListGraph::is_symmetrical() {
	int j = 0;
	for (auto const &inner_list : adj_list) {
		for (auto const &val : inner_list) {
			if (!vertex_is_connected_to(val, j)) return false;
		}
		j++;
	}
	return true;
}

void ListGraph::reverse() {
	for (auto  &inner_list : adj_list)
		inner_list.reverse();
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
