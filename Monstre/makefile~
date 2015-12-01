CC=gcc
FLAG=-Wall -W -g
OBJ= main.o IA.o
JOB= ./include/*.h
SRC=./src/
all:main.exe clean

main.exe: ${OBJ}
	${CC} -o ./bin/main.exe ${OBJ} ${FLAG}

struct.o: ${SRC}struct.c ${JOB}
	${CC} -c ${SRC}struct.c ${FLAG}

IA.o: ${SRC}IA.c ${JOB}
	${CC} -c ${SRC}IA.c ${FLAG} 

main.o: ${SRC}main.c ${JOB}
	${CC} -c ${SRC}main.c ${JOB} ${FLAG}
	
clean:
	rm  *.o

