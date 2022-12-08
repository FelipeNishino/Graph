#ifndef GRAPH_MATRIXGRAPH_H
#define GRAPH_MATRIXGRAPH_H

#include <functional>
#include <list>
#include <numeric>
#include <string>
#include <vector>
#include <set>

class ListGraph;

class Arborescence {
    public:
    
    enum ArchCategory {
        arborescence,
        descendant,
        ret,
        cross,
        none
    };
    
    std::vector<int> t_entry;
    std::vector<int> t_exit;
    std::vector<int> parent;
    Arborescence(int v_count) : t_entry(v_count, -1), t_exit(v_count, -1), parent(v_count, -1){};
};

class MatrixGraph {
  public:
  
    /*
    Momentos de execução:
    on_end: Quando a DFS chega em uma folha
    on_step: Quando a DFS visita um vértice
    on_skip: Quando um vértice não passa na condição de visita
    on_return_to_root: Quando a recursão volta para a raíz
    on_return: Quando um vértice termina de ser visitado e vai subir na recursão
    after_visit: Após a chamada recursiva de uma visita, ainda dentro da condição de entrada
    entry_condition: Função que computa a condição de entrada em um vértice
    */
    struct DFSLambdas {
        std::function<void(int, int, int, int)> on_end; 
        std::function<void(int, int, int, int)> on_step;
        std::function<void(int, int, int, int)> on_skip;
        std::function<void(int, bool)> on_return_to_root;
        std::function<void(int, int, int, int)> on_return;
        std::function<void(int, int, int, int)> after_visit;
        std::function<bool(int, int, int, int)> entry_condition;
        DFSLambdas() : on_end(fnulla), on_step(fnulla), on_skip(fnulla), on_return_to_root(fnullb), on_return(fnulla), after_visit(fnulla){};
    };

    /*
    Momentos de execução:
    on_entry: Quando a BFS entra em um vértice
    on_not_entry: Quando um vértice não passa na condição de visita
    entry_condition: Função que computa a condição de entrada em um vértice
    on_exit: Quando um vértice tem todos os seus adjacentes processados
    */
    struct BFSLambdas {
        std::function<void(int, int)> on_entry;
        std::function<void(int, int)> on_not_entry;
        std::function<bool(int, int)> entry_condition;
        std::function<void(int)> on_exit;
        BFSLambdas() : on_entry(fnullc), on_not_entry(fnullc), on_exit(fnulld){};
    };

    enum WeightType {
        none,
        edge_weight,
        vertix_weight
    };

    int v_count; // vertex count
    int e_count; // edge count
    std::vector<int> edges_per_vertex; // edge count
    bool directed;
    std::vector<std::vector<int>> adj_matrix;
    WeightType weighted;
    std::vector<std::vector<int>> weights;
    static const inline std::function<void(int, int, int, int)> fnulla = [](int a, int b, int c, int d) {};
    static const inline std::function<void(int, bool)> fnullb = [](int a, bool b) {};
    static const inline std::function<void(int, int)> fnullc = [](int a, int b) {};
    static const inline std::function<void(int)> fnulld = [](int a) {};
    
    // LISTA 1
    MatrixGraph(int _n, bool _directed = true, WeightType _weighted = none);
    MatrixGraph(ListGraph g); // EX 5
    MatrixGraph(std::string filename); // EX 7
    static MatrixGraph get_example_graph(bool directed = true) {
        MatrixGraph mg(6, directed);
        mg.insert_edge(0, 2);
        mg.insert_edge(0, 3);
        mg.insert_edge(0, 4);
        mg.insert_edge(2, 1);
        mg.insert_edge(2, 4);
        mg.insert_edge(3, 4);
        mg.insert_edge(3, 5);
        mg.insert_edge(4, 1);
        mg.insert_edge(4, 5);
        mg.insert_edge(5, 1);
        return mg;
    }
    void insert_edge(int v1, int v2);
    void remove_edge(int v1, int v2);
    int indegree(int vertex); // EX 3
    int outdegree(int vertex); // EX 3
    bool operator==(MatrixGraph &other); // EX 4
    bool vertex_is_source(int v); // EX 8
    bool vertex_is_sink(int v); // EX 9
    bool is_symmetrical(); // EX 10

    // LISTA 2
    bool is_path(std::vector<int> seq); // EX 1
    bool is_simple_path(std::vector<int> seq); // EX 2
    bool has_path(int v0, int v1); // EX 3
    void show_path(int v0, int v1); // EX 4
    void DFS_visit();
    // FUNCAO DE DFS DECLARADA NO ESCOPO PRIVATE
    void iterative_dfs(); // EX 5
    Arborescence DFS_arborescence();
    Arborescence::ArchCategory has_arch(int v, int w); // EX 6

    // LISTA 3
    bool has_cycle_with_path(); // EX 1
    bool has_cycle_with_stack(); // EX 2
    bool has_cycle_with_arborescence(); // EX 3
    bool has_cycle_with_colors(); // EX 4

    // LISTA 4
    std::list<int> topologic_sort();  // EX 1

    // LISTA 5
    MatrixGraph *induced_subgraph(std::set<int> vertices); // EX 1, 4
    MatrixGraph *edge_induced_subgraph(MatrixGraph g); // EX 1
    bool is_subgraph(MatrixGraph g); // EX 2
    bool is_spanning_subgraph(MatrixGraph g); // EX 3
    int get_components(); // EX 5
    bool is_connected(); // EX 6
    std::list<std::set<int>> kosaraju(); // EX 7

    // LISTA 6
    bool is_bipartite(); // EX 1, 2

    // LISTA 7
    void bridge_detection(); // EX 1, 2
    void articulation_detection(); // EX 3, 4

    // LISTA 8
    bool is_eulerian(); // EX 1
    bool has_eulerian_trail(); // EX 2
    void fleury(); // EX 3
    void eulerian_trail(int v, std::vector<int> &eulerian_trail);
    void hierholzer(); // EX 4
    void short_hamiltonian_path(); // EX 5
    // void DFS_colors();

    // LISTA 9
    /*
    Similar a função de DFS, a função de dbfs foi implementada de maneira genérica.
    A definição da struct BFSLambdas tem comentários que explicam em que momento 
    cada função é executada.
    */
    void BFS(BFSLambdas bfsl, int o);
    void BFS_visit(int o);
    void BFS_color(int o);
    
    // LISTA 10
    void djikstra(int o);
    void djikstra_vertix(int o, std::vector<int> p);
    void djikstra_heap(int o);

    // LISTA 11
    void relax(int u, int v, std::vector<float> &d, std::vector<int> &pi);
    bool bellman_ford(int o);

    // LISTA 12
    std::vector<std::vector<int>> floyd_warshall();

    void display();
    void display_visitados(std::vector<bool> &visitado);
  private:
    /*
    A função de dfs foi implementada de maneira genérica para que possa ser
    reaproveitada em diversos exercícios. As particularidades de cada
    algoritmo são implementadas por meio dasx funções lambda passadas
    como parametro na struct DFSLambdas. A definição da struct tem comentários
    que explicam em que momento cada função é executada.
    */
    void DFS(DFSLambdas &dfsl, int origin = 0, int depth = 0);
    void DFS_recursion(DFSLambdas &dfsl, int origin, int depth, int v0, int v);
    bool is_adjacent(int v, int w);
    std::vector<int> make_vertex_sequence();
    std::vector<int> make_vertex_sequence_from_origin(int o);
    std::vector<int> get_adj_vertices(int v);
};

#endif // GRAPH_MATRIXGRAPH_H
