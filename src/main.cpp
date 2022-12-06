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
    int i = 0;
    std::cout << (mg.has_path(0, 5)? "Existe " : "Não existe ") << "um caminho entre 0 e 5\n";
	std::cout << (mg.has_path(0, 3)? "Existe " : "Não existe ") << "um caminho entre 0 e 3\n";
	std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";
    std::cout << (mg.has_path(1, 2)? "Existe " : "Não existe ") << "um caminho entre 1 e 2\n";

    while (i < 1000000) {
        i++;
        std::cout << i << std::endl;
    }
}

void test_show_path() {
    MatrixGraph mg = MatrixGraph::get_example_graph();
    int i = 0;
    mg.show_path(0, 5);
    while (i < 1000000) {
        i++;
        std::cout << i << std::endl;
    }
	mg.show_path(0, 3);
	mg.show_path(1, 2);
}

            break;
    }
}

    }

    }
    }
    }
}

int main(int argc, char* argv[]) {
    Logger::set_output_level(Logger::LOG_ERROR);

    //   return a > b;
    // };

    // auto fn102 = std::bind(fn,10,2);
    // auto fnnorm = std::bind(fn,_1,_2);
    // auto fninv = std::bind(fn,_2,_1);
    // auto fnjust2 = std::bind(fn,_2,_2);
    // auto fnover = std::bind(fn,_2,_3);
    g4.insert_edge(4, 7);
    std::cout << "g4:\n";
    g4.display();
int main(int argc, char* argv[]) {
    Logger::set_output_level(Logger::LOG_ERROR);

    get_options(argc, argv);

    // test_source_sink();
    // test_symmetry();
    // test_path();
}