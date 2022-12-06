#include "list_graph.hpp"
#include "logger.hpp"
#include "matrix_graph.hpp"
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <algorithm>
#include <getopt.h>

static int flags{};

enum MAIN_FLAGS {
    FLAG_DEBUG = 1,
    FLAG_INFO = 1 << 1,
    FLAG_WARNING = 1 << 2,
    FLAG_INVALID = 1 << 3
};

void usage() {
    std::cout << "Usage: ./graph.out [OPTIONS]\n";
    std::cout << "-d\t--debug\t\tSet log level to debug\n";
    std::cout << "-i\t--info\t\tSet log level to info\n";
    std::cout << "-w\t--warning\t\tSet log level to warnings\n";
    if (flags ^ FLAG_DEBUG || flags ^ FLAG_INFO || flags ^ FLAG_WARNING) {
        std::cout << "\nInvalid flag usage: received only --no-play, won't do anything\n";
    }
}

void get_options(int argc, char* const* argv) {
    int c = 0;

    static const struct option options[] = {
        {"debug",     no_argument,        &flags, FLAG_DEBUG},
        {"info",     no_argument,        &flags, FLAG_INFO},
        {"warning",  no_argument,        &flags, FLAG_WARNING},
        // {"features",    optional_argument,  &flags, FLAG_INVALID},
        {"help",        no_argument,        &flags, FLAG_INVALID},
        {"loglevel",    required_argument,  0, 'l'},
        
        {0,             0,                  0,  0 }
    };
    
    int option_index = 0;

    while ((c = getopt_long(argc, argv, "dhil:w", options, &option_index)) != -1) {
        switch (c) {
        case 0:
          /* If this option set a flag, do nothing else now. */
            if (options[option_index].flag != 0) break;
            printf("option %s", options[option_index].name);
            if (optarg) printf(" with arg %s", optarg);
            printf("\n");
            break;
        case 'd':
            flags |= FLAG_DEBUG;
            break;
        case 'h':
            flags |= FLAG_INVALID;
            break;
        case 'i':
            flags |= FLAG_INFO;
            break;
        case 'l':
            Logger::set_output_level(static_cast<Logger::LogLevel>(atoi(optarg)));
            break;
        case 'w':
            flags |= FLAG_WARNING;
            break;
        default:
            usage();
            exit(EXIT_FAILURE);
        }
    }

    if (flags & FLAG_INVALID) {
        usage();
        exit(EXIT_FAILURE);
    }
    if (flags & FLAG_DEBUG )  {
        Logger::set_output_level(Logger::LOG_DEBUG);
    }
    if (flags & FLAG_INFO )  {
        Logger::set_output_level(Logger::LOG_INFO);
    }
    if (flags & FLAG_WARNING )  {
        Logger::set_output_level(Logger::LOG_WARNING);
    }
}

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
    // int i = 0;
    std::cout << (mg.has_path(0, 5)? "Existe " : "Não existe ") << "um caminho entre 0 e 5\n";
	std::cout << (mg.has_path(0, 3)? "Existe " : "Não existe ") << "um caminho entre 0 e 3\n";
	std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
}

void test_show_path() {
    MatrixGraph mg = MatrixGraph::get_example_graph();
    mg.display();
    mg.show_path(0, 5);
	mg.show_path(0, 3);
	mg.show_path(1, 2);
    mg.show_path(4, 1);
    mg.show_path(4, 3);
}

void test_iterative_DFS() {
    MatrixGraph mg = MatrixGraph::get_example_graph();
    mg.iterative_dfs();
}

void test_arborescence() {
    MatrixGraph mg = MatrixGraph::get_example_graph();
    mg.DFS_arborescence();
}

void arch_type_to_str(int v, int w, Arborescence::ArchCategory cat) {
    std::cout << "O arco " << v << "-" << w << " é um Arco ";
    switch (cat) {
        case Arborescence::arborescence:
            std::cout << "de Arborescência";
            break;
        case Arborescence::descendant:
            std::cout << "Descendente";
            break;
        case Arborescence::ret:
            std::cout << "de Retorno";
            break;
        case Arborescence::cross:
            std::cout << "Cruzado";
            break;
        case Arborescence::none:
            break;
    }
    std::cout << '\n';
}

void test_has_arch() {
    MatrixGraph mg = MatrixGraph(8);
    mg.insert_edge(0, 5);
    mg.insert_edge(0, 7);
    mg.insert_edge(1, 5);
    mg.insert_edge(2, 1);
    mg.insert_edge(3, 4);
    mg.insert_edge(3, 6);
    mg.insert_edge(4, 0);
    mg.insert_edge(4, 7);
    mg.insert_edge(5, 2);
    mg.insert_edge(5, 7);
    mg.insert_edge(6, 3);
    mg.insert_edge(6, 4);
    mg.insert_edge(7, 1);

    Logger::log(Logger::LOG_INFO, "Testes da função de arborescência com o grafo do slide 72 da aula 2");

    mg.display();

    arch_type_to_str(0, 5, mg.has_arch(0, 5));
    arch_type_to_str(0, 7, mg.has_arch(0, 7));
    arch_type_to_str(1, 5, mg.has_arch(1, 5));
    arch_type_to_str(2, 1, mg.has_arch(2, 1));
    arch_type_to_str(3, 4, mg.has_arch(3, 4));
    arch_type_to_str(3, 6, mg.has_arch(3, 6));
    arch_type_to_str(4, 0, mg.has_arch(4, 0));
    arch_type_to_str(4, 7, mg.has_arch(4, 7));
    arch_type_to_str(5, 2, mg.has_arch(5, 2));
    arch_type_to_str(5, 7, mg.has_arch(5, 7));
    arch_type_to_str(6, 3, mg.has_arch(6, 3));
    arch_type_to_str(6, 4, mg.has_arch(6, 4));
    arch_type_to_str(7, 1, mg.has_arch(7, 1));
}

void test_cicle() {
    MatrixGraph mg(4);
    mg.insert_edge(0, 1);
    mg.insert_edge(1, 2);
    mg.insert_edge(2, 3);
    mg.insert_edge(3, 1);
    mg.display();
    std::cout << "O grafo " << (mg.has_cicle_with_path() ? "tem ciclo" : "não tem ciclo") << std::endl;
    std::cout << "O grafo " << (mg.has_cicle_with_stack() ? "tem ciclo" : "não tem ciclo") << std::endl;
    std::cout << "O grafo " << (mg.has_cicle_with_arborescence() ? "tem ciclo" : "não tem ciclo") << std::endl;
    std::cout << "O grafo " << (mg.has_cicle_with_colors() ? "tem ciclo" : "não tem ciclo") << std::endl;
}

void test_topologic_sort() {
    MatrixGraph mg = MatrixGraph::get_example_graph();
    std::list<int> l = mg.topologic_sort();
    std::cout << "Vertices do topologic sort: ";
    for (auto x : l) {
        std::cout << x << " ";
    }
    std::cout << '\n';
}

void test_subgraph() {
    MatrixGraph mg = MatrixGraph::get_example_graph(false);
    MatrixGraph* mgsub = mg.induced_subgraph({0, 2, 3, 5});
    std::cout << "Grafo base:\n";
    mg.display();
    if (mgsub != nullptr) {
        std::cout << "Subgrafo induzido por {0, 2, 3, 5}:\n";
        mgsub->display();
    }
    else {
        std::cout << "O Grafo passado não é um subgrafo de mg\n";
    }

    mgsub = mg.induced_subgraph({5, 1});
    if (mgsub != nullptr) {
        std::cout << "Subgrafo induzido por {5, 1}:\n";
        mgsub->display();
    }
    else {
        std::cout << "O Grafo passado não é um subgrafo de mg\n";
    }
    // mg = MatrixGraph(6);

    MatrixGraph g1 = MatrixGraph(6, false);
    g1.insert_edge(2, 1);
    g1.insert_edge(2, 4);
    g1.insert_edge(4, 1);
    g1.insert_edge(4, 5);
    g1.insert_edge(5, 1);
    if (!mg.is_subgraph(g1)) {
        std::cout << "O grafo g1 não é um subgrafo de mg\n";
    } else {
        std::cout << "O grafo g1 é um subgrafo de mg\n";
    }

    MatrixGraph g2 = MatrixGraph(6, false);
    g2.insert_edge(2, 1);
    g2.insert_edge(2, 4);
    g2.insert_edge(4, 5);
    g2.insert_edge(5, 1);
    if (!mg.is_subgraph(g2)) {
        std::cout << "O grafo g2 não é um subgrafo de mg\n";
    } else {
        std::cout << "O grafo g2 é um subgrafo de mg\n";
    }

    MatrixGraph g3 = MatrixGraph(5, false);
    g3.insert_edge(0, 1);
    g3.insert_edge(1, 2);
    g3.insert_edge(2, 3);
    g3.insert_edge(3, 4);
    g3.insert_edge(4, 2);

    std::cout << "g3: \n";
    g3.display();

    MatrixGraph g4 = MatrixGraph(5, false);
    g4.insert_edge(0, 1);
    g4.insert_edge(1, 2);
    g4.insert_edge(2, 3);
    std::cout << "g4: \n";
    g4.display();
    if (!g3.is_subgraph(g4)) {
        std::cout << "O grafo g4 não é um subgrafo de g3\n";
    } else {
        std::cout << "O grafo g4 é um subgrafo de g3\n";
    }
    if (!g3.is_spanning_subgraph(g4)) {
        std::cout << "O grafo g4 não é um subgrafo gerador de g3\n";
    } else {
        std::cout << "O grafo g4 é um subgrafo gerador de g3\n";
    }

    MatrixGraph g5 = MatrixGraph(5, false);
    g5.insert_edge(0, 1);
    g5.insert_edge(1, 2);
    g5.insert_edge(2, 3);
    g5.insert_edge(3, 4);
    std::cout << "g5: \n";
    g5.display();
    if (!g3.is_subgraph(g5)) {
        std::cout << "O grafo g5 não é um subgrafo de g3\n";
    } else {
        std::cout << "O grafo g5 é um subgrafo de g3\n";
    }
    if (!g3.is_spanning_subgraph(g5)) {
        std::cout << "O grafo g5 não é um subgrafo gerador de g3\n";
    } else {
        std::cout << "O grafo g5 é um subgrafo gerador de mg\n";
    }
}

void test_components() {
    MatrixGraph g1 = MatrixGraph(5, false);
    g1.insert_edge(0, 1);
    g1.insert_edge(1, 2);
    g1.insert_edge(2, 0);
    g1.insert_edge(3, 4);
    // g1.insert_edge(5, 6);
    // g1.insert_edge(6, 7);
    // g1.insert_edge(7, 5);
    std::cout << "g1:\n";
    g1.display();
    std::cout << "Qtd de componentes em g1: " << g1.get_components() << '\n';
    std::cout << "O grafo g1" << (!g1.is_connected() ? " não " : " ") << "é conexo.\n";

    MatrixGraph g2 = MatrixGraph(4, false);
    g2.insert_edge(0, 1);
    g2.insert_edge(0, 2);
    g2.insert_edge(1, 2);
    g2.insert_edge(1, 3);
    g2.insert_edge(2, 3);
    g2.insert_edge(3, 0);
    std::cout << "g2:\n";
    g2.display();
    std::cout << "Qtd de componentes em g2: " << g2.get_components() << '\n';
    std::cout << "O grafo g2" << (!g2.is_connected() ? " não " : " ") << "é conexo.\n";
};

void test_bipartition() {
    MatrixGraph g1 = MatrixGraph(5, false);
    g1.insert_edge(0, 1);
    g1.insert_edge(1, 2);
    g1.insert_edge(2, 3);
    g1.insert_edge(3, 4);

    std::string output;
    std::cout << "g1:\n";
    g1.display();
    output += "O grafo g1" ;
    output += (!g1.is_bipartite() ? " não " : " ");
    output += "é bipartido.\n";
    std::cout << output;
    
    MatrixGraph g2 = MatrixGraph(8, false);
    g2.insert_edge(0, 1);
    g2.insert_edge(0, 3);
    g2.insert_edge(0, 4);
    g2.insert_edge(1, 2);
    g2.insert_edge(1, 5);
    g2.insert_edge(2, 3);
    g2.insert_edge(2, 6);
    g2.insert_edge(3, 7);
    g2.insert_edge(4, 5);
    g2.insert_edge(5, 6);
    g2.insert_edge(6, 7);
    g2.insert_edge(7, 4);

    output = "";
    std::cout << "g2:\n";
    g2.display();
    output += "O grafo g2" ;
    output += (!g2.is_bipartite() ? " não " : " ");
    output += "é bipartido.\n";
    std::cout << output;

    MatrixGraph g3 = MatrixGraph(4, false);
    g3.insert_edge(0, 1);
    g3.insert_edge(0, 2);
    g3.insert_edge(0, 3);
    g3.insert_edge(1, 2);
    g3.insert_edge(2, 3);

    output = "";
    std::cout << "g3:\n";
    g3.display();
    output += "O grafo g3" ;
    output += (!g3.is_bipartite() ? " não " : " ");
    output += "é bipartido.\n";
    std::cout << output;

    MatrixGraph g4 = MatrixGraph(5, false);
    g4.insert_edge(0, 1);
    g4.insert_edge(0, 2);
    g4.insert_edge(1, 2);
    g4.insert_edge(2, 3);
    g4.insert_edge(3, 4);
    g4.insert_edge(4, 1);

    output = "";
    std::cout << "g4:\n";
    g4.display();
    output += "O grafo g4" ;
    output += (!g4.is_bipartite() ? " não " : " ");
    output += "é bipartido.\n";
    std::cout << output;

    MatrixGraph g5 = MatrixGraph(6, false);
    g5.insert_edge(0, 1);
    g5.insert_edge(0, 2);
    g5.insert_edge(0, 3);
    g5.insert_edge(1, 3);
    g5.insert_edge(1, 4);
    g5.insert_edge(2, 3);
    g5.insert_edge(2, 5);
    g5.insert_edge(3, 4);
    g5.insert_edge(3, 5);
    g5.insert_edge(4, 5);

    output = "";
    std::cout << "g5:\n";
    g5.display();
    output += "O grafo g5" ;
    output += (!g5.is_bipartite() ? " não " : " ");
    output += "é bipartido.\n";
    std::cout << output;
}

void test_bridge_detection() {
    // G′ = {(0, 1), (0, 2), (1, 2), (2, 3), (2, 4), (4, 5), (4, 7), (5, 6), (6, 7)}
    MatrixGraph g1 = MatrixGraph(8, false);
    g1.insert_edge(0, 1);
    g1.insert_edge(1, 2);
    g1.insert_edge(2, 0);
    g1.insert_edge(1, 3);
    g1.insert_edge(3, 4);
    g1.insert_edge(4, 5);
    g1.insert_edge(5, 3);
    
    MatrixGraph g2 = MatrixGraph(8, false);
    g2.insert_edge(0, 1);
    g2.insert_edge(0, 2);
    g2.insert_edge(1, 2);
    g2.insert_edge(2, 3);
    g2.insert_edge(2, 4);
    g2.insert_edge(4, 5);
    g2.insert_edge(4, 7);
    g2.insert_edge(5, 6);
    g2.insert_edge(6, 7);
    // G′ = {(0, 1), (1, 2), (2, 3), (2, 4), (4, 5), (5, 6), (6, 7)}
    MatrixGraph g3 = MatrixGraph(8, false);
    g3.insert_edge(0, 1);
    g3.insert_edge(1, 2);
    g3.insert_edge(2, 3);
    g3.insert_edge(2, 4);
    g3.insert_edge(4, 5);
    g3.insert_edge(5, 6);
    g3.insert_edge(6, 7);
    // G′ = {(0, 1), (0, 3), (1, 2), (1, 7), (2, 3), (2, 4), (4, 5), (5, 6), (6, 7)}
    MatrixGraph g4 = MatrixGraph(8, false);
    g4.insert_edge(0, 1);
    g4.insert_edge(0, 3);
    g4.insert_edge(1, 2);
    g4.insert_edge(1, 7);
    g4.insert_edge(2, 3);
    g4.insert_edge(2, 4);
    g4.insert_edge(4, 5);
    g4.insert_edge(5, 6);
    g4.insert_edge(6, 7);

    std::cout << "g1:\n";
    g1.display();
    g1.bridge_detection();
    std::cout << "g2:\n";
    g2.display();
    g2.bridge_detection();
    std::cout << "g3:\n";
    g3.display();
    g3.bridge_detection();
    std::cout << "g4:\n";
    g4.display();
    g4.bridge_detection();
}

void test_articulation_detection() {
    // G′ = {(0, 1), (0, 2), (1, 2), (2, 3), (2, 4), (4, 5), (4, 6), (4, 7), (5, 6), (6, 7)}
    // G′ = {(0, 1), (0, 3), (0, 6), (1, 2), (1, 4), (1, 5), (2, 3), (4, 5), (4, 7)}

    MatrixGraph g1 = MatrixGraph(6, false);
    g1.insert_edge(0, 1);
    g1.insert_edge(1, 2);
    g1.insert_edge(2, 0);
    g1.insert_edge(1, 3);
    g1.insert_edge(3, 4);
    g1.insert_edge(4, 5);
    g1.insert_edge(5, 3);
    std::cout << "g1:\n";
    g1.display();
    g1.articulation_detection();
    
    MatrixGraph g2 = MatrixGraph(6, false);
    g2.insert_edge(0, 1);
    g2.insert_edge(1, 2);
    g2.insert_edge(2, 0);
    g2.insert_edge(0, 3);
    g2.insert_edge(3, 4);
    g2.insert_edge(4, 5);
    g2.insert_edge(5, 3);
    std::cout << "g2:\n";
    g2.display();
    g2.articulation_detection();

    MatrixGraph g3 = MatrixGraph(8, false);
    g3.insert_edge(0, 1);
    g3.insert_edge(0, 2);
    g3.insert_edge(1, 2);
    g3.insert_edge(2, 3);
    g3.insert_edge(2, 4);
    g3.insert_edge(4, 5);
    g3.insert_edge(4, 6);
    g3.insert_edge(4, 7);
    g3.insert_edge(5, 6);
    g3.insert_edge(6, 7);
    std::cout << "g3:\n";
    g3.display();
    g3.articulation_detection();

    MatrixGraph g4 = MatrixGraph(8, false);
    g4.insert_edge(0, 1);
    g4.insert_edge(0, 3);
    g4.insert_edge(0, 6);
    g4.insert_edge(1, 2);
    g4.insert_edge(1, 4);
    g4.insert_edge(1, 5);
    g4.insert_edge(2, 3);
    g4.insert_edge(4, 5);
    g4.insert_edge(4, 7);
    std::cout << "g4:\n";
    g4.display();
    g4.articulation_detection();
}

void test_eulerian() {
    MatrixGraph g1 = MatrixGraph(5, false);
    g1.insert_edge(0, 1);
    g1.insert_edge(0, 2);
    g1.insert_edge(0, 3);
    g1.insert_edge(1, 2);
    g1.insert_edge(1, 3);
    g1.insert_edge(2, 3);
    g1.insert_edge(2, 4);
    g1.insert_edge(3, 4);
    std::cout << "g1:\n";
    g1.display();
    std::cout << "O grafo g1" << (!g1.is_eulerian() ? " não " : " ") << "é euleriano.\n";
    std::cout << "O grafo g1" << (!g1.has_eulerian_trail() ? " não " : " ") << "possui trilha euleriana.\n";
    std::cout << "Algoritmo de Fleury(g1):\n";
    g1.fleury();
    MatrixGraph g2 = MatrixGraph(5, false);
    g2.insert_edge(0, 1);
    g2.insert_edge(0, 2);
    g2.insert_edge(0, 3);
    g2.insert_edge(0, 4);
    g2.insert_edge(1, 2);
    g2.insert_edge(1, 3);
    g2.insert_edge(1, 4);
    g2.insert_edge(2, 3);
    g2.insert_edge(2, 4);
    g2.insert_edge(3, 4);
    g2.insert_edge(4, 0);
    std::cout << "g2:\n";
    g2.display();
    std::cout << "O grafo g2" << (!g2.is_eulerian() ? " não " : " ") << "é euleriano.\n";
    std::cout << "O grafo g2" << (!g2.has_eulerian_trail() ? " não " : " ") << "possui trilha euleriana.\n";
    std::cout << "Algoritmo de Fleury(g2):\n";
    g2.fleury();
    // g1.hierholzer();
    // g1.short_hamiltonian_path();
}

void test_bfs() {
    // Ex 1
    MatrixGraph g1(6);
    g1.insert_edge(0, 2);
    g1.insert_edge(0, 3);
    g1.insert_edge(0, 4);
    g1.insert_edge(1, 2);
    g1.insert_edge(1, 4);
    g1.insert_edge(2, 4);
    g1.insert_edge(3, 4);
    g1.insert_edge(3, 5);
    g1.insert_edge(4, 5);
    g1.insert_edge(5, 1);

    std::cout << "g1:\n";
    g1.display();
    g1.BFS_visit(0);

    // Ex 2
    MatrixGraph g2(8, false);
    g2.insert_edge(0, 2);
    g2.insert_edge(2, 6);
    g2.insert_edge(6, 4);
    g2.insert_edge(4, 5);
    g2.insert_edge(5, 0);
    g2.insert_edge(0, 7);
    g2.insert_edge(7, 1);
    g2.insert_edge(7, 4);
    g2.insert_edge(3, 4);
    g2.insert_edge(3, 5);

    std::cout << "g2:\n";
    g2.display();
    g2.BFS_visit(0);

    // Ex 4
    MatrixGraph g4(8, false);
    g4.insert_edge(0, 1);
    g4.insert_edge(0, 4);
    g4.insert_edge(1, 5);
    g4.insert_edge(2, 3);
    g4.insert_edge(2, 5);
    g4.insert_edge(2, 6);
    g4.insert_edge(3, 6);
    g4.insert_edge(3, 7);
    g4.insert_edge(5, 6);
    g4.insert_edge(6, 7);
    
    std::cout << "g4:\n";
    g4.display();
    g4.BFS_color(1);
    // std::cout << "O grafo g2" << (!g2.is_eulerian() ? " não " : " ") << "é euleriano.\n";
}

void test_djikstra() {
    MatrixGraph g1(5);
    g1.insert_edge(0, 1);
    g1.insert_edge(0, 2);
    g1.insert_edge(1, 2);
    g1.insert_edge(1, 3);
    g1.insert_edge(2, 1);
    g1.insert_edge(2, 3);
    g1.insert_edge(2, 4);
    g1.insert_edge(3, 4);
    g1.insert_edge(4, 3);
    g1.djikstra(0, {
        {0,10, 3, 0, 0},
        {0 ,0, 1, 2, 0},
        {0, 4, 0, 8, 2},
        {0, 0, 0, 0, 7},
        {0, 0, 0, 9, 0}
        });
    // Ex 1
    MatrixGraph g2(8);
    g2.insert_edge(0, 7);
    g2.insert_edge(0, 1);
    g2.insert_edge(1, 2);
    g2.insert_edge(2, 3);
    g2.insert_edge(3, 4);
    g2.insert_edge(4, 5);
    g2.insert_edge(5, 6);
    g2.insert_edge(6, 7);
    g2.djikstra(0, {
        {0, 1, 0, 0, 0, 0, 0, 9},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        });
}

void test_bellman_ford() {
    MatrixGraph g1(5);
    g1.insert_edge(0, 1);
    g1.insert_edge(0, 3);
    g1.insert_edge(1, 2);
    g1.insert_edge(1, 3);
    g1.insert_edge(1, 4);
    g1.insert_edge(2, 1);
    g1.insert_edge(3, 2);
    g1.insert_edge(3, 4);
    g1.insert_edge(4, 0);
    g1.insert_edge(4, 2);
    std::vector<std::vector<int>> p = {
        {0, 6, 0, 7, 0},
        {0, 0, 5, 8,-4},
        {0,-2, 0, 0, 0},
        {0, 0,-3, 0, 9},
        {2, 0, 7, 0, 0}
        };
    
    std::cout << "O grafo g1" << (!g1.bellman_ford(0, p) ? " não " : " ") << "possui um ciclo negativo.\n";

}

int main(int argc, char* argv[]) {
    Logger::set_output_level(Logger::LOG_ERROR);

    get_options(argc, argv);

    // LISTA 1
    // test_source_sink();
    // test_conversion();
    // test_symmetry();
    // LISTA 2
    // test_path();
    // test_has_path();
    // Logger::log(Logger::LOG_INFO, "Testes de tem caminho realizados com sucesso.");
	// test_show_path();
    // Logger::log(Logger::LOG_INFO, "Testes de mostra caminho realizados com sucesso.");
    // test_iterative_DFS();
    // test_arborescence();
    // test_has_arch();
    // LISTA 3
    // test_cicle();
    // LISTA 4
    // test_topologic_sort();
    // LISTA 5
    // test_subgraph();
    // test_components();
    // LISTA 6
    // test_bipartition();
    // LISTA 7
    // test_bridge_detection();
    // test_articulation_detection();
    // LISTA 8
    // test_eulerian();
    // LISTA 9
    // test_bfs();
    // LISTA 10
    // test_djikstra();
    // LISTA 11
    test_bellman_ford();
    return 0;
}