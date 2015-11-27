
FLAG=-Wall
LIB=-lncurses
LIBB=-lmenu -lncurses

all: menu dep

dep: deplacement.c
	gcc -o deplacement deplacement.c $(LIB) $(FLAG)

menu: menu.c
	gcc -o menu menu.c $(LIBB) $(FLAG)
	
	
clean: 
	rm -f *.o

mrproper: clean
	rm -f deplacement menu
