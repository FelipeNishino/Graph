#include "include/list_graph.hpp"
#include "include/matrix_graph.hpp"
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
    std::cout << "O grafo " << (mg.has_cicle() ? " tem ciclo" : " não tem ciclo") << std::endl;
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
    std::cout << "O grafo mg" << (mg.is_symmetrical() ? "" : "não") << " é simétrico" << std::endl;
    ListGraph lg(mg);
    std::cout << "O grafo lg" << (lg.is_symmetrical() ? "" : "não") << " é simétrico" << std::endl;
}

void test_path() {
    MatrixGraph mg = MatrixGraph::get_example_graph();
    mg.display();

    std::cout << (mg.is_path(std::vector<int>{0, 2, 4, 5, 1}) ? "" : "não") << " é caminho" << std::endl;
    std::cout << (mg.is_path(std::vector<int>{0, 2, 5, 1}) ? "" : "não") << " é caminho" << std::endl;
    std::cout << (mg.is_path(std::vector<int>{0, 2, 4, 5}) ? "" : "não") << " é caminho" << std::endl;
    std::cout << (mg.is_path(std::vector<int>{0, 4, 2, 5, 1}) ? "" : "não") << " é caminho" << std::endl;
    std::cout << (mg.is_path(std::vector<int>{0, 2, 4, 5, 3, 4, 1}) ? "" : "não") << " é caminho" << std::endl;

    std::cout << (mg.is_simple_path(std::vector<int>{0, 2, 4, 5, 1}) ? "" : "não") << " é caminho simples" << std::endl;
    std::cout << (mg.is_simple_path(std::vector<int>{0, 2, 5, 1}) ? "" : "não") << " é caminho simples" << std::endl;
    std::cout << (mg.is_simple_path(std::vector<int>{0, 2, 4, 5}) ? "" : "não") << " é caminho simples" << std::endl;
    std::cout << (mg.is_simple_path(std::vector<int>{0, 4, 2, 5, 1}) ? "" : "não") << " é caminho simples" << std::endl;
    std::cout << (mg.is_simple_path(std::vector<int>{0, 2, 4, 5, 3, 4, 1}) ? "" : "não") << " é caminho simples"
              << std::endl;
}

void test_has_path() {
    MatrixGraph mg = MatrixGraph::get_example_graph();

    std::cout << (mg.has_path(0, 5)? "Existe " : "Não existe ") << "um caminho entre 0 e 5\n";
	std::cout << (mg.has_path(0, 3)? "Existe " : "Não existe ") << "um caminho entre 0 e 3\n";
	std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
}

void test_show_path() {
    MatrixGraph mg = MatrixGraph::get_example_graph();

    mg.show_path(0, 5);
	mg.show_path(0, 3);
	mg.show_path(1, 2);
}


int main() {
    test_has_path();
	test_show_path();
    // using namespace std::placeholders;    // adds visibility of _1, _2, _3,...
    // auto fn = [](int a, int b)->bool {
    //   return a > b;
    // };

    // auto fn102 = std::bind(fn,10,2);
    // auto fnnorm = std::bind(fn,_1,_2);
    // auto fninv = std::bind(fn,_2,_1);
    // auto fnjust2 = std::bind(fn,_2,_2);
    // auto fnover = std::bind(fn,_2,_3);

    // std::cout << (fn102()? "true" : "false") << '\n';
    // std::cout << (fnnorm(1, 2)? "true" : "false") << '\n';
    // std::cout << (fninv(1, 2)? "true" : "false") << '\n';
    // std::cout << (fnjust2(1, 2)? "true" : "false") << '\n';
    // std::cout << (fnover(1, 2, 0)? "true" : "false") << '\n';

    // test_source_sink();
    // test_symmetry();
    // test_path();
}