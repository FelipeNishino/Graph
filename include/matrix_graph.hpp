#ifndef GRAPH_MATRIXGRAPH_H
#define GRAPH_MATRIXGRAPH_H

#include <functional>
#include <list>
#include <string>
#include <vector>

class ListGraph;

class MatrixGraph {
  public:
    struct DFSLambdas {
        std::function<void(int, int, int)> on_end;
        std::function<void(int, int, int)> on_step;
        std::function<void(int, int, int)> on_return;
        DFSLambdas() : on_end(fnull), on_step(fnull), on_return(fnull){};
    };
    int n; // vertex count
    int m; // edge count
    std::vector<std::vector<int>> adj_matrix;
    static const inline std::function<void(int, int, int)> fnull = [](int a, int b, int d) {};
    MatrixGraph(int v);
    MatrixGraph(ListGraph g);
    MatrixGraph(std::string filename);
    static MatrixGraph get_example_graph() {
        MatrixGraph mg(6);
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
    int indegree(int vertex);
    int outdegree(int vertex);
    bool is_equal(MatrixGraph g);
    bool vertex_is_source(int v);
    bool vertex_is_sink(int v);
    bool is_symmetrical();
    bool is_path(std::vector<int> seq);
    bool is_simple_path(std::vector<int> seq);
    bool has_path(int v0, int v1);
    void show_path(int v0, int v1);
    bool travel_to(int o, int t);
    // const std::function<void()/*type of your lamdba::operator()*/>&

    bool has_cicle();
    void topologic_sort();
    // std::list<int> find_equivalent_vertices(MatrixGraph g, int v);
    MatrixGraph induced_subgraph(MatrixGraph g);
    MatrixGraph edge_induced_subgraph(MatrixGraph g);
    void display();

  private:
    void DFS(DFSLambdas dfsl, int origin = 0, int depth = 0, std::vector<bool> visitado = {});
    void visit(DFSLambdas dfsl, int origin, int depth, std::vector<bool> &visitado, int v);
};

#endif // GRAPH_MATRIXGRAPH_H
