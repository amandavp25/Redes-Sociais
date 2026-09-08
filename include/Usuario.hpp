#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    int id;               // Identificador único do usuário (0, 1, 2...)
    std::string nome;     // Nome do usuário 
    int idade;            // Idade do usuário
    int* idsTemas;        // Array dinâmico para guardar os IDs dos temas de interesse 
    int numTemas;         // Quantidade de temas que o usuário possui 

public:
    // Construtor padrão
    Usuario();

    // Construtor completo usado no cadastro (Comando 'U') 
    Usuario(int id, const std::string& nome, int idade, int* temasEntrada, int qtdTemas);

    // Destrutor
    ~Usuario();

    // Métodos Getters
    int getId() const;
    std::string getNome() const;
    int getIdade() const;
    int getNumTemas() const;
    
    // Retorna o ID do tema em uma posição específica do array
    int getTemaIdEm(int indice) const;
};

#endif 
