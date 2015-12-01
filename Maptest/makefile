monprog.exe: main.o maptest.o
	gcc main.o maptest.o -o monprog.exe -Wall

maptest.o: maptest.c maptest.h couleur.h
	gcc -c maptest.c -Wall

main.o: main.c maptest.c maptest.h couleur.h
	gcc -c main.c -Wall

