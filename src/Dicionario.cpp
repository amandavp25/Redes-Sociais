#include "Dicionario.hpp"
#include <iostream>

// Construtor  
Dicionario::Dicionario() {
    // Inicia com uma capacidade padrão
    this->capUsuarios = 10;
    this->capTemas = 10;

    this->usuarios = new Usuario*[capUsuarios]();
    this->nosGrafoSocial = new No*[capUsuarios]();
    this->nosUsuariosGrafoTemas = new No*[capUsuarios]();

    this->temas = new Tema*[capTemas]();
    this->nosTemasGrafoTemas = new No*[capTemas]();
    
    // O uso de () no final do 'new' inicializa todos os ponteiros com nullptr automaticamente
}

// Destrutor
Dicionario::~Dicionario() {
    for (int i = 0; i < capUsuarios; i++) {
        if (usuarios[i] != nullptr) delete usuarios[i];
    }
    for (int i = 0; i < capTemas; i++) {
        if (temas[i] != nullptr) delete temas[i];
    }

    // Desaloca os arrays de ponteiros em si
    delete[] usuarios;
    delete[] nosGrafoSocial;
    delete[] nosUsuariosGrafoTemas;
    delete[] temas;
    delete[] nosTemasGrafoTemas;
}

void Dicionario::redimensionarUsuarios(int novaCapacidade) {
    // Cria novos arrays maiores
    Usuario** novosUsuarios = new Usuario*[novaCapacidade]();
    No** novosNosSocial = new No*[novaCapacidade]();
    No** novosNosTemas = new No*[novaCapacidade]();

    // Copia os dados antigos
    for (int i = 0; i < capUsuarios; i++) {
        novosUsuarios[i] = usuarios[i];
        novosNosSocial[i] = nosGrafoSocial[i];
        novosNosTemas[i] = nosUsuariosGrafoTemas[i];
    }

    // Libera a memória dos arrays de ponteiros antigos
    delete[] usuarios;
    delete[] nosGrafoSocial;
    delete[] nosUsuariosGrafoTemas;

    // Aponta para as novas áreas expandidas
    usuarios = novosUsuarios;
    nosGrafoSocial = novosNosSocial;
    nosUsuariosGrafoTemas = novosNosTemas;
    capUsuarios = novaCapacidade;
}

void Dicionario::redimensionarTemas(int novaCapacidade) {
    Tema** novosTemas = new Tema*[novaCapacidade]();
    No** novosNosTemas = new No*[novaCapacidade]();

    for (int i = 0; i < capTemas; i++) {
        novosTemas[i] = temas[i];
        novosNosTemas[i] = nosTemasGrafoTemas[i];
    }

    delete[] temas;
    delete[] nosTemasGrafoTemas;

    temas = novosTemas;
    nosTemasGrafoTemas = novosNosTemas;
    capTemas = novaCapacidade;
}

// REGISTROS

void Dicionario::registrarUsuario(Usuario* u) {
    if (u->getId() >= capUsuarios) {
        redimensionarUsuarios(u->getId() * 2);
    }
    this->usuarios[u->getId()] = u;
}

void Dicionario::registrarTema(Tema* t) {
    if (t->getId() >= capTemas) {
        redimensionarTemas(t->getId() * 2);
    }
    this->temas[t->getId()] = t;
}

void Dicionario::registrarNoGrafoSocial(int idUsuario, No* no) {
    this->nosGrafoSocial[idUsuario] = no;
}

void Dicionario::registrarNoUsuarioGrafoTemas(int idUsuario, No* no) {
    this->nosUsuariosGrafoTemas[idUsuario] = no;
}

void Dicionario::registrarNoTemaGrafoTemas(int idTema, No* no) {
    this->nosTemasGrafoTemas[idTema] = no;
}

// RECUPERAÇÕES

Usuario* Dicionario::recuperarUsuario(int idUsuario) const {
    if (idUsuario >= 0 && idUsuario < capUsuarios) return usuarios[idUsuario];
    return nullptr;
}

Tema* Dicionario::recuperarTema(int idTema) const {
    if (idTema >= 0 && idTema < capTemas) return temas[idTema];
    return nullptr;
}

No* Dicionario::recuperarNoGrafoSocial(int idUsuario) const {
    if (idUsuario >= 0 && idUsuario < capUsuarios) return nosGrafoSocial[idUsuario];
    return nullptr;
}

No* Dicionario::recuperarNoUsuarioGrafoTemas(int idUsuario) const {
    if (idUsuario >= 0 && idUsuario < capUsuarios) return nosUsuariosGrafoTemas[idUsuario];
    return nullptr;
}

No* Dicionario::recuperarNoTemaGrafoTemas(int idTema) const {
    if (idTema >= 0 && idTema < capTemas) return nosTemasGrafoTemas[idTema];
    return nullptr;
}
