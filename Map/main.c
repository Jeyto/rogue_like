#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "map.h"
#include "couleur.h"

int main(void){
	char matrice[N][M];
	init_matrice(matrice);
	generer_matrice(matrice);
	afficher_matrice(matrice);
	return 0;
}
	
