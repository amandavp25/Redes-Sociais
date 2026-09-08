
CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

CFLAGS = -Wall -g -std=c++11 -I$(INC)


EXE = $(BIN)/tp2.out


OBJS = $(OBJ)/Tema.o $(OBJ)/Usuario.o $(OBJ)/Dicionario.o $(OBJ)/Grafo.o $(OBJ)/main.o

all: directories $(EXE)


directories:
	@mkdir -p $(OBJ) $(BIN)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/Tema.o: $(SRC)/Tema.cpp $(INC)/Tema.hpp
	$(CC) $(CFLAGS) -c $(SRC)/Tema.cpp -o $(OBJ)/Tema.o

$(OBJ)/Usuario.o: $(SRC)/Usuario.cpp $(INC)/Usuario.hpp
	$(CC) $(CFLAGS) -c $(SRC)/Usuario.cpp -o $(OBJ)/Usuario.o

$(OBJ)/Dicionario.o: $(SRC)/Dicionario.cpp $(INC)/Dicionario.hpp
	$(CC) $(CFLAGS) -c $(SRC)/Dicionario.cpp -o $(OBJ)/Dicionario.o

$(OBJ)/Grafo.o: $(SRC)/Grafo.cpp $(INC)/Grafo.hpp
	$(CC) $(CFLAGS) -c $(SRC)/Grafo.cpp -o $(OBJ)/Grafo.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/Usuario.hpp $(INC)/Tema.hpp $(INC)/Dicionario.hpp $(INC)/Grafo.hpp
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

clean:
	rm -f $(OBJ)/*.o $(EXE)