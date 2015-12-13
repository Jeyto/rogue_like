#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include "../include/map.h"
#include "../include/couleur.h"
#include "../include/jeu.h"
#include "../include/structure.h"
#include "../include/IA.h"

/*Fonction generation_level
*Initialise la map, genere les pieces, fait spawn les items,affiche la matrice de jeu
*Tout cela pour un niveau donne
*Permet l'affichage de matrice de jeu avec une difficulte differente
*/
void generation_level(t_case matrice[N][M], int level){
	//declaration
	int nb_piece;

	//traitement
	init_matrice(matrice);
	nb_piece=generer_matrice_tot(matrice,level);
	spawn_item(matrice,nb_piece,level);
}

/*************************************************************/
/*Fonction game_over
*Modifie la matrice de jeu et affiche le message "game over"
*/
void game_over(t_case matrice[N][M]){
	int i=0;
	int j=0;
	FILE * fichier;
	fichier=fopen("map_game_over.txt","r");
	//si aucun fichier de ce nom, affiche matrice rempli de mur
	if(fichier==NULL){
		init_matrice(matrice);
	}
	else{
		while(!feof(fichier)){
			fscanf(fichier,"%i",&matrice[i][j]);
			j++;
		}
		fclose(fichier);
	}
	afficher_matrice(matrice);
}

/*************************************************************/
/*Fonction game_win
*Modifie la matrice de jeu et affiche le message "Winner"
*/
void game_win(t_case matrice[N][M]){
	int i=0;
	int j=0;
	FILE * fichier;
	fichier=fopen("map_game_win.txt","r");
	//si aucun fichier de ce nom, affiche matrice rempli de mur
	if(fichier==NULL){
		init_matrice(matrice);
	}
	else{
		while(!feof(fichier)){
			fscanf(fichier,"%i",&matrice[i][j]);
			j++;
		}
		fclose(fichier);
	}
	afficher_matrice(matrice);
}
/******************************************************************/
/*Fonction spawn_death
*si le joueur perd un combat(piege,monstre), il perd un point de vie
*et retourne a l'objectif precedent(depart, cle, ou coffre)
*/
void spawn_death(t_case matrice[N][M],t_personnage *gestion_personnage,t_coord *pos_personnage){
	int level=generer_map_sauvegarde(matrice,*gestion_personnage);
	gestion_personnage->PV=gestion_personnage->PV-1;
	pos_personnage->x=gestion_personnage->position_spawn.x;
	pos_personnage->y=gestion_personnage->position_spawn.y;
	sauvegarde_map(matrice,level,*gestion_personnage);
}
/******************************************************************/
/*Fonction jeu
*Gere le jeu en lui-meme
*/
void jeu(t_case matrice[N][M], int level,t_personnage gestion_personnage){
	//declaration
	int i,j;
	char dep;
	t_coord pos_personnage;
	t_coord pos_init;
	t_coord pos_cle;
	t_coord pos_coffre;
	int niveau_termine=0;
	init_liste_mob(matrice);
	//traitement
	if(level>=1){
		//recuperation position objectif
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				if(matrice[i][j]==hero){
					pos_personnage.x=i;
					pos_personnage.y=j;
					pos_init.x=i;
					pos_init.y=j;
				}
				if(matrice[i][j]==cle){
					pos_cle.x=i;
					pos_cle.y=j;
				}
				if(matrice[i][j]==coffre){
					pos_coffre.x=i;
					pos_coffre.y=j;
				}
			}
		}
		sauvegarde_map(matrice,level,gestion_personnage);
		while(gestion_personnage.PV>0 && niveau_termine==0){ //tant que la vie>0
			scanf("%c",&dep);
			printf("Score: %i\n",gestion_personnage.score_bonus);
			printf("Vie: %i\n",gestion_personnage.PV);
			switch(dep){
				case 'z':
							if(matrice[pos_personnage.x-1][pos_personnage.y]!=mur_contour && matrice[pos_personnage.x-1][pos_personnage.y]!=mur){
								pos_personnage.x--;
								//action en fonction de la nouvelle case
								switch(matrice[pos_personnage.x][pos_personnage.y]){
									case vide:
										matrice[pos_personnage.x+1][pos_personnage.y]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case couloir:
										matrice[pos_personnage.x+1][pos_personnage.y]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case porte:
										matrice[pos_personnage.x+1][pos_personnage.y]=vide;
										pos_personnage.x--;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case cle:
										matrice[pos_personnage.x+1][pos_personnage.y]=vide;
										//si mort il y a, a l'emplacement de la cle, joueur spawnera
										gestion_personnage.position_spawn.x=pos_cle.x;
										gestion_personnage.position_spawn.y=pos_cle.y;
										printf("cle prise\n");
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										sauvegarde_map(matrice,level,gestion_personnage);
										break;
									case coffre:
										if(gestion_personnage.position_spawn.x!=pos_cle.x && gestion_personnage.position_spawn.y!=pos_cle.y){
											pos_personnage.x++; //personnage ne bouge pas
											printf("veuillez prendre la cle\n");
										}
										else{
											matrice[pos_personnage.x+1][pos_personnage.y]=vide;
											gestion_personnage.position_spawn.x=pos_coffre.x;
											gestion_personnage.position_spawn.y=pos_coffre.y;
											printf("coffre pris\n");
											matrice[pos_personnage.x][pos_personnage.y]=hero;
											matrice[pos_init.x][pos_init.y]=sortie;
											sauvegarde_map(matrice,level,gestion_personnage);
										}
										break;
									case bonus:
										matrice[pos_personnage.x+1][pos_personnage.y]=vide;
										gestion_personnage.score_bonus=gestion_personnage.score_bonus+20;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case piege:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_agressif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_defensif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_inactif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case sortie:
										niveau_termine=1;
										break;
									default:
										break;
								}
								generation_mob_suivante(matrice,pos_personnage);
								afficher_matrice(matrice);
							}
							break;
				case 'q':	if(matrice[pos_personnage.x][pos_personnage.y-1]!=mur_contour && matrice[pos_personnage.x][pos_personnage.y-1]!=mur){
								pos_personnage.y--;
								//action en fonction de la nouvelle case
								switch(matrice[pos_personnage.x][pos_personnage.y]){
									case vide:
										matrice[pos_personnage.x][pos_personnage.y+1]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case couloir:
										matrice[pos_personnage.x][pos_personnage.y+1]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case porte:
										matrice[pos_personnage.x][pos_personnage.y+1]=vide;
										pos_personnage.y--;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case cle:
										matrice[pos_personnage.x][pos_personnage.y+1]=vide;
										//si mort il y a, a l'emplacement de la cle, joueur spawnera
										gestion_personnage.position_spawn.x=pos_cle.x;
										gestion_personnage.position_spawn.y=pos_cle.y;
										printf("cle prise\n");
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										sauvegarde_map(matrice,level,gestion_personnage);
										break;
									case coffre:
										if(gestion_personnage.position_spawn.x!=pos_cle.x && gestion_personnage.position_spawn.y!=pos_cle.y){
											pos_personnage.y++; //personnage ne bouge pas
											printf("veuillez prendre la cle\n");
										}
										else{
											matrice[pos_personnage.x][pos_personnage.y+1]=vide;
											gestion_personnage.position_spawn.x=pos_coffre.x;
											gestion_personnage.position_spawn.y=pos_coffre.y;
											printf("coffre pris\n");
											matrice[pos_personnage.x][pos_personnage.y]=hero;
											matrice[pos_init.x][pos_init.y]=sortie;
											sauvegarde_map(matrice,level,gestion_personnage);
										}
										break;
									case bonus:
										matrice[pos_personnage.x][pos_personnage.y+1]=vide;
										gestion_personnage.score_bonus=gestion_personnage.score_bonus+20;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case piege:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_agressif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_defensif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_inactif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case sortie:
										niveau_termine=1;
										break;
									default:
										break;
								}
								generation_mob_suivante(matrice,pos_personnage);
								afficher_matrice(matrice);
							}
							break;
				case 's':	if(matrice[pos_personnage.x+1][pos_personnage.y]!=mur_contour && matrice[pos_personnage.x+1][pos_personnage.y]!=mur){
								pos_personnage.x++;
								//action en fonction de la nouvelle case
								switch(matrice[pos_personnage.x][pos_personnage.y]){
									case vide:
										matrice[pos_personnage.x-1][pos_personnage.y]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case couloir:
										matrice[pos_personnage.x-1][pos_personnage.y]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case porte:
										matrice[pos_personnage.x-1][pos_personnage.y]=vide;
										pos_personnage.x++;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case cle:
										matrice[pos_personnage.x-1][pos_personnage.y]=vide;
										//si mort il y a, a l'emplacement de la cle, joueur spawnera
										gestion_personnage.position_spawn.x=pos_cle.x;
										gestion_personnage.position_spawn.y=pos_cle.y;
										printf("cle prise\n");
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										sauvegarde_map(matrice,level,gestion_personnage);
										break;
									case coffre:
										if(gestion_personnage.position_spawn.x!=pos_cle.x && gestion_personnage.position_spawn.y!=pos_cle.y){
											pos_personnage.x--; //personnage ne bouge pas
											printf("veuillez prendre la cle\n");
										}
										else{
											matrice[pos_personnage.x-1][pos_personnage.y]=vide;
											gestion_personnage.position_spawn.x=pos_coffre.x;
											gestion_personnage.position_spawn.y=pos_coffre.y;
											printf("coffre pris\n");
											matrice[pos_personnage.x][pos_personnage.y]=hero;
											matrice[pos_init.x][pos_init.y]=sortie;
											sauvegarde_map(matrice,level,gestion_personnage);
										}
										break;
									case bonus:
										matrice[pos_personnage.x-1][pos_personnage.y]=vide;
										gestion_personnage.score_bonus=gestion_personnage.score_bonus+20;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case piege:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_agressif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_defensif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_inactif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case sortie:
										niveau_termine=1;
										break;
									default:
										break;
								}
								generation_mob_suivante(matrice,pos_personnage);
								afficher_matrice(matrice);
							}
							break;
				case 'd':	if(matrice[pos_personnage.x][pos_personnage.y+1]!=mur_contour && matrice[pos_personnage.x][pos_personnage.y+1]!=mur){
								pos_personnage.y++;
								//action en fonction de la nouvelle case
								switch(matrice[pos_personnage.x][pos_personnage.y]){
									case vide:
										matrice[pos_personnage.x][pos_personnage.y-1]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case couloir:
										matrice[pos_personnage.x][pos_personnage.y-1]=vide;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case porte:
										matrice[pos_personnage.x][pos_personnage.y-1]=vide;
										pos_personnage.y++;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case cle:
										matrice[pos_personnage.x][pos_personnage.y-1]=vide;
										//si mort il y a, a l'emplacement de la cle, joueur spawnera
										gestion_personnage.position_spawn.x=pos_cle.x;
										gestion_personnage.position_spawn.y=pos_cle.y;
										printf("cle prise\n");
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										sauvegarde_map(matrice,level,gestion_personnage);
										break;
									case coffre:
										if(gestion_personnage.position_spawn.x!=pos_cle.x && gestion_personnage.position_spawn.y!=pos_cle.y){
											pos_personnage.y--; //personnage ne bouge pas
											printf("veuillez prendre la cle\n");
										}
										else{
											matrice[pos_personnage.x][pos_personnage.y-1]=vide;
											gestion_personnage.position_spawn.x=pos_coffre.x;
											gestion_personnage.position_spawn.y=pos_coffre.y;
											printf("coffre pris\n");
											matrice[pos_personnage.x][pos_personnage.y]=hero;
											matrice[pos_init.x][pos_init.y]=sortie;
											sauvegarde_map(matrice,level,gestion_personnage);
										}
										break;
									case bonus:
										matrice[pos_personnage.x][pos_personnage.y-1]=vide;
										gestion_personnage.score_bonus=gestion_personnage.score_bonus+20;
										matrice[pos_personnage.x][pos_personnage.y]=hero;
										break;
									case piege:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_agressif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_defensif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case monstre_inactif:
										spawn_death(matrice,&gestion_personnage,&pos_personnage);
										break;
									case sortie:
										niveau_termine=1;
										break;
									default:
										break;
								}
								generation_mob_suivante(matrice,pos_personnage);
								afficher_matrice(matrice);
							}
							break;
			}
		}
		//perdu, message de fin
		if(niveau_termine==1) game_win(matrice);
		else game_over(matrice);
	}
}
