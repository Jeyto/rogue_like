map: main.o map.o
	gcc main.o map.o -o map -Wall

map.o: map.c map.h couleur.h
	gcc -c map.c -Wall

main.o: main.c map.c map.h couleur.h
	gcc -c main.c -Wall

