#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "../include/map.h"
#include "../include/couleur.h"

#include "../include/structure.h"
#include "../include/IA.h"
#include <unistd.h>
void generation_level(int level, t_case matrice[N][M]){
	t_coord personnage;
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
	while(matrice[personnage.x][personnage.y]==hero){
		generation_mob_suivante(matrice,personnage);
		afficher_matrice(matrice);
		usleep(100000);
		system("clear");
	}
}

int main(void){
	t_case matrice[N][M];
		
	int choix;	/* Choix de l'utilisateur */
	int choix2;
	do{	/* Affichage du menu */
		printf("\nMenu :\n");
		printf(" 1 - Jouer\n");
		printf(" 2 - Partie sauvegardee\n");
		printf(" 3 - Quitter\n");
		printf("Votre choix : ");
		scanf("%i",&choix);
		/* Traitement du choix de l'utilisateur */
		switch(choix){	
			case 1 :/* Affichage du menu */
					printf("\nMenu des niveaux :\n");
					printf(" 1 - Niveau 1\n");
					printf(" 2 - Niveau 2\n");
					printf(" 3 - Niveau 3\n");
					printf(" 4 - Niveau 4\n");
					printf(" 5 - Niveau 5\n");
					printf(" 6 - Retour\n");
					printf("Votre choix : ");
					scanf("%i",&choix2);
					/* Traitement du choix de l'utilisateur */
					switch(choix2){	
						case 1: generation_level(1,matrice); break;
						case 2: generation_level(2,matrice); break;
						case 3: generation_level(2,matrice); break;
						case 4: generation_level(4,matrice); break;
						case 5: generation_level(5,matrice); break;
						case 6: break;
						default: printf("Erreur: votre choix doit être compris entre 1 et 6\n");
					}
					break;
			case 2:  printf("on verra plus tard\n"); break;
			case 3:  break;
			default: printf("Erreur: votre choix doit être compris entre 1 et 3\n");
		}
	}while(choix!=3);
	
	return 0;
}
