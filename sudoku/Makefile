main: main.o sudoku.o
	g++ -o main main.o sudoku.o -g
main.o: main.cpp sudoku.h
	g++ -c main.cpp -g
sudoku.o: sudoku.cpp sudoku.h
	g++ -c sudoku.cpp -g
clean:
	rm main *.o
