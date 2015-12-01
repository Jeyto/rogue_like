#include <stdio.h>
#include <assert.h>
#include "../include/IA.h"
#include "../include/struct.h"
#include "../include/liste_ptr_coord.h"
/*Fonctions generant le deplacement prochain d'un monstre agressif*/
/*http://www.maths-algo.fr/algo/exercices/grille_plus_court_chemin.htm*/

/*affiche la grille chemin*/
void afficher_grille(t_cellule grille[N][M]){
	int i,j;
	for(i=0;i<N;i++){
		printf("\n");
		for(j=0;j<M;j++){
			switch(grille[i][j]){
				case 0:
					printf(" ");
					break;
				case 1:
					printf("X");
					break;
				case 2:printf("P");
					break;
				case 3:printf("M");
					break;
			}
		}
	}
	printf("\n");
}
int chemin_possible(t_cellule grille[N][M],t_coord a,t_coord b){
	int grille_zone[N][M];
	int i,j,k=1;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(grille[i][j]==0) {
				grille_zone[i][j]=k;
				k++;
			}
			else grille_zone[i][j]=0;
		}
	}
	grille_zone[a.x][a.y]=N*M;
	grille_zone[b.x][b.y]=N*M;
	k=0;
	while(k<N*M){
		k++;
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				if(grille_zone[i][j]!=0){
					if(grille_zone[i-1][j]>grille_zone[i][j]) grille_zone[i-1][j]=grille_zone[i][j];
					else if(grille_zone[i+1][j]>grille_zone[i][j]) grille_zone[i+1][j]=grille_zone[i][j];
					else if(grille_zone[i][j-1]>grille_zone[i][j]) grille_zone[i][j-1]=grille_zone[i][j];
					else if(grille_zone[i][j+1]>grille_zone[i][j]) grille_zone[i][j+1]=grille_zone[i][j];
				}
				
			}
		}
	}
	//printf("\nAffichage de la zone:");
	//afficher_chemin(grille_zone);
	if(grille_zone[a.x][a.y]==grille_zone[b.x][b.y])return 1;
	else return 0;
}

void afficher_chemin(int grille[N][M]){
	int i,j;
	for(i=0;i<N;i++){
		printf("\n");
		for(j=0;j<M;j++){
			if(grille[i][j]==-2) printf("X");
			else printf("%d",grille[i][j]);
		}
	}
	printf("\n");
}

/*fonction permutant 2 objets de la grille*/
void permutation(t_cellule grille[N][M],t_coord pos_ini,t_coord pos_arr){
	int tampon=grille[pos_arr.x][pos_arr.y];
	grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
	grille[pos_ini.x][pos_ini.y]=tampon;
}

/*Affiche la recherche du plus court chemin*/
void recherche_chemin(t_cellule grille[N][M],t_coord depart,t_coord arrive){
	int tab_longueur[N][M];
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
				if(grille[i][j]!=mur){
					tab_longueur[i][j]=-1;
				}
				else tab_longueur[i][j]=-2;
		}
	}
	tab_longueur[depart.x][depart.y]=0;
	while(tab_longueur[arrive.x][arrive.y]==-1){
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				if(tab_longueur[i][j]==-1){
					int valeur=0;
					int valeur_min=N*M;
					if(tab_longueur[i-1][j]>=0 && valeur_min>tab_longueur[i-1][j]) 
						valeur_min=tab_longueur[i-1][j];
					if(tab_longueur[i+1][j]>=0 && valeur_min>tab_longueur[i+1][j]) 
						valeur_min=tab_longueur[i+1][j];
					if(tab_longueur[i][j-1]>=0 && valeur_min>tab_longueur[i][j-1]) 
						valeur_min=tab_longueur[i][j-1];
					if(tab_longueur[i][j+1]>=0 && valeur_min>tab_longueur[i][j+1]) 
						valeur_min=tab_longueur[i][j+1];

					if(valeur_min==tab_longueur[i-1][j]) 
						valeur=tab_longueur[i-1][j]+1;
					else if(valeur_min==tab_longueur[i+1][j]) 
						valeur=tab_longueur[i+1][j]+1;
					else if(valeur_min==tab_longueur[i][j-1]) 
						valeur=tab_longueur[i][j-1]+1;
					else if(valeur_min==tab_longueur[i][j+1]) 
						valeur=tab_longueur[i][j+1]+1;
					if(valeur!=0) 
						tab_longueur[i][j]=valeur;
				}
			}
		}	
	}
	//printf("\nAffichage du chemin");
	//afficher_chemin(tab_longueur);
	/*Recuperation du chemin*/
	i=arrive.x;
	j=arrive.y;
	while(tab_longueur[i][j]!=1){
		/*Recherche des coordonnées de la prochaine coordonnée*/
		if(i-1>=0 && tab_longueur[i-1][j]==tab_longueur[i][j]-1) i--;
		else if(i+1<N && tab_longueur[i+1][j]==tab_longueur[i][j]-1) i++;
		else if(j-1>=0 && tab_longueur[i][j-1]==tab_longueur[i][j]-1) j--;
		else if(j+1<M && tab_longueur[i][j+1]==tab_longueur[i][j]-1) j++;
	}
	arrive.x=i;
	arrive.y=j;
	permutation(grille,depart,arrive);
}
void vider_liste()
{	
	if(!liste_vide()){
		en_queue();//on commence en fin de liste car on utilise oter_elt() qui se positionne sur le predecesseur
		/*on enleve les elements un par un jusqu'à ce que la liste soit vide*/
		while(!hors_liste()){
			oter_elt();

		}
	}
}
int est_present(t_coord v){
	t_coord valeur;
	if(!liste_vide()){
		en_tete();
		while(!hors_liste()){
			valeur_elt(&valeur);
			if(valeur.x==v.x && valeur.y==v.y) return 1;
			suivant();
		}
	}
	return 0;
}

void generation_mob_suivante(t_cellule grille[N][M],t_coord personnage){
	t_coord coordonnee;
	init_liste();
	for(coordonnee.x=0;coordonnee.x<N;coordonnee.x++){
		for(coordonnee.y=0;coordonnee.y<M;coordonnee.y++){
			//printf("\nX=%d,Y=%d",coordonnee.x,coordonnee.y);
			if(grille[coordonnee.x][coordonnee.y]==ennemi && !est_present(coordonnee) && chemin_possible(grille,personnage,coordonnee)){
				recherche_chemin(grille,coordonnee,personnage);
				en_queue();
				ajout_droit(coordonnee);
			}
		}
	}
	vider_liste();
}

