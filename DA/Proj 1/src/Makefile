CXX = g++
CXXFLAGS = -std=c++14 -pedantic -Wall -Wuninitialized -Werror -Wextra -lm -fsanitize=address -fsanitize=undefined -O
OBJ = ../obj
LIB = ../lib

all: objects $(OBJ)/main.o main
	@echo "Finishing...\n"

objects: $(OBJ)/Edge.o $(OBJ)/Graph.o $(OBJ)/Parser.o $(OBJ)/Tests.o $(OBJ)/Vertex.o $(OBJ)/Runtime.o

O_FILES = $(OBJ)/Edge.o $(OBJ)/Graph.o $(OBJ)/Parser.o $(OBJ)/Tests.o $(OBJ)/Vertex.o $(OBJ)/Runtime.o
HPP_FILES = $(wildcard $(LIB)/*.hpp)
CPP_FILES = $(wildcard *.cpp)

main: $(OBJ)/main.o $(O_FILES)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)/main.o $(O_FILES)

$(OBJ)/main.o: main.cpp $(HPP_FILES) $(CPP_FILES)
	$(CXX) -c $(CXXFLAGS) main.cpp -o $(OBJ)/main.o

$(OBJ)/Edge.o: Edge.cpp $(LIB)/Edge.hpp Vertex.cpp $(LIB)/Vertex.hpp
	$(CXX) -c $(CXXFLAGS) Edge.cpp -o $(OBJ)/Edge.o

$(OBJ)/Graph.o: Graph.cpp $(LIB)/Graph.hpp Vertex.cpp $(LIB)/Vertex.hpp
	$(CXX) -c $(CXXFLAGS) Graph.cpp -o $(OBJ)/Graph.o

$(OBJ)/Parser.o: Parser.cpp $(LIB)/Parser.hpp Graph.cpp $(LIB)/Graph.hpp
	$(CXX) -c $(CXXFLAGS) Parser.cpp -o $(OBJ)/Parser.o

$(OBJ)/Tests.o: Tests.cpp $(LIB)/Tests.hpp Graph.cpp $(LIB)/Graph.hpp
	$(CXX) -c $(CXXFLAGS) Tests.cpp -o $(OBJ)/Tests.o

$(OBJ)/Vertex.o: Vertex.cpp $(LIB)/Vertex.hpp Edge.cpp $(LIB)/Edge.hpp
	$(CXX) -c $(CXXFLAGS) Vertex.cpp -o $(OBJ)/Vertex.o

$(OBJ)/Runtime.o: Runtime.cpp $(LIB)/Runtime.hpp $(LIB)/Graph.hpp $(LIB)/Vertex.hpp $(LIB)/Edge.hpp
	$(CXX) -c $(CXXFLAGS) Runtime.cpp -o $(OBJ)/Runtime.o
