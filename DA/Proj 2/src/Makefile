CXX = g++
DEV_FLAGS = -fsanitize=address -fsanitize=undefined -O
RELEASE_FLAGS = -O3
CXXFLAGS = -std=c++14 -pedantic -Wall -Wuninitialized -Werror -Wextra -lm $(RELEASE_FLAGS)
OBJ = ../obj
LIB = ../lib

all: objects $(OBJ)/main.o main
	@echo "Finishing...\n"

objects: $(OBJ)/Auxil.o $(OBJ)/Edge.o $(OBJ)/Graph.o $(OBJ)/Parser.o  $(OBJ)/Vertex.o $(OBJ)/Runtime.o

O_FILES = $(OBJ)/Auxil.o $(OBJ)/Edge.o $(OBJ)/Graph.o $(OBJ)/Parser.o $(OBJ)/Vertex.o $(OBJ)/Runtime.o
HPP_FILES = $(wildcard $(LIB)/*.hpp)
CPP_FILES = $(wildcard *.cpp)

main: $(OBJ)/main.o $(O_FILES)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)/main.o $(O_FILES)

$(OBJ)/main.o: main.cpp $(HPP_FILES) $(CPP_FILES)
	$(CXX) -c $(CXXFLAGS) main.cpp -o $(OBJ)/main.o

$(OBJ)/Auxil.o: Auxil.cpp $(LIB)/Auxil.hpp Graph.cpp $(LIB)/Graph.hpp
	$(CXX) -c $(CXXFLAGS) Auxil.cpp -o $(OBJ)/Auxil.o

$(OBJ)/Edge.o: Edge.cpp $(LIB)/Edge.hpp Vertex.cpp $(LIB)/Vertex.hpp
	$(CXX) -c $(CXXFLAGS) Edge.cpp -o $(OBJ)/Edge.o

$(OBJ)/Graph.o: Graph.cpp $(LIB)/Graph.hpp Vertex.cpp $(LIB)/Vertex.hpp
	$(CXX) -c $(CXXFLAGS) Graph.cpp -o $(OBJ)/Graph.o

$(OBJ)/Parser.o: Parser.cpp $(LIB)/Parser.hpp Graph.cpp $(LIB)/Graph.hpp
	$(CXX) -c $(CXXFLAGS) Parser.cpp -o $(OBJ)/Parser.o

$(OBJ)/Vertex.o: Vertex.cpp $(LIB)/Vertex.hpp Edge.cpp $(LIB)/Edge.hpp
	$(CXX) -c $(CXXFLAGS) Vertex.cpp -o $(OBJ)/Vertex.o

$(OBJ)/Runtime.o: Runtime.cpp $(LIB)/Runtime.hpp $(LIB)/Graph.hpp $(LIB)/Vertex.hpp $(LIB)/Edge.hpp
	$(CXX) -c $(CXXFLAGS) Runtime.cpp -o $(OBJ)/Runtime.o
