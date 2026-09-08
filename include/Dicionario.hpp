#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "Usuario.hpp"
#include "Tema.hpp"

struct No; 

class Dicionario {
private:
    // Arrays dinâmicos para mapear ID -> Objeto/Nó
    Usuario** usuarios;
    Tema** temas;
    No** nosGrafoSocial;
    No** nosUsuariosGrafoTemas;
    No** nosTemasGrafoTemas;

    // Controle de capacidade atual alocada para os arrays
    int capUsuarios;
    int capTemas;

    // Métodos auxiliares privados para redimensionar os arrays quando necessário
    void redimensionarUsuarios(int novaCapacidade);
    void redimensionarTemas(int novaCapacidade);

public:
    Dicionario();
    ~Dicionario();

    // Métodos de registro (Inserção)
    void registrarUsuario(Usuario* u);
    void registrarTema(Tema* t);
    void registrarNoGrafoSocial(int idUsuario, No* no);
    void registrarNoUsuarioGrafoTemas(int idUsuario, No* no);
    void registrarNoTemaGrafoTemas(int idTema, No* no);

    // Métodos de recuperação (Busca)
    Usuario* recuperarUsuario(int idUsuario) const;
    Tema* recuperarTema(int idTema) const;
    No* recuperarNoGrafoSocial(int idUsuario) const;
    No* recuperarNoUsuarioGrafoTemas(int idUsuario) const;
    No* recuperarNoTemaGrafoTemas(int idTema) const;
};

#endif 