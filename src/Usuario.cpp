#include "Usuario.hpp"

// Construtor padrão inicializando tudo zerado ou nulo
Usuario::Usuario() {
    this->id = -1;
    this->nome = "";
    this->idade = -1;
    this->idsTemas = nullptr;
    this->numTemas = 0;
}

// Construtor para ler o comando 'U' do arquivo 
Usuario::Usuario(int id, const std::string& nome, int idade, int* temasEntrada, int qtdTemas) {
    this->id = id;
    this->nome = nome;
    this->idade = idade;
    this->numTemas = qtdTemas;

    if (qtdTemas > 0 && temasEntrada != nullptr) {
        // Alocação dinâmica manual do array para os temas do usuário
        this->idsTemas = new int[qtdTemas];
        for (int i = 0; i < qtdTemas; i++) {
            this->idsTemas[i] = temasEntrada[i];
        }
    } else {
        this->idsTemas = nullptr;
    }
}

// Destrutor
Usuario::~Usuario() {
    if (this->idsTemas != nullptr) {
        delete[] this->idsTemas; // Deleta o array dinâmico de IDs de temas
        this->idsTemas = nullptr;
    }
}

// Retorna o ID único do usuário
int Usuario::getId() const {
    return this->id;
}

// Retorna o nome do usuário
std::string Usuario::getNome() const {
    return this->nome;
}

// Retorna a idade do usuário
int Usuario::getIdade() const {
    return this->idade;
}

// Retorna a quantidade total de temas de interesse do usuário
int Usuario::getNumTemas() const {
    return this->numTemas;
}

// Retorna o ID do tema guardado no índice informado
int Usuario::getTemaIdEm(int indice) const {
    if (indice >= 0 && indice < this->numTemas) {
        return this->idsTemas[indice];
    }
    return -1; // Índice inválido
}