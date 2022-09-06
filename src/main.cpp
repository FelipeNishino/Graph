#include "include/graph.h"
#include <iostream>

int main() {
  // (1, 2), (1, 3), (2, 3), (2, 4), (2, 5), (3, 4), (4, 5)
  MatrixGraph mg(4);
  // ListGraph mg(6);
  // mg.insert_edge(1, 2);
  // mg.insert_edge(1, 3);
  // mg.insert_edge(2, 1);
  // mg.insert_edge(2, 3);
  // mg.insert_edge(2, 4);
  // mg.insert_edge(2, 5);
  // mg.insert_edge(3, 4);
  // mg.insert_edge(4, 5);
  // mg.display();
  // mg.remove_edge(3, 4);
  // mg.remove_edge(3, 2);
  // std::cout << "Grau de entrada do vertice 1: " << mg.indegree(1) << std::endl;
  // std::cout << "Grau de saida do vertice 1: " << mg.outdegree(1) << std::endl;
  mg.insert_edge(0, 1);
  mg.insert_edge(1, 2);
  mg.insert_edge(2, 3);
  mg.insert_edge(3, 1);
  // mg.insert_edge(0, 2);
  // mg.insert_edge(0, 3);
  // mg.insert_edge(0, 4);
  // mg.insert_edge(2, 1);
  // mg.insert_edge(3, 4);
  // mg.insert_edge(3, 5);
  // mg.insert_edge(4, 1);
  // mg.insert_edge(4, 2);
  // mg.insert_edge(4, 5);
  // mg.insert_edge(5, 1);
  mg.display();
  ListGraph lg(mg);
  lg.display();
  MatrixGraph mg2(lg);
  mg2.display();
  std::cout << "O grafo " << ( mg.has_cicle() ? "tem ciclo" : "não tem ciclo" ) << std::endl;
}