#ifndef GRAPH_MATRIXGRAPH_H
#define GRAPH_MATRIXGRAPH_H

#include <vector>
#include <string>
#include <list>

class ListGraph;

class MatrixGraph {
public:
  int n; // vertex count
  int m; // edge count
  std::vector<std::vector<int>> adj_matrix;

  MatrixGraph(int v);
  MatrixGraph(ListGraph g);
  MatrixGraph(std::string filename);
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
  bool travel_to(int o, int t);
  void DFS(std::vector<bool> visitado={});
  void visit(std::vector<bool> visitado, int v);
  bool has_cicle();
  void topologic_sort();
  // std::list<int> find_equivalent_vertices(MatrixGraph g, int v);
  MatrixGraph induced_subgraph(MatrixGraph g);
  MatrixGraph edge_induced_subgraph(MatrixGraph g);
  void display();
};

#endif //GRAPH_MATRIXGRAPH_H
