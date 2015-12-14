#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "IA.h"
#include "jeu.h"
#include "liste_ptr_coord.h"
#include "map.h"
#include "sauvegarde.h"
#include "structure.h"
#include "personnage.h"

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
	init_liste_mob(matrice);
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
	int dx, dy;
	int i,j;
	t_coord pos_sortie;
	t_coord perso_position;
	int niveau_termine=0;
	
	//position de la sortie 3cases du coffre
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(matrice[i][j]==coffre){
				pos_sortie.x=i;
				pos_sortie.y=j-3;
			}
		}
	}
	
	//traitement
	if(level>=1){
		sauvegarde_map(matrice,level);
		while(valeur_PV_personnage()>0 && niveau_termine==0){ //tant que la vie>0 et niveau en cours
			scanf("%c",&dep);
			printf("Score: %i\n",valeur_score_personnage());
			printf("Vie: %i\n",valeur_PV_personnage());
			switch(dep){
				case 'z':
					dx=-1; dy=0;
					break;
				case 'q':
					dx=0; dy=-1;
					break;
				case 's':
					dx=1; dy=0;
					break;
				case 'd':
					dx=0; dy=1;
					break;
				default: dx=0; dy=0;
					break;
			}
				
				if(dx != 0 || dy != 0){
					valeur_position_personnage(&perso_position);
					if(matrice[perso_position.x+dx][perso_position.y+dy]!=mur_contour && matrice[perso_position.x+dx][perso_position.y+dy]!=mur){
						perso_position.x=perso_position.x+dx;
						perso_position.y=perso_position.y+dy;
						//action en fonction de la nouvelle case
						switch(matrice[perso_position.x][perso_position.y]){
							case vide:
								matrice[perso_position.x-dx][perso_position.y-dy]=vide;
								matrice[perso_position.x][perso_position.y]=hero;
								break;
							case couloir:
								matrice[perso_position.x-dx][perso_position.y-dy]=vide;
								matrice[perso_position.x][perso_position.y]=hero;
								break;
							case porte:
								matrice[perso_position.x-dx][perso_position.y-dy]=vide;
								perso_position.x=perso_position.x+dx;
								perso_position.y=perso_position.y+dy;
								matrice[perso_position.x][perso_position.y]=hero;
								break;
							case cle:
								matrice[perso_position.x-dx][perso_position.y-dy]=vide;
								modif_cle_personnage(1);
								printf("cle prise\n");
								matrice[perso_position.x][perso_position.y]=hero;
								break;
							case coffre:
								if(valeur_cle_personnage()==0){
									perso_position.x=perso_position.x-dx; //personnage ne bouge pas
									perso_position.y=perso_position.y-dy;
									printf("veuillez prendre la cle\n");
								}
								else{
									matrice[perso_position.x-dx][perso_position.y-dy]=vide;
									printf("coffre pris\n");
									matrice[perso_position.x][perso_position.y]=hero;
									//creation piece sortie
									matrice[pos_sortie.x][pos_sortie.y]=sortie;
									matrice[pos_sortie.x-2][pos_sortie.y]=porte;
									matrice[pos_sortie.x-2][pos_sortie.y-1]=mur_contour;
									matrice[pos_sortie.x-2][pos_sortie.y+1]=mur_contour;
									matrice[pos_sortie.x-1][pos_sortie.y]=vide;
									matrice[pos_sortie.x-1][pos_sortie.y-1]=mur_contour;
									matrice[pos_sortie.x-1][pos_sortie.y+1]=mur_contour;
									matrice[pos_sortie.x][pos_sortie.y-1]=mur_contour;
									matrice[pos_sortie.x][pos_sortie.y+1]=mur_contour;
								}
								break;
							case bonus:
								matrice[perso_position.x-dx][perso_position.y-dy]=vide;
								gain_bonus_personnage(20);
								matrice[perso_position.x][perso_position.y]=hero;
								break;
							case piege:
							case monstre_agressif:
							case monstre_defensif:
							case monstre_inactif:
								perso_position.x=perso_position.x-dx; //personnage ne bouge pas
								perso_position.y=perso_position.y-dy;
								spawn_death();
								break;
							
							case sortie:
								niveau_termine=1;
								break;
							default:
								break;
						}
						//personnage est mort, il a 3 coup pour se sauver et apres attaque des monstres
						if(valeur_invi_personnage()==0)
							generation_mob_suivante(matrice,perso_position);
						else{
							if(valeur_invi_personnage()<=50) modif_invi_personnage(valeur_invi_personnage()+1);
							else modif_invi_personnage(0);
						}
						modif_position_personnage(perso_position);
						sauvegarde_map(matrice,level);
						afficher_matrice(matrice);
					}
				}
					
				
		}
		if(niveau_termine==0){
			game_message(matrice,niveau_termine);
		}
		else{
			level++;
			if(level<=5){
				generation_level(matrice, level);
				jeu(matrice,level);
			}
			else game_message(matrice,1);
		}
	}
}
