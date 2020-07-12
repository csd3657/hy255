clean:
	rm -rf *.out
	rm -rf *.o
	rm -rf *.h.gch

list:
	gcc -Wall -ansi -pedantic symtablelist.c SymTable.h testsymtab.c

hash:
	gcc -Wall -ansi -pedantic symtablehash.c SymTable.h testsymtab.c

run:
	./a.out