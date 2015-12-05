#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "../include/map.h"
#include "../include/couleur.h"

#include "../include/structure.h"
#include "../include/IA.h"
#include <unistd.h>

/*Fonction generation_level
*Initialise la map, genere les pieces, fait spawn les items,affiche la matrice de jeu
*Tout cela pour un niveau donne
*Permet l'affichage de matrice de jeu avec une difficulte differente
*Gere le jeu en lui_meme
*/
void generation_level(t_case matrice[N][M], int level){
	//declaration
	int i,j;
	int nb_piece;
	t_coord personnage;
	
	//traitement
	init_matrice(matrice);
	nb_piece=generer_matrice_tot(matrice,level);
	spawn_item(matrice,nb_piece,level);
	afficher_matrice(matrice);
	sauvegarde_map(matrice);
	
	if(level==4 || level==5){
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
			sauvegarde_map(matrice);
		}
	}
}

int main(void){
	//declaration
	int choix;	//choix de l'utilisateur
	int choix2;
	t_case matrice[N][M];
	
	//traitement
	printf("\t****************************************************\n");
    printf("\t     ROGUELIKE by Valentin - Baptiste - Maxime      \n");
    printf("\t****************************************************\n\n");
	do{	//affichage du menu
		printf("\n\tMenu :\n");
		printf("\t\t 1 - Jouer\n");
		printf("\t\t 2 - Continuer une partie sauvegardee\n");
		printf("\t\t 3 - Quitter\n");
		printf("\tVotre choix : ");
		scanf("%i",&choix);
		//traitement du choix de l'utilisateur
		switch(choix){	
			case 1 ://affichage du menu
					printf("\n\tMenu des niveaux :\n");
					printf("\t\t 1 - Niveau 1\n");
					printf("\t\t 2 - Niveau 2\n");
					printf("\t\t 3 - Niveau 3\n");
					printf("\t\t 4 - Niveau 4\n");
					printf("\t\t 5 - Niveau 5\n");
					printf("\t\t 6 - Retour\n");
					printf("\tVotre choix : ");
					scanf("%i",&choix2);
					//traitement du choix de l'utilisateur
					switch(choix2){	
						case 1: generation_level(matrice, 1); break;
						case 2: generation_level(matrice, 2); break;
						case 3: generation_level(matrice, 3); break;
						case 4: generation_level(matrice, 4); break;
						case 5: generation_level(matrice, 5); break;
						case 6: break;
						default: printf("Erreur: votre choix doit être compris entre 1 et 6\n");
					}
					break;
			case 2: //generer_map_sauvegarde(matrice);
					break;
			case 3:  break;
			default: printf("Erreur: votre choix doit être compris entre 1 et 3\n");
		}
	}while(choix!=3);
	
	printf("\n\t******************** FIN DU JEU ********************\n");
	return 0;
}
