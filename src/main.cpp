#include <iostream>
#include <string>
#include <sstream>

#include "Dicionario.hpp"
#include "Grafo.hpp"
#include "Usuario.hpp"
#include "Tema.hpp"

int main() {
    // Inicializa o Dicionário, o grafo social (direcionado) e o grafo de temas (não direcionado) 
    Dicionario* dic = new Dicionario();
    Grafo* grafoSocial = new Grafo(true);  // Direcionado 
    Grafo* grafoTemas = new Grafo(false);  // Não direcionado

    int proxIdUsuario = 0; 
    int proxIdTema = 0;   

    std::string linha;
    // Lê cada linha da entrada padrão até o fim do arquivo 
    while (std::getline(std::cin, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string comando;
        ss >> comando;

        // ---- COMANDO A: ALTERNAR MODO DE ARMAZENAMENTO ---- 
        if (comando == "A") {
            char modo;
            ss >> modo; 
            
            // Migra os dois grafos para a representação informada ('L' ou 'M') 
            grafoSocial->alternarModo(modo);
            grafoTemas->alternarModo(modo);
            
            std::cout << "A " << modo << std::endl;
        }
        
        // ---- COMANDO T: CADASTRAR TEMA ---- 
        else if (comando == "T") {
            std::string nomeTema;
            char tipoTema;
            ss >> nomeTema >> tipoTema;

            // Criar o objeto Tema e seu nó correspondente no grafo de temas 
            Tema* novoTema = new Tema(proxIdTema, nomeTema, tipoTema);
            No* noTema = grafoTemas->adicionarVertice(proxIdTema, 'T');

            // Registrar o tema e o nó no Dicionário 
            dic->registrarTema(novoTema);
            dic->registrarNoTemaGrafoTemas(proxIdTema, noTema);

            std::cout << "T " << proxIdTema << std::endl;
            proxIdTema++; 
        }
        
        // ---- COMANDO U: CADASTRAR USUÁRIO ---- 
        else if (comando == "U") {
            std::string nomeUsuario;
            int idadeUsuario;
            ss >> nomeUsuario >> idadeUsuario; 

            // Lê a lista de IDs de temas associados ao usuário que estão no resto da linha 
            int temasTemporarios[1000]; // Array estático temporário para leitura
            int qtdTemas = 0;
            int idTemaLido;
            while (ss >> idTemaLido) {
                temasTemporarios[qtdTemas] = idTemaLido;
                qtdTemas++;
            }

            // Criar o objeto Usuário passando a lista de temas 
            Usuario* novoUsuario = new Usuario(proxIdUsuario, nomeUsuario, idadeUsuario, temasTemporarios, qtdTemas);
            
            // Criar seus nós nos dois grafos (Social e Temas) 
            No* noSocial = grafoSocial->adicionarVertice(proxIdUsuario, 'U');
            No* noTemasU = grafoTemas->adicionarVertice(proxIdUsuario, 'U');

            // Registrar o usuário e seus nós no Dicionário 
            dic->registrarUsuario(novoUsuario);
            dic->registrarNoGrafoSocial(proxIdUsuario, noSocial);
            dic->registrarNoUsuarioGrafoTemas(proxIdUsuario, noTemasU);

            // Inserir, no grafo de temas, as arestas entre o usuário e seus temas de interesse 
            for (int i = 0; i < qtdTemas; i++) {
                No* noTemaAlvo = dic->recuperarNoTemaGrafoTemas(temasTemporarios[i]);
                grafoTemas->adicionarAresta(noTemasU, noTemaAlvo);
            }

            std::cout << "U " << proxIdUsuario << std::endl; 
            proxIdUsuario++; 
        }
        
        // ---- COMANDO S: SEGUIR USUÁRIO ---- 
        else if (comando == "S") {
            int id1, id2;
            ss >> id1 >> id2; 

            Usuario* u1 = dic->recuperarUsuario(id1);
            Usuario* u2 = dic->recuperarUsuario(id2);
            No* noU1 = dic->recuperarNoGrafoSocial(id1);
            No* noU2 = dic->recuperarNoGrafoSocial(id2); 

            grafoSocial->adicionarAresta(noU1, noU2); 
            std::cout << "S " << u1->getNome() << " " << u2->getNome() << std::endl; 
        }
        
        // ---- COMANDO R: REMOVER SEGUIMENTO ---- 
        else if (comando == "R") {
            int id1, id2;
            ss >> id1 >> id2; 

            Usuario* u1 = dic->recuperarUsuario(id1);
            Usuario* u2 = dic->recuperarUsuario(id2);
            No* noU1 = dic->recuperarNoGrafoSocial(id1);
            No* noU2 = dic->recuperarNoGrafoSocial(id2); 

            grafoSocial->removerAresta(noU1, noU2); 
            std::cout << "R " << u1->getNome() << " " << u2->getNome() << std::endl;
        }
        
        // ---- CONSULTA LT: LISTAR TEMAS DO USUÁRIO ----
        else if (comando == "LT") {
            int idUser;
            ss >> idUser; 
            Usuario* u = dic->recuperarUsuario(idUser);
            std::cout << "LT " << u->getNome();
            
            for (int i = 0; i < u->getNumTemas(); i++) {
                int idT = u->getTemaIdEm(i);
                Tema* t = dic->recuperarTema(idT);
                std::cout << " " << t->getNome(); 
            }
            std::cout << std::endl;
        }
        
        // ---- CONSULTA LC: LISTAR SEGUIDORES ----
        else if (comando == "LC") {
            int idUser;
            ss >> idUser;
            Usuario* u = dic->recuperarUsuario(idUser);
            No* noU = dic->recuperarNoGrafoSocial(idUser);

            std::cout << "LC " << u->getNome();
            
            int totalVertices = grafoSocial->getNumVertices();
            No** mapeamento = grafoSocial->getMapeamentoVertices();
            for (int i = 0; i < totalVertices; i++) {
                No* potencialSeguidor = mapeamento[i];
                if (potencialSeguidor->tipo == 'U' && potencialSeguidor->idLogico != idUser) {
                    // Se 'i' segue 'u', então 'i' é um seguidor
                    if (grafoSocial->existeAresta(potencialSeguidor, noU)) {
                        Usuario* seguidor = dic->recuperarUsuario(potencialSeguidor->idLogico);
                        std::cout << " " << seguidor->getNome(); 
                    }
                }
            }
            std::cout << std::endl;
        }
        
        // ---- CONSULTA LS: LISTAR SEGUIDOS ----
        else if (comando == "LS") {
            int idUser;
            ss >> idUser; 
            Usuario* u = dic->recuperarUsuario(idUser);
            No* noU = dic->recuperarNoGrafoSocial(idUser);

            std::cout << "LS " << u->getNome(); 
            
            int totalVertices = grafoSocial->getNumVertices();
            No** mapeamento = grafoSocial->getMapeamentoVertices();
            for (int i = 0; i < totalVertices; i++) {
                No* potencialSeguido = mapeamento[i];
                if (potencialSeguido->tipo == 'U' && potencialSeguido->idLogico != idUser) {
                    // Se 'u' segue 'i', então 'i' é seguido por u
                    if (grafoSocial->existeAresta(noU, potencialSeguido)) {
                        Usuario* seguido = dic->recuperarUsuario(potencialSeguido->idLogico);
                        std::cout << " " << seguido->getNome(); 
                    }
                }
            }
            std::cout << std::endl;
        }
        
        // ---- CONSULTA LA: LISTAR AMIGOS (MUTUO) ----
        else if (comando == "LA") {
            int idUser;
            ss >> idUser; 
            Usuario* u = dic->recuperarUsuario(idUser);
            No* noU = dic->recuperarNoGrafoSocial(idUser);

            std::cout << "LA " << u->getNome(); 
            
            int totalVertices = grafoSocial->getNumVertices();
            No** mapeamento = grafoSocial->getMapeamentoVertices();
            for (int i = 0; i < totalVertices; i++) {
                No* potencialAmigo = mapeamento[i];
                if (potencialAmigo->tipo == 'U' && potencialAmigo->idLogico != idUser) {
                    // Amigo mútua: u segue i E i segue u 
                    if (grafoSocial->existeAresta(noU, potencialAmigo) && grafoSocial->existeAresta(potencialAmigo, noU)) {
                        Usuario* amigo = dic->recuperarUsuario(potencialAmigo->idLogico);
                        std::cout << " " << amigo->getNome(); 
                    }
                }
            }
            std::cout << std::endl;
        }
        
        // ---- CONSULTA Q: CONSULTAR RELAÇÃO ----
        else if (comando == "Q") {
            int id1, id2;
            ss >> id1 >> id2; 
            Usuario* u1 = dic->recuperarUsuario(id1);
            Usuario* u2 = dic->recuperarUsuario(id2);
            No* noU1 = dic->recuperarNoGrafoSocial(id1);
            No* noU2 = dic->recuperarNoGrafoSocial(id2);

            bool u1_segue_u2 = grafoSocial->existeAresta(noU1, noU2);
            bool u2_segue_u1 = grafoSocial->existeAresta(noU2, noU1);

            int valorRelacao = 0; 
            if (u1_segue_u2 && u2_segue_u1) valorRelacao = 3;      // Mútua 
            else if (!u1_segue_u2 && u2_segue_u1) valorRelacao = 2; // id2 segue id1 
            else if (u1_segue_u2 && !u2_segue_u1) valorRelacao = 1; // id1 segue id2 

            std::cout << "Q " << u1->getNome() << " " << u2->getNome() << " " << valorRelacao << std::endl; 
        }
        
        // ---- CONSULTA G: CONSULTA INTERESSE ----
        else if (comando == "G") {
            int idUser, idTema;
            ss >> idUser >> idTema; 
            Usuario* u = dic->recuperarUsuario(idUser);
            Tema* t = dic->recuperarTema(idTema);
            No* noU = dic->recuperarNoUsuarioGrafoTemas(idUser);
            No* noT = dic->recuperarNoTemaGrafoTemas(idTema);

            int temInteresse = grafoTemas->existeAresta(noU, noT) ? 1 : 0; 
            std::cout << "G " << u->getNome() << " " << t->getNome() << " " << temInteresse << std::endl; 
        }
        
        // ---- CONSULTA F: POPULARIDADE DO TEMA ----
        else if (comando == "F") {
            int idTema;
            ss >> idTema; 
            Tema* t = dic->recuperarTema(idTema);
            No* noT = dic->recuperarNoTemaGrafoTemas(idTema);

            int popularidade = 0; 
            int totalVertices = grafoTemas->getNumVertices();
            No** mapeamento = grafoTemas->getMapeamentoVertices();
            
            // Varre o grafo de temas contando quantos usuários estão conectados a esse nó de tema 
            for (int i = 0; i < totalVertices; i++) {
                No* noAtual = mapeamento[i];
                if (noAtual->tipo == 'U') {
                    if (grafoTemas->existeAresta(noAtual, noT)) {
                        popularidade++;
                    }
                }
            }
            std::cout << "F " << t->getNome() << " " << popularidade << std::endl; 
        }
    }

    // Liberação de memória centralizada
    delete grafoSocial;
    delete grafoTemas;
    delete dic; // O dicionário deleta todos os usuários e temas criados por cascata

    return 0;
}