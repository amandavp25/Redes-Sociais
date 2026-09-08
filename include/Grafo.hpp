#ifndef GRAFO_H
#define GRAFO_H

#include <string>

// Estrutura do Nó (identifica se o vértice representa um usuário ou tema)
struct No {
    int idLogico;     // ID que vem da entrada 
    char tipo;        // 'U' para Usuário, 'T' para Tema
    int idInterno;    // Índice físico sequencial atribuído a este nó no grafo (0, 1, 2...)
    No* proximo;      // Ponteiro para o próximo nó (usado na lista de adjacência)

    No(int idLog, char t, int idInt) {
        idLogico = idLog;
        tipo = t;
        idInterno = idInt;
        proximo = nullptr;
    }
};

class Grafo {
private:
    bool direcionado;         // True se for o Grafo Social, False se for o de Temas
    char modoArmazenamento;   // 'L' para Lista de Adjacência, 'M' para Matriz de Adjacência
    
    int numVertices;          // Quantidade atual de vértices no grafo
    int capVertices;          // Capacidade alocada para os arrays de vértices

    // REPRESENTAÇÃO 1: LISTA DE ADJACÊNCIA
    // Array de ponteiros para as listas encadeadas de vizinhos
    No** listaAdjacencia;

    // REPRESENTAÇÃO 2: MATRIZ DE ADJACÊNCIA
    // Matriz bidimensional alocada dinamicamente (0 para sem aresta, 1 para com aresta)
    int** matrizAdjacencia;

    // Array para mapear do 'idInterno' de volta para o ponteiro do 'No' original
    No** mapeamentoVertices;

    // Métodos privados auxiliares de redimensionamento interno
    void redimensionarEstruturas(int novaCapacidade);
    void limparLista();
    void limparMatriz();

public:
    Grafo(bool ehDirecionado);
    ~Grafo();

    // Adiciona um vértice ao grafo e retorna o ponteiro para o Nó criado
    No* adicionarVertice(int idLogico, char tipo);

    // Insere uma aresta no grafo respeitando a direção e o modo de armazenamento atual
    void adicionarAresta(No* u, No* v);

    // Remove uma aresta do grafo (usado no comando R)
    void removerAresta(No* u, No* v);

    // Altera a representação interna (Comando A) sem perder dados lógicos
    void alternarModo(char novoModo);

    // Getters de suporte
    char getModo() const;
    int getNumVertices() const;
    No** getMapeamentoVertices() const;
    
    // Métodos para auxiliar nas consultas (retornam se existe a aresta u -> v)
    bool existeAresta(No* u, No* v) const;
};

#endif 