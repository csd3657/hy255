sudoku: sudoku.o grid.o
	gcc -Wall -ansi -pedantic sudoku.o grid.o -o sudoku

main.o: main.c
	gcc -Wall -ansi -pedantic -c main.c

sudoku.o: sudoku.c
	gcc -Wall -ansi -pedantic -c sudoku.c

grid.o: grid.c
	gcc -Wall -ansi -pedantic -c grid.c

clean:
	rm -f *.o sudoku
