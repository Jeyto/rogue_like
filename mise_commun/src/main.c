#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "../include/map.h"
#include "../include/couleur.h"
#include "../include/jeu.h"
#include "../include/IA.h"
#include "../include/structure.h"
#include "../include/liste_ptr_coord.h"

int main(void){
   	srand(time(NULL));
	//declaration
	int choix;	//choix de l'utilisateur
	int choix2;
	int level;
	t_case matrice[N][M];
	init_liste();

	//traitement
	system("clear");
	printf("\t****************************************************\n");
    printf("\t     ROGUELIKE by Valentin - Baptiste - Maxime      \n");
    printf("\t****************************************************\n\n");
	do{	//affichage du menu
		printf("\n\tMenu :\n");
		printf("\t\t 1 - Jouer\n");
		printf("\t\t 2 - Charger une partie sauvegardee(sauvegarde a chaque objectif reussi)\n");
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
					printf("\t\t 6 - Explication items\n");
					printf("\t\t 7 - Retour\n");
					printf("\tVotre choix : ");
					scanf("%i",&choix2);
					//traitement du choix de l'utilisateur
					switch(choix2){
						case 1: //joueur
							generation_level(matrice, 1);
							jeu(matrice,1);
							break;
						case 2: generation_level(matrice, 2);
							jeu(matrice,2);
							break;
						case 3:	generation_level(matrice, 3);
							jeu(matrice,3);
							break;
						case 4: generation_level(matrice, 4);
							jeu(matrice,4);
							break;
						case 5: generation_level(matrice, 5);
							jeu(matrice,5);
							break;
						case 6:
							printf("\t\t&:\t Contour des pieces infranchissable\n");
							printf("\t\tX:\t mur infranchissable\n");
							printf("\t\t(vide):\t Deplacement autorise\n");
							printf("\t\tP:\t porte\n");
							printf("\t\tC:\t coffre\n");
							printf("\t\tK:\t cle\n");
							printf("\t\t@:\t hero\n");
							printf("\t\t^:\t piege\n");
							printf("\t\tM:\t monstre agressif\n");
							printf("\t\tD:\t monstre defensif\n");
							printf("\t\tI:\t monstre inactif\n");
							printf("\t\t?:\t bonus\n");
							break;
						case 7: system("clear"); break;
						default: printf("Erreur: votre choix doit être compris entre 1 et 7\n");
					}
					break;
			case 2: level=generer_map_sauvegarde(matrice);
				afficher_matrice(matrice);
				jeu(matrice,level);
				break;
			case 3:  break;
			default: printf("Erreur: votre choix doit être compris entre 1 et 3\n");
		}
	}while(choix!=3);

	printf("\n\t******************** FIN DU JEU ********************\n");
	return 0;
}
