#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "maptest.h"
#include "couleur.h"

int main(void){
	t_case matrice[N][M];
	init_matrice(matrice);
	generer_matrice_tot(matrice);
	afficher_matrice(matrice);
	return 0;
}