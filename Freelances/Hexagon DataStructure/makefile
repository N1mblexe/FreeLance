CXX := g++
CXXFLAGS := -I"./include" -std=c++11 -O2 -Wall

hepsi: derle bagla calistir

derle:
	@mkdir -p ./lib ./bin
	$(CXX) $(CXXFLAGS) -c ./src/main.cpp -o ./lib/main.o
	$(CXX) $(CXXFLAGS) -c ./src/BST.cpp -o ./lib/BST.o
	$(CXX) $(CXXFLAGS) -c ./src/Hexagon.cpp -o ./lib/Hexagon.o
	$(CXX) $(CXXFLAGS) -c ./src/Manager.cpp -o ./lib/Manager.o
	$(CXX) $(CXXFLAGS) -c ./src/Node.cpp -o ./lib/Node.o

bagla:
	@mkdir -p ./bin
	$(CXX) ./lib/main.o ./lib/BST.o ./lib/Hexagon.o ./lib/Manager.o ./lib/Node.o -o ./bin/program

calistir:
	./bin/program

clean:
	rm -f ./lib/*.o ./bin/program

.PHONY: hepsi derle bagla calistir clean
