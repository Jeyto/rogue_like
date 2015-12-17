CC=gcc
FLAG=-Wall -W -g -I ./include/
OBJ= main.o IA.o liste_mob.o map.o jeu.o structure.o sauvegarde.o personnage.o
JOB= ./include/*.h
LIB=-lncurses
SRC=./src/
all:main.exe

main.exe: ${OBJ}
	${CC} -o ./bin/main.exe ${OBJ} ${LIB} ${FLAG}

structure.o: ${SRC}structure.c ${JOB}
	${CC} -c ${SRC}structure.c ${FLAG}

personnage.o: ${SRC}personnage.c ${JOB}
	${CC} -c ${SRC}personnage.c ${FLAG}

IA.o: ${SRC}IA.c ${JOB}
	${CC} -c ${SRC}IA.c ${FLAG}

liste_mob.o: ${SRC}IA.c ${JOB}
	${CC} -c ${SRC}liste_mob.c ${FLAG}

map.o: ${SRC}map.c ${JOB}
	${CC} -c ${SRC}map.c ${FLAG}

jeu.o: ${SRC}jeu.c ${JOB}
	${CC} -c ${SRC}jeu.c ${FLAG}

sauvegarde.o: ${SRC}sauvegarde.c ${JOB}
	${CC} -c ${SRC}sauvegarde.c ${FLAG}

main.o: ${SRC}main.c ${JOB}
	${CC} -c ${SRC}main.c ${JOB} ${LIB} ${FLAG}

clean:
	rm ./include/*.gch
	rm  *.o
