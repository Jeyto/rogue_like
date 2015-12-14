CC=gcc
FLAG=-Wall -W -g
OBJ= main.o IA.o liste_ptr_coord.o map.o jeu.o structure.o
JOB= ./include/*.h
SRC=./src/
all:main.exe

main.exe: ${OBJ}
	${CC} -o ./bin/main.exe ${OBJ} ${FLAG}

structure.o: ${SRC}structure.c ${JOB}
	${CC} -c ${SRC}structure.c ${FLAG}

IA.o: ${SRC}IA.c ${JOB}
	${CC} -c ${SRC}IA.c ${FLAG}

liste_ptr_coord.o: ${SRC}IA.c ${JOB}
	${CC} -c ${SRC}liste_ptr_coord.c ${FLAG} 

map.o: ${SRC}map.c ${JOB}
	${CC} -c ${SRC}map.c ${FLAG}

jeu.o: ${SRC}jeu.c ${JOB}
	${CC} -c ${SRC}jeu.c ${FLAG}

main.o: ${SRC}main.c ${JOB}
	${CC} -c ${SRC}main.c ${JOB} ${FLAG}
	
clean:
	rm ./include/*.gch
	rm  *.o
