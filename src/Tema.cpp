#include "Tema.hpp"

// Construtor padrão inicializando com valores nulos/padrão
Tema::Tema() {
    this->id = -1;
    this->nome = "";
    this->tipo = '\0';
}

// Construtor para ler o comando 'T' do arquivo
Tema::Tema(int id, const std::string& nome, char tipo) {
    this->id = id;
    this->nome = nome;
    this->tipo = tipo;
}

// Destrutor (vazio pois não há alocação dinâmica de memória)
Tema::~Tema() {}

// Retorna o ID único do tema
int Tema::getId() const {
    return this->id;
}

// Retorna o nome do tema
std::string Tema::getNome() const {
    return this->nome;
}

// Retorna o tipo do tema ('A' ou 'P')
char Tema::getTipo() const {
    return this->tipo;
}