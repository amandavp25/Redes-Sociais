#include "Grafo.hpp"
#include <iostream>

// Construtor
Grafo::Grafo(bool ehDirecionado) {
    this->direcionado = ehDirecionado;
    this->modoArmazenamento = 'L'; 
    this->numVertices = 0;
    this->capVertices = 10;        // Capacidade inicial padrão

    // Inicializa as estruturas para o modo Lista
    this->listaAdjacencia = new No*[capVertices]();
    this->mapeamentoVertices = new No*[capVertices]();
    
    // Matriz começa nula porque está em modo Lista
    this->matrizAdjacencia = nullptr;
}

// Destrutor
Grafo::~Grafo() {
    limparLista();
    limparMatriz();
    
    // Limpa as estruturas de nós
    for (int i = 0; i < numVertices; i++) {
        if (mapeamentoVertices[i] != nullptr) {
            delete mapeamentoVertices[i];
        }
    }
    delete[] mapeamentoVertices;
}

// Limpar a memória alocada para a lista de adjacência depois da migração para matriz
void Grafo::limparLista() {
    if (listaAdjacencia != nullptr) {
        for (int i = 0; i < capVertices; i++) {
            No* atual = listaAdjacencia[i];
            while (atual != nullptr) {
                No* aux = atual;
                atual = atual->proximo;
                delete aux; // Deleta as cópias/nós de ligação da lista de vizinhos
            }
        }
        delete[] listaAdjacencia;
        listaAdjacencia = nullptr;
    }
}

// Limpar a memória alocada para a matriz depois da migração para lista de adjacência
void Grafo::limparMatriz() {
    if (matrizAdjacencia != nullptr) {
        for (int i = 0; i < capVertices; i++) {
            if (matrizAdjacencia[i] != nullptr) {
                delete[] matrizAdjacencia[i];
            }
        }
        delete[] matrizAdjacencia;
        matrizAdjacencia = nullptr;
    }
}

void Grafo::redimensionarEstruturas(int novaCapacidade) {
    // Redimensiona o mapeamento de vértices
    No** novoMapeamento = new No*[novaCapacidade]();
    for (int i = 0; i < numVertices; i++) {
        novoMapeamento[i] = mapeamentoVertices[i];
    }
    delete[] mapeamentoVertices;
    mapeamentoVertices = novoMapeamento;

    // Se estiver em modo Lista, redimensiona o array de listas
    if (modoArmazenamento == 'L') {
        No** novaLista = new No*[novaCapacidade]();
        for (int i = 0; i < numVertices; i++) {
            novaLista[i] = listaAdjacencia[i];
        }
        delete[] listaAdjacencia;
        listaAdjacencia = novaLista;
    } 
    // Se estiver em modo Matriz, redimensiona a matriz quadrada NxN
    else if (modoArmazenamento == 'M') {
        int** novaMatriz = new int*[novaCapacidade]();
        for (int i = 0; i < novaCapacidade; i++) {
            novaMatriz[i] = new int[novaCapacidade](); // Inicializa com zeros
        }

        // Copia os dados da matriz anterior
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                novaMatriz[i][j] = matrizAdjacencia[i][j];
            }
            delete[] matrizAdjacencia[i];
        }
        delete[] matrizAdjacencia;
        matrizAdjacencia = novaMatriz;
    }

    capVertices = novaCapacidade;
}

No* Grafo::adicionarVertice(int idLogico, char tipo) {
    if (numVertices >= capVertices) {
        redimensionarEstruturas(capVertices * 2);
    }

    // Cria o nó associando ao índice físico sequencial 'numVertices'
    No* novo = new No(idLogico, tipo, numVertices);
    mapeamentoVertices[numVertices] = novo;
    numVertices++;

    return novo;
}

void Grafo::adicionarAresta(No* u, No* v) {
    if (u == nullptr || v == nullptr) return;

    if (modoArmazenamento == 'L') {
        // Insere na lista de adjacência de 'u' (inserção no início da lista encadeada)
        No* copiaV = new No(v->idLogico, v->tipo, v->idInterno);
        copiaV->proximo = listaAdjacencia[u->idInterno];
        listaAdjacencia[u->idInterno] = copiaV;

        // Se não for direcionado (Grafo de Temas), adiciona a volta v -> u
        if (!direcionado) {
            No* copiaU = new No(u->idLogico, u->tipo, u->idInterno);
            copiaU->proximo = listaAdjacencia[v->idInterno];
            listaAdjacencia[v->idInterno] = copiaU;
        }
    } else {
        // Modo Matriz
        matrizAdjacencia[u->idInterno][v->idInterno] = 1;
        if (!direcionado) {
            matrizAdjacencia[v->idInterno][u->idInterno] = 1;
        }
    }
}

void Grafo::removerAresta(No* u, No* v) {
    if (u == nullptr || v == nullptr) return;

    if (modoArmazenamento == 'L') {
        // Remove da lista de 'u'
        No* atual = listaAdjacencia[u->idInterno];
        No* anterior = nullptr;

        while (atual != nullptr) {
            if (atual->idInterno == v->idInterno) {
                if (anterior == nullptr) {
                    listaAdjacencia[u->idInterno] = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }
                delete atual;
                break;
            }
            anterior = atual;
            atual = atual->proximo;
        }

        // Se não for direcionado, remove a volta v -> u
        if (!direcionado) {
            atual = listaAdjacencia[v->idInterno];
            anterior = nullptr;
            while (atual != nullptr) {
                if (atual->idInterno == u->idInterno) {
                    if (anterior == nullptr) {
                        listaAdjacencia[v->idInterno] = atual->proximo;
                    } else {
                        anterior->proximo = atual->proximo;
                    }
                    delete atual;
                    break;
                }
                anterior = atual;
                atual = atual->proximo;
            }
        }
    } else {
        // Modo Matriz
        matrizAdjacencia[u->idInterno][v->idInterno] = 0;
        if (!direcionado) {
            matrizAdjacencia[v->idInterno][u->idInterno] = 0;
        }
    }
}

bool Grafo::existeAresta(No* u, No* v) const {
    if (u == nullptr || v == nullptr) return false;

    if (modoArmazenamento == 'L') {
        No* atual = listaAdjacencia[u->idInterno];
        while (atual != nullptr) {
            if (atual->idInterno == v->idInterno) return true;
            atual = atual->proximo;
        }
        return false;
    } else {
        return matrizAdjacencia[u->idInterno][v->idInterno] == 1;
    }
}

void Grafo::alternarModo(char novoModo) {
    if (this->modoArmazenamento == novoModo) return;

    if (novoModo == 'M') {
        // Migrando de Lista para Matriz
        this->matrizAdjacencia = new int*[capVertices]();
        for (int i = 0; i < capVertices; i++) {
            this->matrizAdjacencia[i] = new int[capVertices]();
        }

        // Transpõe os dados das listas para a nova matriz
        for (int i = 0; i < numVertices; i++) {
            No* atual = listaAdjacencia[i];
            while (atual != nullptr) {
                matrizAdjacencia[i][atual->idInterno] = 1;
                atual = atual->proximo;
            }
        }

        // Limpa a estrutura antiga de listas
        limparLista();
        this->modoArmazenamento = 'M';

    } else if (novoModo == 'L') {
        // Migrando de Matriz para Lista
        this->listaAdjacencia = new No*[capVertices]();

        // Transpõe os dados da matriz para as novas listas
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (matrizAdjacencia[i][j] == 1) {
                    // Como a matriz já processa bidirecional, adiciona direto
                    No* destino = mapeamentoVertices[j];
                    No* copiaV = new No(destino->idLogico, destino->tipo, destino->idInterno);
                    copiaV->proximo = listaAdjacencia[i];
                    listaAdjacencia[i] = copiaV;
                }
            }
        }

        // Limpa a estrutura antiga de matriz
        limparMatriz();
        this->modoArmazenamento = 'L';
    }
}

char Grafo::getModo() const { return this->modoArmazenamento; }
int Grafo::getNumVertices() const { return this->numVertices; }
No** Grafo::getMapeamentoVertices() const { return this->mapeamentoVertices; }