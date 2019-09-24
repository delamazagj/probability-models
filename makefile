all: 
	g++ -std=c++11 -c *.cpp
	g++ -std=c++11 main.o t2Table.o tupleT2.o -o output

clean: 
	rm *.o

out:
	./output
