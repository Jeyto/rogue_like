#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "../include/map.h"
#include "../include/couleur.h"
#include "../include/jeu.h"
#include "../include/structure.h"
#include "../include/IA.h"

t_personnage *personnage;
/***************Fonction Personnage***************/
/*
*Fonction init_personnage
*Initialise la variable personnage
*/
void init_personnage(){
	personnage = malloc(sizeof(t_personnage));
	personnage->PV=3;
	personnage->score_bonus=0;
	personnage->cle=0;
	personnage->invisible=0;
}
/*
*Fonction gain_bonus_personnage(int gain)
* ajoute gain au score
*/
void gain_bonus_personnage(int gain){
	personnage->score_bonus=personnage->score_bonus+gain;
}
void valeur_personnage(t_personnage *valeur){
	valeur->PV=personnage->PV;
	valeur->score_bonus=personnage->score_bonus;

}
void modif_position_personnage(t_coord npos){
	personnage->position.x=npos.x;
	personnage->position.y=npos.y;
}
void valeur_position_personnage(t_coord *pos){
	pos->x=personnage->position.x;
	pos->y=personnage->position.y;
}

/******************************************************************/
/*Fonction spawn_death
*si le joueur perd un combat(piege,monstre), il perd un point de vie
*et retourne a l'objectif precedent(depart, cle, ou coffre)
*/
void spawn_death(void){
	personnage->PV=personnage->PV-1;
	personnage->invisible=1;
}

/***********************************************************************/
/*Fonction generation_level
*Initialise la map, genere les pieces, fait spawn les items,affiche la matrice de jeu
*Tout cela pour un niveau donne
*Permet l'affichage de matrice de jeu avec une difficulte differente
*/
void generation_level(t_case matrice[N][M], int level){
	//declaration
	int nb_piece;
	init_personnage();
	//traitement
	init_matrice(matrice);
	nb_piece=generer_matrice_tot(matrice,level);
	spawn_item(matrice,nb_piece,level);
	afficher_matrice(matrice);
}

/*************************************************************/
/*Fonction game_message
*Modifie la matrice de jeu et affiche le message "game over" ou "good game"
*/
void game_message(t_case matrice[N][M], int niveau_termine){
	int i=0;
	int j=0;
	int valeur;
	FILE * fichier;
	if(niveau_termine==0) fichier=fopen("map_game_over.txt","r");
	else fichier=fopen("map_game_win.txt","r");
	//si aucun fichier de ce nom, affiche matrice rempli de mur
	if(fichier==NULL){
		init_matrice(matrice);
	}
	else{
		while(!feof(fichier)){
			fscanf(fichier,"%i",&valeur);
			convertion_int_enum(matrice,i,j,valeur);
			j++;
		}
		fclose(fichier);
	}
	afficher_matrice(matrice);
}

/******************************************************************/
/*Fonction jeu
*Gere le jeu en lui-meme
*/
void jeu(t_case matrice[N][M], int level){
	//declaration
	char dep;
	t_coord pos_sortie=personnage->position;
	int niveau_termine=0;
	init_liste_mob(matrice);
	
	//traitement
	if(level>=1){
		sauvegarde_map(matrice,level,*personnage);
		while(personnage->PV>0 && niveau_termine==0){ //tant que la vie>0 et niveau en cours
			scanf("%c",&dep);
			printf("Score: %i\n",personnage->score_bonus);
			printf("Vie: %i\n",personnage->PV);
			switch(dep){
				case 'z':
					if(matrice[personnage->position.x-1][personnage->position.y]!=mur_contour && matrice[personnage->position.x-1][personnage->position.y]!=mur){
						personnage->position.x=personnage->position.x-1;
						//action en fonction de la nouvelle case
						switch(matrice[personnage->position.x][personnage->position.y]){
							case vide:
								matrice[personnage->position.x+1][personnage->position.y]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case couloir:
								matrice[personnage->position.x+1][personnage->position.y]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case porte:
								matrice[personnage->position.x+1][personnage->position.y]=vide;
								personnage->position.x=personnage->position.x-1;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case cle:
								matrice[personnage->position.x+1][personnage->position.y]=vide;
								personnage->cle=1;
								printf("cle prise\n");
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case coffre:
								if(personnage->cle ==0){
									personnage->position.x=personnage->position.x+1; //personnage ne bouge pas
									printf("veuillez prendre la cle\n");
								}
								else{
									matrice[personnage->position.x+1][personnage->position.y]=vide;
									printf("coffre pris\n");
									matrice[personnage->position.x][personnage->position.y]=hero;
									matrice[pos_sortie.x][pos_sortie.y]=sortie;
								}
								break;
							case bonus:
								matrice[personnage->position.x+1][personnage->position.y]=vide;
								gain_bonus_personnage(20);
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case piege:
								personnage->position.x=personnage->position.x+1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_agressif:
								personnage->position.x=personnage->position.x+1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_defensif:
								personnage->position.x=personnage->position.x+1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_inactif:
								personnage->position.x=personnage->position.x+1; //personnage ne bouge pas
								spawn_death();
								break;
							case sortie:
								niveau_termine=1;
								break;
							default:
								break;
						}
						//personnage est mort, il a 3 coup pour se sauver et apres attaque des monstres
						if(personnage->invisible==0)
							generation_mob_suivante(matrice,personnage->position);
						else{
							if(personnage->invisible<=3) personnage->invisible=personnage->invisible+1;
							else personnage->invisible=0;
						}
						sauvegarde_map(matrice,level,*personnage);
						afficher_matrice(matrice);
					}
					break;
				case 'q':
					if(matrice[personnage->position.x][personnage->position.y-1]!=mur_contour && matrice[personnage->position.x][personnage->position.y-1]!=mur){
						personnage->position.y=personnage->position.y-1;
						//action en fonction de la nouvelle case
						switch(matrice[personnage->position.x][personnage->position.y]){
							case vide:
								matrice[personnage->position.x][personnage->position.y+1]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case couloir:
								matrice[personnage->position.x][personnage->position.y+1]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case porte:
								matrice[personnage->position.x][personnage->position.y+1]=vide;
								personnage->position.y=personnage->position.y-1;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case cle:
								matrice[personnage->position.x][personnage->position.y+1]=vide;
								personnage->cle=1;
								printf("cle prise\n");
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case coffre:
								if(personnage->cle==0){
									personnage->position.y=personnage->position.y+1; //personnage ne bouge pas
									printf("veuillez prendre la cle\n");
								}
								else{
									matrice[personnage->position.x][personnage->position.y+1]=vide;
									printf("coffre pris\n");
									matrice[personnage->position.x][personnage->position.y]=hero;
									matrice[pos_sortie.x][pos_sortie.y]=sortie;
								}
								break;
							case bonus:
								matrice[personnage->position.x][personnage->position.y+1]=vide;
								gain_bonus_personnage(20);
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case piege:
								personnage->position.y=personnage->position.y+1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_agressif:
								personnage->position.y=personnage->position.y+1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_defensif:
								personnage->position.y=personnage->position.y+1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_inactif:
								personnage->position.y=personnage->position.y+1; //personnage ne bouge pas
								spawn_death();
								break;
							case sortie:
								niveau_termine=1;
								break;
							default:
								break;
						}
						//personnage est mort, il a 3 coup pour se sauver et apres attaque des monstres
						if(personnage->invisible==0)
							generation_mob_suivante(matrice,personnage->position);
						else{
							if(personnage->invisible<=3) personnage->invisible=personnage->invisible+1;
							else personnage->invisible=0;
						}
						sauvegarde_map(matrice,level,*personnage);
						afficher_matrice(matrice);
					}
					break;
				case 's':
					if(matrice[personnage->position.x+1][personnage->position.y]!=mur_contour && matrice[personnage->position.x+1][personnage->position.y]!=mur){
						personnage->position.x=personnage->position.x+1;
						//action en fonction de la nouvelle case
						switch(matrice[personnage->position.x][personnage->position.y]){
							case vide:
								matrice[personnage->position.x-1][personnage->position.y]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case couloir:
								matrice[personnage->position.x-1][personnage->position.y]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case porte:
								matrice[personnage->position.x-1][personnage->position.y]=vide;
								personnage->position.x=personnage->position.x+1;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case cle:
								matrice[personnage->position.x-1][personnage->position.y]=vide;
								personnage->cle=1;
								printf("cle prise\n");
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case coffre:
								if(personnage->cle==0){
									personnage->position.x=personnage->position.x-1; //personnage ne bouge pas
									printf("veuillez prendre la cle\n");
								}
								else{
									matrice[personnage->position.x-1][personnage->position.y]=vide;
									printf("coffre pris\n");
									matrice[personnage->position.x][personnage->position.y]=hero;
									matrice[pos_sortie.x][pos_sortie.y]=sortie;
								}
								break;
							case bonus:
								matrice[personnage->position.x-1][personnage->position.y]=vide;
								gain_bonus_personnage(20);
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case piege:
								personnage->position.x=personnage->position.x-1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_agressif:
								personnage->position.x=personnage->position.x-1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_defensif:
								personnage->position.x=personnage->position.x-1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_inactif:
								personnage->position.x=personnage->position.x-1; //personnage ne bouge pas
								spawn_death();
								break;
							case sortie:
								niveau_termine=1;
								break;
							default:
								break;
						}
						//personnage est mort, il a 3 coup pour se sauver et apres attaque des monstres
						if(personnage->invisible==0)
							generation_mob_suivante(matrice,personnage->position);
						else{
							if(personnage->invisible<=3) personnage->invisible=personnage->invisible+1;
							else personnage->invisible=0;
						}
						sauvegarde_map(matrice,level,*personnage);
						afficher_matrice(matrice);
					}
					break;
				case 'd':
					if(matrice[personnage->position.x][personnage->position.y+1]!=mur_contour && matrice[personnage->position.x][personnage->position.y+1]!=mur){
						personnage->position.y=personnage->position.y+1;
						//action en fonction de la nouvelle case
						switch(matrice[personnage->position.x][personnage->position.y]){
							case vide:
								matrice[personnage->position.x][personnage->position.y-1]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case couloir:
								matrice[personnage->position.x][personnage->position.y-1]=vide;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case porte:
								matrice[personnage->position.x][personnage->position.y-1]=vide;
								personnage->position.y++;
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case cle:
								matrice[personnage->position.x][personnage->position.y-1]=vide;
								personnage->cle=1;
								printf("cle prise\n");
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case coffre:
								if(personnage->cle==0){
									personnage->position.y=personnage->position.y-1; //personnage ne bouge pas
									printf("veuillez prendre la cle\n");
								}
								else{
									matrice[personnage->position.x][personnage->position.y-1]=vide;
									printf("coffre pris\n");
									matrice[personnage->position.x][personnage->position.y]=hero;
									matrice[pos_sortie.x][pos_sortie.y]=sortie;
								}
								break;
							case bonus:
								matrice[personnage->position.x][personnage->position.y-1]=vide;
								gain_bonus_personnage(20);
								matrice[personnage->position.x][personnage->position.y]=hero;
								break;
							case piege:
								personnage->position.y=personnage->position.y-1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_agressif:
								personnage->position.y=personnage->position.y-1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_defensif:
								personnage->position.y=personnage->position.y-1; //personnage ne bouge pas
								spawn_death();
								break;
							case monstre_inactif:
								personnage->position.y=personnage->position.y-1; //personnage ne bouge pas
								spawn_death();
								break;
							case sortie:
								niveau_termine=1;
								break;
							default:
								break;
						}
						//personnage est mort, il a 3 coup pour se sauver et apres attaque des monstres
						if(personnage->invisible==0)
							generation_mob_suivante(matrice,personnage->position);
						else{
							if(personnage->invisible<=3) personnage->invisible=personnage->invisible+1;
							else personnage->invisible=0;
						}
						sauvegarde_map(matrice,level,*personnage);
						afficher_matrice(matrice);
					}
					break;
			}
		}
		//perdu ou gagne, message de fin
		game_message(matrice,niveau_termine);
	}
}
