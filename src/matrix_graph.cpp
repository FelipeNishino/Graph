#include <array>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <stack>
#include <tuple>
#include <algorithm>
#include <numeric>
#include "list_graph.hpp"
#include "matrix_graph.hpp"
#include "logger.hpp"

using std::vector, std::string;

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 1
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

MatrixGraph::MatrixGraph(int _v_count, bool _directed) {
	v_count = _v_count;
	e_count = 0;
    directed = _directed;
    edges_per_vertex = std::vector<int>(v_count, 0);
	vector<int> inner_list(v_count);
	for (int i = 0; i < v_count; i++)
		adj_matrix.push_back(inner_list);
}

MatrixGraph::MatrixGraph(ListGraph g) {
	v_count = g.v_count;
	e_count = g.e_count;

	vector<int> inner_vector(v_count);
	int j = 0;
	for (auto const &inner_list : g.adj_list) {
		for (auto const &val : inner_list) {
			inner_vector[val] = 1;

		}
		adj_matrix.push_back(inner_vector);
		inner_vector.assign(v_count, 0);
		j++;
	}
}

MatrixGraph::MatrixGraph(string filename) {
	std::ifstream file(filename);
	if (file.fail()) {
        Logger::log(Logger::LOG_ERROR, "Erro ao abrir arquivo %s", filename.c_str());
		return;
	}
	string line;

	int step = 0;
	int v1, v2;
	size_t next;
	while(getline(file, line)) {
		switch (step) {
			case 0:
				v_count = stoi(line);
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
    edges_per_vertex[v1]++;
    if (!directed) {
        adj_matrix[v2][v1] = 1;
        edges_per_vertex[v2]++;
    }
	e_count++;
}

void MatrixGraph::remove_edge(int v1, int v2) {
	adj_matrix[v1][v2] = 0;
    edges_per_vertex[v1]--;
    if (!directed) {
        adj_matrix[v2][v1] = 0;
        edges_per_vertex[v2]--;
    }
	e_count--;
}

int MatrixGraph::indegree(int vertex) {
	int degree = 0;
	for (int i = 0; i < v_count; i++) {
		if (i == vertex) continue;
		if (is_adjacent(i, vertex)) degree++;
	}
	return degree;
}

int MatrixGraph::outdegree(int vertex) {
	int degree = 0;
	for (int i = 0; i < v_count; i++) {
		if (i == vertex) continue;
		if (is_adjacent(vertex, i)) degree++;
	}
	return degree;
}

bool MatrixGraph::operator==(MatrixGraph &other) {
	for (int i = 0; i < v_count; i++) {
		for (int j = 0; j < v_count; j++) {
			if (other.adj_matrix[i][j] != adj_matrix[i][j])
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
    if (directed) return true;
	for (int i = 0; i < v_count; i++) {
		for (int j = 0; j < v_count; j++) {
			if (adj_matrix[i][j] != adj_matrix[j][i]) return false;
		}
	}
	return true;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 2
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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
	std::vector<bool> visited(v_count, false);
	int current = seq.front();
	for (auto it=++(seq.begin()); it!=seq.end(); current = *it, visited[current] = true, ++it) {
		if (adj_matrix[current][*it] && !visited[*it]) continue;
		return false;
	}
	return true;
}

bool MatrixGraph::has_path(int u, int v1) {
	DFSLambdas dfsl;
	std::vector<int> nums = {u, v1};
	bool res = false;
    std::vector<bool> visitado = vector<bool>(v_count, false);
	dfsl.entry_condition = [&visitado](int origin, int u, int v, int d)->bool {
        return !visitado[v];
	};
    dfsl.on_step = [&res, &visitado](int origin, int u, int v, int d) {
        visitado[v] = true;
	};
	dfsl.on_end = [&nums, &res](int origin, int u, int v, int d) {
		res |= (nums[0] == origin && nums[1] == v);
	};
	DFS(dfsl, u);

	return res;
}

void MatrixGraph::show_path(int u, int v1) {
	DFSLambdas dfsl;
	std::vector<int> nums = {u, v1};
    std::vector<bool> visitado = vector<bool>(v_count, false);

	std::list<int> path{};
	bool res = false;
    
    dfsl.entry_condition = [&visitado](int origin, int u, int v, int d)->bool {
        return !visitado[v];
	};
	dfsl.on_step = [&path, &res, &visitado](int origin, int u, int v, int d) {
        visitado[v] = true;
        Logger::log(Logger::LOG_DEBUG, "Adicionou %d à lista de visitados.", v);
		if (!res) path.push_back(v);
	};
	dfsl.on_end = [&nums, &res](int origin, int u, int v, int d) {
        Logger::log(Logger::LOG_DEBUG, "Vai testar se chegou em %d, está em %d.", nums[1], v);
		res |= (nums[0] == origin && nums[1] == v);
        Logger::log(Logger::LOG_DEBUG, "%shegou!\n", (res ? "C" : "Não c"));
	};
	dfsl.on_return = [&path, &res](int origin, int u, int v, int d) {
		if (!res) {
            Logger::log(Logger::LOG_DEBUG, "Vai remover %d de visitados.", path.back());
            path.pop_back();
            Logger::log(Logger::LOG_DEBUG, "Removeu %d de visitados.", path.back());
        } else {
            Logger::log(Logger::LOG_DEBUG, "Não fez nada no on return.");
        }
	};

	DFS(dfsl, u);

    if (!res) {
        std::cout << "Nenhum caminho encontrado de " << u << " a " << v1 << '\n';
        return;
    }
	
    std::cout << "Caminho encontrado de " << u << " a " << v1 << ":";
    for (auto const &i : path) {
        std::cout << " -> " << i;
    }
    std::cout << '\n';
	
}

Arborescence MatrixGraph::DFS_arborescence() {
	DFSLambdas dfsl;
    Arborescence a(v_count);
    int time{-1};
    std::vector<bool> visitado = vector<bool>(v_count, false);

    dfsl.entry_condition = [&visitado](int origin, int u, int v, int d)->bool {
        return !visitado[v];
	};
	dfsl.on_step = [&a, &time, &visitado](int origin, int u, int v, int depth) {
        time++;
        a.t_entry[v] = time;
        a.parent[v] = (u == -1 ? v : u);
        visitado[v] = true;
        Logger::log(Logger::LOG_DEBUG, "Adicionou %d à lista de visitados.", v);
	};
	dfsl.on_return = [&a, &time](int origin, int u, int v, int d) {
        a.t_exit[v] = ++time;
	};
    
    
	DFS(dfsl, 0);

    return a;
}

Arborescence::ArchCategory MatrixGraph::has_arch(int v, int w) {
    Arborescence a = DFS_arborescence();
    if (!is_adjacent(v, w)) return Arborescence::ArchCategory::none;
    if (a.t_entry[v] < a.t_entry[w]) {
        return (a.parent[w] == v ? Arborescence::ArchCategory::arborescence : Arborescence::ArchCategory::descendant);
    }
    else {
        return (a.t_exit[w] < a.t_entry[v] ? Arborescence::ArchCategory::cross : Arborescence::ArchCategory::ret);
    }
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 3
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

bool MatrixGraph::has_cicle_with_path() {
	for (auto &v : make_vertex_sequence()) {
        for (auto &w : make_vertex_sequence()) {
            if(is_adjacent(v, w)) {
                if (has_path(w, v)) return true;
            };
        }
    }
	return false;
}

bool MatrixGraph::has_cicle_with_stack() {
	DFSLambdas dfsl;
    std::vector<bool> in_stack(v_count, false);
    bool res = false;
    std::vector<bool> visitado = vector<bool>(v_count, false);

    dfsl.entry_condition = [&visitado](int origin, int u, int v, int d)->bool {
        return !visitado[v];
	};
	dfsl.on_step = [&in_stack, &visitado](int origin, int u, int v, int depth) {
        visitado[v] = true;
        in_stack[v] = true;
	};
    dfsl.on_skip = [&in_stack, &res](int origin, int u, int v, int depth) {
        res |= in_stack[u];
	};
	dfsl.on_return = [&in_stack](int origin, int u, int v, int d) {
        in_stack[v] = false;
	};
    
	DFS(dfsl, 0);
    return res;
}

bool MatrixGraph::has_cicle_with_arborescence() {
	DFSLambdas dfsl;
    Arborescence a = DFS_arborescence();
    
    for (auto v : make_vertex_sequence()) {
        for (auto w : make_vertex_sequence()) {
            if (has_arch(v, w) == Arborescence::ArchCategory::ret) return true;
        }
    }
    return false;
}

bool MatrixGraph::has_cicle_with_colors() {
	return DFS_colors();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 4
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

std::list<int> MatrixGraph::topologic_sort() {
	Arborescence a = DFS_arborescence();
    std::vector<std::tuple<int,int>> aux_vec;
    std::list<int> vertices;
    for (int i = 0; i < v_count; i++) aux_vec.push_back(std::tuple<int,int> (a.t_exit[i], i));
    std::sort(aux_vec.begin(), aux_vec.end(), [](std::tuple<int,int> a, std::tuple<int,int> b){return std::get<0>(a) > std::get<0>(b);});
    for (auto &[t, v] : aux_vec) vertices.push_back(v);
    return vertices;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 5
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

MatrixGraph *MatrixGraph::induced_subgraph(std::set<int> vertices) {
    if (this->directed) {
        std::cout << "O grafo base é direcionado, portanto não tem subgrafo.\n";
        return nullptr;
    }
    if (vertices.size() > this->v_count) {
        std::cout << "O grafo g tem mais vértices que o grafo base, não é subgrafo.\n";
        return nullptr;
    }
    if (std::any_of(vertices.begin(), vertices.end(), [this](int i){return i >= this->v_count;})) {
        std::cout << "O conjunto de vértices não é um subconjunto do grafo base.\n";
        return nullptr;
    }

    MatrixGraph* m = new MatrixGraph(this->v_count);

    for (auto &i : vertices) {
        for (auto &j : vertices) {
            if (is_adjacent(i, j)) {
                m->insert_edge(i, j);
            }
        }
    }
	return m;
}

MatrixGraph *MatrixGraph::edge_induced_subgraph(MatrixGraph g) {
    if (this->directed) {
        std::cout << "O grafo base é direcionado, portanto não tem subgrafo.\n";
        return nullptr;
    }
    if (g.directed) {
        std::cout << "O grafo g é direcionado, portanto não é subgrafo.\n";
        return nullptr;
    }
    if (g.v_count > this->v_count) {
        std::cout << "O grafo g tem mais vértices que o grafo base, não é subgrafo.\n";
        return nullptr;
    }

    MatrixGraph* m = new MatrixGraph(g.v_count);

    for (auto &v : g.make_vertex_sequence()) {
        for (auto &w : g.get_adj_vertices(v)) {
            m->insert_edge(v, w);
        }
    }
    return m;
}

bool MatrixGraph::is_subgraph(MatrixGraph g) {
    if (this->directed) {
        std::cout << "O grafo base é direcionado, portanto não tem subgrafo.\n";
        return false;
    }
    if (g.directed) {
        std::cout << "O grafo g é direcionado, portanto não é subgrafo.\n";
        return false;
    }
    if (g.v_count > this->v_count) {
        std::cout << "O grafo g tem mais vértices que o grafo base, não é subgrafo.\n";
        return false;
    }
    std::set<int> non_isolated_vertices;
    for (auto v : g.make_vertex_sequence()) {
        if (g.edges_per_vertex[v] > 0) non_isolated_vertices.insert(v);
    }

    for (auto &v : this->make_vertex_sequence()) {
        if (v > g.v_count) continue;
        for (auto &w : this->get_adj_vertices(v)) {
            if (w > g.v_count) continue;
            if (
                g.is_adjacent(v, w) && !is_adjacent(v, w)
                // non_isolated_vertices.find(v) != non_isolated_vertices.end() &&
                // non_isolated_vertices.find(w) != non_isolated_vertices.end()
            ) return false;
        }
    }
	return true;
}

bool MatrixGraph::is_spanning_subgraph(MatrixGraph g) {
    if (!is_subgraph(g)) return false;
    for (auto v : g.make_vertex_sequence())
        if (g.edges_per_vertex[v] == 0 || this->edges_per_vertex[v] == 0) return false;
    return true;
}

int MatrixGraph::get_components() {
    DFSLambdas dfsl;
    std::vector<int> cc(v_count, -1);
    int comp = 0;
      
    dfsl.entry_condition = [&cc](int origin, int u, int v, int d)->bool {
        return cc[v] == -1;
	};
	dfsl.on_step = [&cc, &comp](int origin, int u, int v, int depth) {
        cc[v] = comp;
	};
    dfsl.on_return_to_root = [&comp](int v, bool passed_condition) {
        if (passed_condition) comp++;
	};
    
	DFS(dfsl, 0);
    return comp;
}

bool MatrixGraph::is_connected() {
    return get_components() == 1;
}

std::list<std::set<int>> MatrixGraph::kosaraju() {
    std::list<std::set<int>> components;
    if (directed) return components;
    return components;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 6
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

bool MatrixGraph::is_bipartite() {
    DFSLambdas dfsl;
    std::vector<bool> visitado = vector<bool>(v_count, false);
    std::vector<int> cores = vector<int>(v_count, 0);
    int cor = 0;
    std::vector<int> azul{}, vermelho{};
    bool ret = true;
    dfsl.entry_condition = [&visitado, &cores, &ret](int origin, int u, int v, int depth)->bool {
        // if (u != -1) {
        //     if (cores[v] == cores[u]) ret = false;
        // }
        return !visitado[v];
	};
    dfsl.on_step = [&visitado, &cores, &cor](int origin, int u, int v, int depth) {
    	visitado[v] = true;
        cores[v] = cor;
        ++cor %= 2;
	};

    DFS(dfsl);
    for (unsigned int v = 0; v < cores.size(); v++) {
        if (cores[v] == 0) azul.push_back(v); else vermelho.push_back(v);
        for (auto w : get_adj_vertices(v)) {
            if (cores[v] == cores[w]) ret = false;
        }
    }

    std::cout << "Os vértices {";
    for (auto cor : azul) {
        std::cout << " " <<  cor;
    }
    std::cout << " são azuis.\n";
    std::cout << "Os vértices {";
    for (auto cor : vermelho) {
        std::cout << " " <<  cor;
    }
    std::cout << " são vermelhos.\n";
    return ret;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 7
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void MatrixGraph::bridge_detection() {
    int tempo{};
    DFSLambdas dfsl;
    std::vector<int> pre(v_count, -1);
    std::vector<int> pai(v_count, -1);
    std::vector<int> low(v_count, -1);
    bool has_bridge = false;

    dfsl.entry_condition = [&pre](int origin, int u, int v, int depth)->bool {
        return pre[v] == -1;
	};
	dfsl.on_step = [&pai, &pre, &low, &tempo](int origin, int u, int v, int depth) {
        pai[v] = (u == -1 ? v : u);
    	tempo++;
        pre[v] = tempo;
        low[v] = pre[v];
	};
    dfsl.after_visit = [&pai, &pre, &low, &has_bridge](int origin, int u, int v, int d) {
        low[u] = std::min(low[u], low[v]);
        if (low[v] == pre[v]) {
            has_bridge = true;
            std::cout << u << " - " << v << " é uma ponte.\n";
        }
	};
	dfsl.on_skip = [&pai, &pre, &low](int origin, int u, int v, int d) {
        if (u != -1 && v != pai[u])
            low[u] = std::min(low[u], pre[v]);
	};
    DFS(dfsl);

    if (!has_bridge) {
        std::cout << "O grafo não possui pontes.\n";
    }
}
// TODO: o vertice 0 sempre eh considerado um ponto de articulação
void MatrixGraph::articulation_detection() {
    int tempo{};
    DFSLambdas dfsl;
    std::vector<int> pre(v_count, -1);
    std::vector<int> pai(v_count, -1);
    std::vector<int> low(v_count, -1);
    std::vector<int> filhos(v_count, 0);
    std::vector<int> is_articulation(v_count, false);

    dfsl.entry_condition = [&pre](int origin, int u, int v, int depth)->bool {
        return pre[v] == -1;
	};
	dfsl.on_step = [&pai, &pre, &low, &tempo, &filhos](int origin, int u, int v, int depth) {
        pai[v] = (u == -1 ? v : u);
    	tempo++;
        if (u != -1) {
            filhos[u]++;
        }
        pre[v] = tempo;
        low[v] = pre[v];
	};
    dfsl.after_visit = [&pai, &pre, &low, &is_articulation](int origin, int u, int v, int d) {
        low[u] = std::min(low[u], low[v]);
        
        if (low[v] >= pre[u]) is_articulation[u] = true;
	};
	dfsl.on_skip = [&pai, &pre, &low](int origin, int u, int v, int d) {
        if (u != -1 && v != pai[u])
            low[u] = std::min(low[u], pre[v]);
	};
    dfsl.on_return = [&pai, &pre, &low, &is_articulation, &filhos](int origin, int u, int v, int d) {
        if ((pai[v] != -1 && is_articulation[v]) || (pai[v] == -1 && filhos[v] > 0))
            std::cout << "O vértice " << v << " é um ponto de articulação\n";
	};
    DFS(dfsl);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lista 8
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

bool MatrixGraph::is_eulerian() {

}

bool MatrixGraph::has_eulerian_path() {

}

bool MatrixGraph::fleury() {

}

bool MatrixGraph::hierholzer() {

}

void MatrixGraph::short_hamiltonian_path() {

}

void MatrixGraph::DFS(DFSLambdas &dfsl, int origin, int depth){	
    bool condition;
	for (auto const &v : [origin](int n)->vector<int>{vector<int> vec(n); std::iota(vec.begin(), vec.end(), 0); vec.erase(vec.begin() + origin), vec.insert(vec.begin(), origin);return vec;}(v_count)) {
        condition = dfsl.entry_condition(origin, -1, v, depth);
		if (condition) visit(dfsl, origin, depth, -1, v);
        dfsl.on_return_to_root(v, condition);
	}
}

void MatrixGraph::visit(DFSLambdas &dfsl, int origin, int depth, int u, int v) {
    Logger::log(Logger::LOG_DEBUG, "origin %d, visitando %d", origin, v);
	bool did_entry = false;
    Logger::log(Logger::LOG_DEBUG, "Vai executar on step");
	dfsl.on_step(origin, u, v, depth);
	for (auto const &w : get_adj_vertices(v)) {
        Logger::log(Logger::LOG_DEBUG, "Checando se %d se conecta a %d", v, w);
        
		if (Logger::output_level() == Logger::LOG_DEBUG) display();
        if (dfsl.entry_condition(origin, v, w, depth)) {
            Logger::log(Logger::LOG_DEBUG, "vai visitar %d", w);

            visit(dfsl, origin, depth + 1, v, w);
            did_entry = true;
            dfsl.after_visit(origin, v, w, depth);
        }
        else {
            dfsl.on_skip(origin, v, w, depth);
            Logger::log(Logger::LOG_DEBUG, "Não passou na condição da DFS %d", w);
        }
	}
	if (!did_entry) {
        Logger::log(Logger::LOG_DEBUG, "Vai executar on end");
		dfsl.on_end(origin, u, v, depth);
    }
    Logger::log(Logger::LOG_DEBUG, "Vai executar on return");
	dfsl.on_return(origin, u, v, depth);
}

void MatrixGraph::DFS_visita(){
	DFSLambdas dfsl;
    std::vector<bool> visitado = vector<bool>(v_count, false);
  
    dfsl.entry_condition = [&visitado](int origin, int u, int v, int depth)->bool {
        return !visitado[v];
	};
	dfsl.on_step = [&visitado](int origin, int u, int v, int depth) {
    	visitado[v] = true;
	};
    dfsl.on_end = [](int origin, int u, int v, int depth) {
        std::cout << "Chegou numa folha (vertice " << v << ")\n";
	};
    dfsl.on_skip = [](int origin, int u, int v, int depth) {
        std::cout << "Vertice " << v << " não passou na condição\n";
	};
	dfsl.on_return = [](int origin, int u, int v, int d) {
        std::cout << "Retornando para o vertice " << u << "\n";
	};
    
	DFS(dfsl);
}

bool MatrixGraph::DFS_colors() {
    std::vector<int> colors = vector<int>(v_count, 0);
	// Branco == 0, Cinza == 1, Preto == 2
	for (auto const &v : make_vertex_sequence()) {
		if (colors[v] == 0) {
            if (visit_colors(colors, v)) return true;
        }
	}
    return false;
}

bool MatrixGraph::visit_colors(std::vector<int> &colors, int v) {
    colors[v] = 1;
    
    for (auto const &w : get_adj_vertices(v)) {
        switch (colors[w]) {
            case 0:
                if (!visit_colors(colors, w)) break;
            case 1:
                return true;
        }
    }
    colors[v] = 2;
	return false;
}

void MatrixGraph::iterative_dfs(){
	std::vector<bool> visitado = vector<bool>(v_count, false);

    std::stack<int> path;
    for (auto &u : make_vertex_sequence()) {
        if (!visitado[u]) {
            path.push(u); 
            visitado[u] = true;
            // std::cout << "Visita " << path.top() << '\n';
        }
        while (!path.empty()) {
            int v = path.top();
            path.pop();
            std::cout << "Visita " << v << '\n';

            for (int w = v_count-1; w >= 0; w--) {
                if (!is_adjacent(v, w) || visitado[w]) continue;
                path.push(w);
                visitado[w] = true;
            }
        }
    }
}

std::vector<int> MatrixGraph::get_adj_vertices(int v) {
    std::vector<int> adj_v;
    for (int i = 0; i < v_count; i++) if (is_adjacent(v, i)) adj_v.push_back(i);
    return adj_v;
}

std::vector<int> MatrixGraph::make_vertex_sequence() {
    std::vector<int> v(v_count);
    std::iota(v.begin(), v.end(), 0);
    return v;
}

std::vector<int> MatrixGraph::make_vertex_sequence_from_origin(int o) {
    vector<int> v(v_count);
    std::iota(v.begin(), v.end(), 0);
    v.erase(v.begin() + o), v.insert(v.begin(), o);
    
    return v;
}

void MatrixGraph::display() {
    std::string output = "Grafo (Matriz de Adjacência): \n";
	for(int i = 0; i < this->v_count; i++) {
		output += "Vertex ";
        output += std::to_string(i);
        output += " - ";
		for (auto const &val : adj_matrix[i]) {
			output += std::to_string(val);
            output +=  ", ";
		}
        output += '\n';
	}
    output += '\n';

    // Logger::log(Logger::LOG_DEBUG, output);
    std::cout << output;
}