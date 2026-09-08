#ifndef TEMA_H
#define TEMA_H

#include <string>

class Tema {
private:
    int id;           // Identificador único do tema (0, 1, 2...)
    std::string nome; // Nome do tema
    char tipo;        // 'A' para acadêmico, 'P' para pessoal

public:
    // Construtor padrão
    Tema();

    // Construtor com parâmetros para inicializar o tema no momento do cadastro
    Tema(int id, const std::string& nome, char tipo);

    // Destrutor
    ~Tema();

    // Métodos Getters para acessar os dados encapsulados
    int getId() const;
    std::string getNome() const;
    char getTipo() const;
};

#endif