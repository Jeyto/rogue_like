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
	afficher_matrice(matrice);
	sauvegarde_map(matrice,level);
}

/*Fonction jeu
*Gere le jeu en lui-meme
*/
void jeu(t_case matrice[N][M], int level){
	//declaration
	int i,j;
	char dep;
	t_coord personnage;
	t_personnage gestion_personnage;
	gestion_personnage.PV=3; //3 vie au depart    													 //stocker la valeur dans la save
	gestion_personnage.score_bonus=0; //bonus=0;
	
	//traitement
	if(level>=1){
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				if(matrice[i][j]==hero){
					personnage.x=i;
					personnage.y=j;
				}
			}
		}
		while(matrice[personnage.x][personnage.y]==hero){
			scanf("%c",&dep);
			switch(dep){
				case 'z':	
							if(matrice[personnage.x-1][personnage.y]==vide || matrice[personnage.x-1][personnage.y]==couloir || matrice[personnage.x-1][personnage.y]==porte){
								matrice[personnage.x][personnage.y]=vide;
								personnage.x--;
								matrice[personnage.x][personnage.y]=hero;
								sauvegarde_map(matrice,level);
								generation_mob_suivante(matrice,personnage,&gestion_personnage);
								afficher_matrice(matrice);
							}
							break;
				case 'q':	if(matrice[personnage.x][personnage.y-1]==vide || matrice[personnage.x][personnage.y-1]==couloir || matrice[personnage.x][personnage.y-1]==porte){
								matrice[personnage.x][personnage.y]=vide;
								personnage.y--;
								matrice[personnage.x][personnage.y]=hero;
								sauvegarde_map(matrice,level);
								generation_mob_suivante(matrice,personnage,&gestion_personnage);
								afficher_matrice(matrice);
							}
							break;
				case 's':	if(matrice[personnage.x+1][personnage.y]==vide || matrice[personnage.x+1][personnage.y]==couloir || matrice[personnage.x+1][personnage.y]==porte){
								matrice[personnage.x][personnage.y]=vide;
								personnage.x++;
								matrice[personnage.x][personnage.y]=hero;
								sauvegarde_map(matrice,level);
								generation_mob_suivante(matrice,personnage,&gestion_personnage);
								afficher_matrice(matrice);
							}
							break;
				case 'd':	if(matrice[personnage.x][personnage.y+1]==vide || matrice[personnage.x][personnage.y+1]==couloir || matrice[personnage.x][personnage.y+1]==porte){
								matrice[personnage.x][personnage.y]=vide;
								personnage.y++;
								matrice[personnage.x][personnage.y]=hero;
								sauvegarde_map(matrice,level);
								generation_mob_suivante(matrice,personnage,&gestion_personnage);
								afficher_matrice(matrice);
							}
							break;
			
			}
			//usleep(500000);
		}
		if(matrice[personnage.x][personnage.y]==monstre_agressif || matrice[personnage.x][personnage.y]==monstre_defensif || matrice[personnage.x][personnage.y]==monstre_inactif || matrice[personnage.x][personnage.y]==piege){
			game_over(matrice);
		}
	}
}
/*Fonction game_over
*Modifie la matrice de jeu et affiche le message "game over"
*/
void game_over(t_case matrice[N][M]){	
	int i=0;
	int j=0;
	FILE * fichier;
	fichier=fopen("map_game_over.txt","r");
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
