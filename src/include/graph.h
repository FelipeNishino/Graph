#ifndef GRAPH_GRAPH
#define GRAPH_GRAPH

#include <vector>
#include <list>
/*
class _Graph {
public:
  int n; // vertex count
  int m; // edge count

  // _Graph(int v);
  // void insert_edge(int v1, int v2);
  // void remove_edge(int v1, int v2);
  // void display();
};
*/
class MatrixGraph;

class ListGraph {
public:
  int n; // vertex count
  int m; // edge count
  std::list<std::list<int>> adj_list;

  ListGraph(int v);
  ListGraph(MatrixGraph g);
  void insert_edge(int v1, int v2);
  void remove_edge(int v1, int v2);
  bool is_equal(ListGraph g);
  void reverse();
  void display();
};

class MatrixGraph {
public:
  int n; // vertex count
  int m; // edge count
  std::vector<std::vector<int>> adj_matrix;

  MatrixGraph(int v);
  MatrixGraph(ListGraph g);
  void insert_edge(int v1, int v2);
  void remove_edge(int v1, int v2);
  int indegree(int vertex);
  int outdegree(int vertex);
  bool is_equal(MatrixGraph g);
  bool travel_to(int o, int t);
  bool has_cicle();
  void display();
};

#endif //GRAPH_GRAPH