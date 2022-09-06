#ifndef GRAPH_MATRIXGRAPH_H
#define GRAPH_MATRIXGRAPH_H

#include <vector>

class ListGraph;

class MatrixGraph {
public:
  int n; // vertex count
  int m; // edge count
  std::vector<std::vector<int>> adj_matrix;

  MatrixGraph(int v);
  MatrixGraph(ListGraph g);
  MatrixGraph(string filename);
  void insert_edge(int v1, int v2);
  void remove_edge(int v1, int v2);
  int indegree(int vertex);
  int outdegree(int vertex);
  bool is_equal(MatrixGraph g);
  bool vertex_is_source(int v);
  bool vertex_is_sink(int v);
  bool is_symmetrical();
  bool travel_to(int o, int t);
  bool has_cicle();
  void display();
};

#endif //GRAPH_MATRIXGRAPH_H
