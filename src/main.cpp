#include "include/list_graph.h"
#include "include/matrix_graph.h"
#include <iostream>
#include <list>
#include <vector>

void test_source_sink() {
  MatrixGraph mg(5);
  mg.insert_edge(0, 1);
  mg.insert_edge(1, 2);
  mg.insert_edge(2, 3);
  mg.insert_edge(2, 4);
  mg.insert_edge(3, 1);
  mg.insert_edge(3, 4);
  mg.display();
  std::cout << "O vertice 0" << (mg.vertex_is_source(0) ? "" : "não") << " é fonte" << std::endl;
  std::cout << "O vertice 4" << (mg.vertex_is_sink(4) ? "" : "não") << " é sorvedouro" << std::endl;
}


void test_conversion() {
  MatrixGraph mg(4);
  mg.insert_edge(0, 1);
  mg.insert_edge(1, 2);
  mg.insert_edge(2, 3);
  mg.insert_edge(3, 1);
  mg.display();
  ListGraph lg(mg);
  lg.display();
  MatrixGraph mg2(lg);
  mg2.display();
}

void test_cicle() {
  MatrixGraph mg(4);
  mg.insert_edge(0, 1);
  mg.insert_edge(1, 2);
  mg.insert_edge(2, 3);
  mg.insert_edge(3, 1);
  mg.display();
  std::cout << "O grafo " << ( mg.has_cicle() ? " tem ciclo" : " não tem ciclo" ) << std::endl;
}

void test_symmetry() {
//   Exemplo: o grafo G = (V, E), com V = {1, 2, 3} e arestas E =
// {(1, 2), (2, 1), (1, 3), (3, 1), (2, 3), (3, 2), } é um dígrafo simétrico.
  MatrixGraph mg(3);
  mg.insert_edge(1, 2);
  mg.insert_edge(2, 1);
  mg.insert_edge(1, 3);
  mg.insert_edge(3, 1);
  mg.insert_edge(2, 3);
  mg.insert_edge(3, 2);
  std::cout << "O grafo mg" << ( mg.is_symmetrical() ? "" : "não" ) << " é simétrico" << std::endl;
  ListGraph lg(mg);
  std::cout << "O grafo lg" << ( lg.is_symmetrical() ? "" : "não" ) << " é simétrico" << std::endl;
}

void test_path() {
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
  mg.insert_edge(5, 3);
  mg.display();
  
  std::cout << ( mg.is_path(std::vector<int>{0, 2, 4, 5, 1}) ? "" : "não" ) << " é caminho" << std::endl;
  std::cout << ( mg.is_path(std::vector<int>{0, 2, 5, 1}) ? "" : "não" ) << " é caminho" << std::endl;
  std::cout << ( mg.is_path(std::vector<int>{0, 2, 4, 5}) ? "" : "não" ) << " é caminho" << std::endl;
  std::cout << ( mg.is_path(std::vector<int>{0, 4, 2, 5, 1}) ? "" : "não" ) << " é caminho" << std::endl;
  std::cout << ( mg.is_path(std::vector<int>{0, 2, 4, 5, 3, 4, 1}) ? "" : "não" ) << " é caminho" << std::endl;

  std::cout << ( mg.is_simple_path(std::vector<int>{0, 2, 4, 5, 1}) ? "" : "não" ) << " é caminho simples" << std::endl;
  std::cout << ( mg.is_simple_path(std::vector<int>{0, 2, 5, 1}) ? "" : "não" ) << " é caminho simples" << std::endl;
  std::cout << ( mg.is_simple_path(std::vector<int>{0, 2, 4, 5}) ? "" : "não" ) << " é caminho simples" << std::endl;
  std::cout << ( mg.is_simple_path(std::vector<int>{0, 4, 2, 5, 1}) ? "" : "não" ) << " é caminho simples" << std::endl;
  std::cout << ( mg.is_simple_path(std::vector<int>{0, 2, 4, 5, 3, 4, 1}) ? "" : "não" ) << " é caminho simples" << std::endl;
}

void test_dfs() {
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
  mg.insert_edge(5, 3);
  mg.display();

  mg.DFS();
}

int main() {
  test_dfs();
  // test_source_sink();
  // test_symmetry();
  // test_path();
}