HugeInt:HugeInt.o lab5.o
	g++ -o HugeInt HugeInt.o lab5.o -g
HugeInt.o:HugeInt.cpp HugeInt.h
	g++ -c HugeInt.cpp -g
lab5.o:lab5.cpp HugeInt.h
	g++ -c lab5.cpp -g
clean:
	rm HugeInt *.o
