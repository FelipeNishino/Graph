#ifndef GRAPH_LISTGRAPH_H
#define GRAPH_LISTGRAPH_H

#include <list>
#include <string>
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
  ListGraph(std::string filename);
  void insert_edge(int v1, int v2);
  void remove_edge(int v1, int v2);
  int indegree(int vertex);
  int outdegree(int vertex);
  bool is_equal(ListGraph g);
  bool vertex_is_source(int v);
  bool vertex_is_sink(int v);
  bool vertex_is_connected_to(int v1, int v2);
  bool is_symmetrical();
  void reverse();
  void display();
};



#endif //GRAPH_LISTGRAPH_H