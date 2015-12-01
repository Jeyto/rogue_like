#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "map.h"
#include "couleur.h"

int main(void){
	t_case matrice[N][M];
	init_matrice(matrice);
	generer_matrice_tot(matrice);
	spawn_item(matrice);
	afficher_matrice(matrice);
	return 0;
}