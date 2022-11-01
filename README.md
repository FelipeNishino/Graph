# Teoria de Grafos

Implementação de uma estrutura de grafos em c++.

### Listas de exercícios:
- [Lista 1](#lista-1)
- [Lista 2](#lista-2)
- [Lista 3](#lista-3)
- [Lista 4](#lista-4)
- [Lista 5](#lista-5)
- [Lista 6](#lista-6)
- [Lista 7](#lista-7)
- [Lista 8](#lista-8)
- [Lista 9](#lista-9)
- [Lista 10](#lista-10)

## Lista 1

1. Construa uma classe Digrafo para representar o grafo orientado utilizando a matriz de adjacência.

2. Em quais momentos é mais vantajoso utilizar uma matriz de
adjacência em relação uma lista de adjacência?

3. Escreva um método grau entrada() que calcula o grau de
entrada de um vértice v de um digrafo. Escreva também a função
grau saida() que calcula o grau de saída de v no digrafo. As
funções devem ser implementadas na classe Digrafo que utiliza
uma matriz de adjacência

4. Escreva uma função que decida se dois grafos são iguais.
A função deve ser implementada para classe Grafo que utiliza
matriz e listas de adjacência.

5. Escreva uma função que converta uma representação de grafo
em outra, por exemplo, converta um grafo armazenado em uma
matriz de adjacência em uma lista de adjacência.

6. Escreva uma função que recebe um digrafo armazenado em
listas de adjacência e inverta as listas de todos os vértices do
grafo. Por exemplo, se os 4 vizinhos de um certo vértice u
aparecem na lista adj[u] na ordem v, w, x, y, então depois da
aplicação da função a lista deve conter os mesmos vértices na
ordem y, x, w e v.

7. Um grafo pode ser armazenado em um arquivo, onde na primeira linha contém um inteiro V (vértice), na segunda contém um inteiro A (arestas) e nas demais linha contém dois inteiros pertencentes ao intervalo 0 . . V − 1. Se  nterpretarmos cada linha do arquivo como uma aresta, podemos dizer que o arquivo define um grafo com vértices 0 . . V − 1. Escreva uma função que receba um nome de arquivo com o formato acima e construa uma representação (matriz e listas de adjacência) do grafo. Abaixo encontra-se um exemplo do formato do arquivo.
    ```
    6
    8
    0 1
    0 5
    1 0
    1 5
    2 4
    3 1
    4 3
    3 5
    ```


8. Escreva uma função que receba um dígrafo e um vértice
como parâmetro e retorne 1 se vértice for uma fonte (grau de
saída maior que zero e grau de entrada igual a 0), ou 0 caso
contrário. A função deve ser implementada para a classe Grafo
que utilizam matriz e listas de adjacência.

9. Escreva uma função que receba um dígrafo e um vértice
como parâmetro, retorne 1 se vértice for uma sorvedouro (grau
de entrada maior que zero e grau de saída igual a 0), ou 0 caso
contrário. A função deve ser implementada para a classe Grafo
que utiliza matriz e listas de adjacência.

10. Escreva uma função que retorna 1 se o dígrafo for simétrico
e 0 caso contrário. Um dígrafo é simétrico se cada uma das
arestas é anti-paralela a outra. A função deve ser implementada
para classe Grafo que utilizam matriz e listas de adjacência.
Exemplo: o grafo G = (V, E), com V = {1, 2, 3} e arestas E =
{(1, 2), (2, 1), (1, 3), (3, 1), (2, 3), (3, 2), } é um dígrafo simétrico.

## Lista 2

1. Escreva uma função que verifique se uma dada sequência seq[0..k] de vértices de um grafo é um **caminho**. A função devolve 1 caso a sequencia seja um caminho e 0 caso contrário. Faça duas versões do método:supõe que o grafo dado por sua matriz de adjacência e outra supõe que o grafo é dado por listas de adjacência.

2. Escreva uma função que verifique se uma dada sequência seq[0..k] de vértices de um grafo é um **caminho simples**. A função devolve 1 caso a sequencia seja um caminho e 0 caso contrário. Faça duas versões do método:supõe que o grafo dado por sua matriz de adjacência e outra supõe que o grafo é dado por listas de adjacência.

- Implemente uma função de DFS genérica para a estrutura de grafos implementada.

3. Dados vértices s e t de um grafo G, escreva uma função que retorna 1 se existe um caminho ou 0 se não existe um caminho de s a t em G. Faça duas versões: uma supõe que o grafo é dado por sua **matriz de adjacência** e outra supõe que o grafo é dado por **listas de adjacência**.

4. Dados vértices s e t de um grafo G, escreva uma função que encontra e exibe (caso exista) um caminho de s a t. Faça duas versões da função: uma supõe que o grafo é dado por sua **matriz de adjacência** e outra supõe que o grafo é dado por **listas de adjacência**.

5. Escreva uma **versão iterativa** para a busca em profundidade para grafos representados por uma matriz de adjacência e por uma listas de adjacência. Dica utilize uma pilha como estrutura auxiliar.

- Implemente uma função de DFS que trabalhe com os conceitos de arborescência e tempo para a estrutura de grafos implementada.

6. Escreva um método receba dois vértices v e w em V (G), e verifique se existe um arco v − w em G. Caso positivo devolva a classificação do arco (arborescência, descendente, retorno ou cruzado).

## Lista 3

- Escreva um método que verifica se um dado digrafo contém um ciclo. O método devolve 1 se existe um ciclo e devolve 0 em caso contrário.
    -  Implemente a detecção do ciclo utilizando a função de caminho.
    - Escreva o algoritmo recursivo e o algoritmo iterativo. Implemente a detecção do ciclo utilizando pilhas.
    - Implemente a detecção do ciclo utilizando classificação de arcos.
    - Implemente a detecção do ciclo utilizando cores.

## Lista 4

- Implemente o algoritmo de ordenação topológica utilizando busca em profundidade.

## Lista 5

1. Tendo em mente o conceito de subgrafo, faça:
    - Apresente o subgrafo G′ 1 de G induzido por 
        ```
        V′ = {a, b, c, d, e, f }
        ```

    - Apresente o subgrafo G′ 2 de G aresta-induzido por 
        ```
        E′ = {(a, g), (b, g), (c, g), (d, g), (e, g), (f, g)}
        ```

2. Dado um grafo não orientado G = (V, E), escreva um método que receba um grafo G1 = (V, E) e devolva verdadeiro se G1 ⊆ G, e falso caso contrário.

3. Dado um grafo não orientado G = (V, E), escreva um método que receba um grafo G1 = (V, E) e devolva verdadeiro se G1 é um subgrafo gerador de G, e falso caso contrário.

4. Dado um grafo não orientado G = (V, E), escreva um método que receba um conjunto de vértices V ′ ∈ V e devolva um grafo induzido por V ′. Caso não seja possível gerar o grafo induzido, apresente uma mensagem de erro.

5. Dado um grafo G não orientado, construa um método que devolve o número de componentes de G.

6. Dado um grafo não orientado, utilize o método que devolve o número de componentes do grafo construído no exercício anterior para construir um outro método que devolva verdadeiro se o grafo é conexo e falso caso o grafo seja desconexo

7. Dado um digrafo D = (V, E), escreva um programa que determine os componentes fortemente conexos utilizando o algoritmo de Kosaraju. Exemplos:
    ```
    D′ = {(0, 1), (1, 2), (1, 4), (2, 5), (3, 0), (4, 3), (4, 5), (5, 2), (6, 3), (6, 4), (6, 5)}
    ```
    ```
    D′ = {(0, 1), (1, 4), (1, 6), (2, 0), (2, 3), (3, 5), (4, 7), (5, 4), (6, 2), (6, 7), (7, 3)}
    ```

## Lista 6

1. Escreva um programa que verifique se o grafo é bipartido,
caso seja bipartido, apresente quais são os vértices que da cor azul e quais vértices da cor vermelho.

2. Dada a matriz de adjacência a seguir, determine se o grafo é bipartido.
    ```
    Entrada:
    Matriz de adjacência
    0 1 1 1 0 0
    1 0 0 1 1 0
    1 0 0 1 0 1
    1 1 1 0 1 1
    0 1 0 1 0 1
    0 0 1 1 1 0
    ```

3. Em uma rede social, dado um conjunto de n pessoas (numeradas de 0, 1, ... n−1), gostaríamos de dividir em dois grupos de tamanho arbitrário.

    Cada pessoa pode enviar um dislike para alguma outra pessoa, quando isso ocorre, elas devem ser separadas em dois grupos distintos (digamos o grupo da esquerda e o grupo da direita).

    Formalmente, se o dislikes[i] = (a,b), significa que as pessoas numerada por a e b devem ser colocadas em grupos diferentes. 

    Devolva True se somente se for possível dividir todos em dois grupos, e False caso contrário.

    ```
    # Exemplo 1:
    Entrada: n = 4, dislikes = [(0,1), (0,2), (1,3)]
    Saída: True
    Explicação: esquerda (0,3), direita (1,2)
    # Exemplo 2:
    Entrada: n = 4, dislikes = [(0,1), (0,2), (1,2)]
    Saída: False
    # Exemplo 3:
    Entrada: n = 5, dislikes = [(0,1), (1,2), (2,3), (3,4), (4,0)]
    Saída: False
    ```

## Lista 7

1. Escreva um programa que mostre todas as pontes do grafo
usando a abordagem ingênua.

2. Mostre a numeração pre-ordem e o valor low para cada vértice dos grafos abaixo:
    ```
    G′ = {(a, b), (a, c), (b, c), (c, d), (c, e), (e, f), (e, h), (f, g), (g, h)}
    ```
    ```
    G′ = {(a, b), (b, c), (c, d), (c, e), (e, f), (f, g), (g, h)}
    ```
    ```
    G′ = {(a, b), (a, d), (b, c), (b, h), (c, d), (c, e), (e, f), (f, g), (g, h)}
    ```

3. Escreva um programa que mostre todas as pontes do grafo
usando o algorítmo de detecção de pontes.

4. Escreva um programa que mostre todos os pontos de articulação do grafo usando a abordagem ingênua.

5. Mostre a numeração pre-ordem e o valor low para cada vértice dos grafos abaixo:
    ```
    G′ = {(a, b), (a, c), (b, c), (c, d), (c, e), (e, f), (e, g), (e, h), (f, g), (g, h)}
    ```
    ```
    G′ = {(a, b), (a, d), (a, g), (b, c), (b, e), (b, f), (c, d), (e, f), (e, h)}
    ```

6. Escreva um programa que mostre todos os pontos de articulação do grafo usando o algorítmo de detecção de articulações.

## Lista 8

1. Considere um grafo não-dirigido conexo G, escreva um método que devolva True caso G for euleriano e False caso contrário. Faça duas versões da função: uma utilizando matriz de adjacências e outra utilizando listas de adjacências.

2. Seja G um grafo não-dirigido conexo. Escreva um método que devolva True se G tem uma trilha euleriana e False caso contrário. Faça duas versões da função: uma utilizando matriz de adjacências e outra utilizando listas de adjacências

3. Observe a seguinte planta de uma casa, modele a planta da
casa utilizando um grafo não-dirigido, em seguida responda as
questões abaixo:
    - É possível uma pessoa a partir do cômodo A chegar ao cômodo B e passar por todas as portas exatamente uma única vez? Existe alguma teoria que caracteriza esse problema? Se for possível apresente a solução
    ```
    G′ = {{a, b}, {a, g}, {b, c}, {c, d}, {d, j}, {e, f}, {e, h}, {e, i}, {e, k}, {f, h}, {g, h}, {h, i}, {j, k}}
    ```

4. Seja um jogo de dominós que contém 10 peças, cujas configurações são as seguintes: (1,2); (1,3); (1,4); (1,5); (2,3); (2,4); (2,5); (3,4); (3,5); (4,5). É possível dispor todas as peça de tal maneira que dado uma peça com um número ela toque uma outra peça com o mesmo número, tendo assim um jogo completo de dominós? Existe alguma teoria que caracteriza esse problema? Explique.
    ```
    G′ = {(1, 2), (1, 3), (1, 4), (1, 5), (2, 3), (2, 5), (2, 6), (3, 4), (3, 5), (4, 5)}
    ```

5. Escreva um método que receba um grafo não-dirigido conexo e mostre uma trilha euleriana, caso seja possível. Neste exercício utilize o algoritmo de Fleury.

6. Escreva um método que receba um grafo não-dirigido conexo e mostre uma trilha euleriana, caso seja possível. Neste exercício utilize o algoritmo de Hierholzer.

7. Dado o grafo G = (V, E), escreva um programa que encontra,
se houver, o menor circuito Hamiltoniano.
    ```
    G′ = {{(a, b), 2}, {(a, c), 8}, {(a, d), 5}, {(b, c), 3}, {(b, d), 4}, {(c, d), 7}}
    ```

## Lista 9

- Implemente uma função de BFS genérica para a estrutura de grafos implementada.

1. Represente o digrafo D a seguir em uma matriz de adjacência e faça uma busca em largura a partir do vértice 0. Apresente a ordem em que os vértices são visitados.
    ```
    D = {(0, 2), (0, 3), (0, 4), (1, 2), (1, 4), (2, 4), (3, 4), (3, 5), (4, 5), (5, 1)}
    ```

2. Represente o grafo G a seguir em uma matriz de adjacência e faça uma busca em largura a partir do vértice 0. Apresente a ordem em que os vértices são visitados
    ```
    G = {(0, 2), (2, 6), (6, 4), (4, 5), (5, 0), (0, 7), (7, 1), (7, 4), (3, 4), (3, 5)}
    ```

3. Dado um grafo G, escreva uma função que recebe um vértice
origem e retorna um vetor com o caminho de comprimento mínimo, desde o vértice origem para todos os outros vértices, caso não exista caminho entre o vértice origem e um vértice no grafo na posição desse vértice no vetor distância tem o valor -1, e é claro, o caminho do vértice origem para ele mesmo é o valor do próprio vértice. Faça duas versões da função: uma supõe que o grafo é representado por uma matriz de adjacência e outra supõe que o grafo é representado por listas de adjacência.

4. Implemente o algoritmo de Busca em profundidade (BFS)
utilizando cores

## Lista 10

1. Considere o grafo dirigido com custos nas arestas definido a seguir. Encontre um caminho de custo mínimo de 0 a 7.
    ```
    G′ = {{(0, 7), 9}, {(0, 1), 1}, {(1, 2), 1}, {(2, 3), 1},{(3, 4), 1}, {(4, 5), 1}, {(5, 6), 1}, {(6, 7), 1}}
    ```

2. Escreva uma função que dado um grafo dirigido com custos positivos associados aos vértices (e não às arestas) encontra um caminho de custo mínimo entre o vértice s até o vértice t. O custo de um caminho num tal grafo é a soma dos pesos dos vértices do caminho. Adapte o algoritmo de Dijkstra para resolver esse problema. Faça duas versões da função: uma supõe que o grafo é representado por uma matriz de adjacência e outra supõe que o grafo é representado por listas de adjacência.

- Implemente o Algoritmo de Djikstra com fila de prioridades.