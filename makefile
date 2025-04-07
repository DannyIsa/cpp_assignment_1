# daniisakov@gmail.com 

Main: main.o graph.o algorithms.o data_structures.o
	g++ -o Main main.o graph.o algorithms.o data_structures.o

main.o: main.cpp graph.h algorithms.h
	g++ -c main.cpp -Wall -std=c++11

graph.o: graph.cpp graph.h
	g++ -c graph.cpp -Wall -std=c++11

algorithms.o: algorithms.cpp algorithms.h graph.h data_structures.h
	g++ -c algorithms.cpp -Wall -std=c++11

data_structures.o: data_structures.cpp data_structures.h
	g++ -c data_structures.cpp -Wall -std=c++11

test: test.o graph.o algorithms.o data_structures.o
	g++ -o Test test.o graph.o algorithms.o data_structures.o
	./Test

test.o: test.cpp graph.h algorithms.h
	g++ -c test.cpp -Wall -std=c++11

valgrind: Main
	valgrind --leak-check=full ./Main

clean:
	rm -f *.o Main

.PHONY: all clean test valgrind