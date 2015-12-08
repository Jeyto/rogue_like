#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "../include/map.h"
#include "../include/couleur.h"
#include "../include/jeu.h"

#include "../include/structure.h"
#include "../include/IA.h"
#include <unistd.h>

int main(void){
	//declaration
	int choix;	//choix de l'utilisateur
	int choix2;
	int level;
	t_case matrice[N][M];
	
	//traitement
	system("clear");
	printf("\t****************************************************\n");
    printf("\t     ROGUELIKE by Valentin - Baptiste - Maxime      \n");
    printf("\t****************************************************\n\n");
	do{	//affichage du menu
		printf("\n\tMenu :\n");
		printf("\t\t 1 - Jouer\n");
		printf("\t\t 2 - Continuer une partie sauvegardee(A chaque deplacement de monstre, la map est sauvegardee)\n");
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
						case 1: generation_level(matrice, 1);
								jeu(matrice,1);
								break;
						case 2: generation_level(matrice, 2);
								jeu(matrice,2);
								break;
						case 3: generation_level(matrice, 3);
								jeu(matrice,3);
								break;
						case 4: generation_level(matrice, 4);
								jeu(matrice,4);
								break;
						case 5: generation_level(matrice, 5);
								jeu(matrice,5);
								break;
						case 6: couleur(33); printf("\t\t&:\t Contour des pieces infranchissable\n");
							couleur(0);
							couleur(33); printf("\t\tX:\t mur infranchissable\n");
							couleur(0);
							couleur(0);printf("\t\t(vide):\t Deplacement autorise\n");
							couleur(0);
							couleur(0);printf("\t\tP:\t porte\n");
							couleur(0);
							couleur(32);printf("\t\tC:\t coffre\n");
							couleur(0);
							couleur(32);printf("\t\tK:\t cle\n");
							couleur(0);
							couleur(35);printf("\t\t^:\t piege\n");
							couleur(0);
							couleur(32);printf("\t\t@:\t hero\n");
							couleur(0);
							couleur(35);printf("\t\tM:\t monstre agressif\n");
							couleur(0);
							couleur(35);printf("\t\tD:\t monstre defensif\n");
							couleur(0);
							couleur(35);printf("\t\tI:\t monstre inactif\n");
							couleur(0);
							couleur(34);printf("\t\t?:\t bonus\n");
							couleur(0);
								break;
						case 7: system("clear"); break;
						default: printf("Erreur: votre choix doit être compris entre 1 et 7\n");
					}
					break;
			case 2: level=generer_map_sauvegarde(matrice);
					jeu(matrice,level);
					break;
			case 3:  break;
			default: printf("Erreur: votre choix doit être compris entre 1 et 3\n");
		}
	}while(choix!=3);
	
	printf("\n\t******************** FIN DU JEU ********************\n");
	return 0;
}
