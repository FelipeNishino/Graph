#include <array>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <algorithm>
#include <numeric>
#include "include/list_graph.hpp"
#include "include/matrix_graph.hpp"

using std::vector, std::string;

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
	std::ifstream file(filename);
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
			if (adj_matrix[i][j] != adj_matrix[j][i])
				return false;
		}
	}
	return true;
}

bool MatrixGraph::is_path(std::vector<int> seq) {
	if (seq.empty()) return false;
	
	int current = seq.front();
	for (auto it=++(seq.begin()); it!=seq.end(); current = *it, ++it) {
		if (adj_matrix[current][*it]) continue;
		return false;
	}
	return true;
}


bool MatrixGraph::is_simple_path(std::vector<int> seq) {
	if (seq.empty()) return false;
	std::vector<bool> visited(n, false);
	int current = seq.front();
	for (auto it=++(seq.begin()); it!=seq.end(); current = *it, visited[current] = true, ++it) {
		if (adj_matrix[current][*it] && !visited[*it]) continue;
		return false;
	}
	return true;
}

bool MatrixGraph::has_path(int v0, int v1) {
	DFSLambdas dfsl;
	std::vector<int> nums = {v0, v1};
	bool res = false;
	
	dfsl.on_end = [&nums, &res](int origin, int v, int d) {
		// std::cout << "origin " << origin << " atual " << v << " checando " << nums[0] << " e " << nums[1] << " depth " << d << '\n';
		res |= (nums[0] == origin && nums[1] == v);
	};
	DFS(dfsl, v0);

	return res;
}

void MatrixGraph::show_path(int v0, int v1) {
	DFSLambdas dfsl;
	std::vector<int> nums = {v0, v1};
	std::vector<int> path{n};
	bool res = false;

	dfsl.on_step = [&path, &res](int origin, int v, int d) {
		// std::cout << "origin " << origin << " atual " << v << " checando " << nums[0] << " e " << nums[1] << " depth " << d << '\n';
		// res |= (nums[0] == origin && nums[1] == v);
		std::cout << "Adicionou " << v << '\n';
		if (!res) path.push_back(v);
	};
	dfsl.on_end = [&nums, &res](int origin, int v, int d) {
		// std::cout << "origin " << origin << " atual " << v << " checando " << nums[0] << " e " << nums[1] << " depth " << d << '\n';
		std::cout << "Vai testar se chegou, está no " << v << '\n';
		res |= (nums[0] == origin && nums[1] == v);
		if (nums[0] == origin && nums[1] == v) {
			std::cout << "Chegou!\n";
		}
	};
	dfsl.on_return = [&path, &res](int origin, int v, int d) {
		// std::cout << "origin " << origin << " atual " << v << " checando " << nums[0] << " e " << nums[1] << " depth " << d << '\n';
		std::cout << "Removeu " << path.back() << '\n';
		if (!res) path.erase(path.end());
	};

	DFS(dfsl, v0);

	if (res) {
		std::cout << "Caminho encontrado de " << v0 << " a " << v1 << ":";
		for (auto const &i : path) {
			std::cout << " " << i;
		}
		std::cout << '\n';
	}
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

void MatrixGraph::topologic_sort() {
	std::list<std::list<int>> sublists;
	sublists.push_back({});
	int vo;
	
	for (int i = 0; i < n; ++i) {
		if (!vertex_is_source(i)) continue;
	}

}

// std::list<int> find_equivalent_vertices(MatrixGraph g, int v) {
// 	int i, j;

// 	for (i = 0; i < g.n; i++) {
// 		bool eq = true;
// 		for (j = 0; j < g.n; j++) {

// 		}	
// 	}
// }

MatrixGraph induced_subgraph(MatrixGraph g) {
	

	return g;
}

MatrixGraph edge_induced_subgraph(MatrixGraph g) {
	return g;
}

void MatrixGraph::display() {
	for(int i = 0; i < this->n; i++) {
		std::cout << "Vertex " << i << " - ";
		for (auto const &val : adj_matrix[i]) {
			std::cout << val << ", ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

// DFS(G)
// 1 para cada vértice u em V (G) faça
// 2 marque u como não visitado
// 3 para cada vértice u em V (G) faça
// 4 se u não foi visitado então
// 5 DFS-visita(G, u)

void MatrixGraph::DFS(DFSLambdas dfsl, int origin, int depth, std::vector<bool> visitado){
	if (visitado.size() == 0) visitado = vector<bool>(n, false);
	
	for (auto const &vp : [origin](int n)->vector<int>{vector<int> v(n); std::iota(v.begin(), v.end(), 0); v.erase(v.begin() + origin), v.insert(v.begin(), origin);return v;}(n)) {
		if (!visitado[vp]) visit(dfsl, vp, depth, visitado, vp);
	}
}

// DFS-visita(G, u)
// 1 marque u como visitado
// 2 para cada vértice w em adj(u) faça
// 3 se w não foi visitado então
// 4 DFS-visita(G, w)

void MatrixGraph::visit(DFSLambdas dfsl, int origin, int depth, std::vector<bool> &visitado, int v) {
	std::cout << "origin "<< origin << " visitando " << v << '\n';
	visitado[v] = true;
	bool visitou = false;
	dfsl.on_step(origin, v, depth);
	for (auto const &vp : [](int n)->vector<int>{vector<int> v(n); std::iota(v.begin(), v.end(), 0);return v;}(n)) {
		std::cout << "testando " << vp << '\n';
		display();
		if (!visitado[vp] && adj_matrix[v][vp]) {
			std::cout << "vai visitar " << vp << '\n';

			visit(dfsl, origin, depth + 1, visitado, vp);
			visitou = true;
		}
		else {
			std::cout << "Não visitou " << vp << '\n';
		}
	}
	if (!visitou)
		dfsl.on_end(origin, v, depth);
	dfsl.on_return(origin, v, depth);
}