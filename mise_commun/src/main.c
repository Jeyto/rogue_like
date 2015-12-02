#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "../include/map.h"
#include "../include/couleur.h"

#include "../include/structure.h"
#include "../include/IA.h"


int main(void){
	t_coord personnage;
	t_case matrice[N][M];
	int i,j;
	
	init_matrice(matrice);
	generer_matrice_tot(matrice);
	spawn_item(matrice);
	afficher_matrice(matrice);
	
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(matrice[i][j]==hero){
				personnage.x=i;
				personnage.y=j;
			}
		}
	}
	int k;
	while(matrice[personnage.x][personnage.y]==hero){
		generation_mob_suivante(matrice,personnage);
		afficher_matrice(matrice);
		printf("\n");
	}
	
	return 0;
}