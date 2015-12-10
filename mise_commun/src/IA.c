#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "../include/IA.h"
#include "../include/structure.h"
#include "../include/liste_ptr_coord.h"
#include "../include/map.h"
#include "../include/couleur.h"
/*Fonctions generant le deplacement prochain d'un monstre agressif*/
/*http://www.maths-algo.fr/algo/exercices/grille_plus_court_chemin.htm*/


void afficher_chemin(int grille[N][M]){
	int i,j;
	for(i=0;i<N;i++){
		printf("\n");
		for(j=0;j<M;j++){
			if(grille[i][j]==-2) printf("X");
			else if (grille[i][j]==-1) printf("0");
			else  printf("t");
		}
	}
	printf("\n");
}



/*
* renvoie vrai si chemin trouvé, faux sinon
*/
int recherche_chemin_monstre_agr(t_case grille[N][M],t_coord depart,t_coord arrive){
	int tab_longueur[N][M];
	int i,j;
	int chemin_trouve=0;
	int maj = 1; //Au début, pas de chemin trouvé
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
				/*les chemins sont nommés -1*/
				if(grille[i][j]==vide || grille[i][j]==couloir || grille[i][j]==porte || grille[i][j]==monstre_agressif  || grille[i][j]==monstre_defensif){
					tab_longueur[i][j]=-1;
				}
				/*les murs sont nommés -2*/
				else tab_longueur[i][j]=-2;
		}
	}
	tab_longueur[depart.x][depart.y]=0;
	tab_longueur[arrive.x][arrive.y]=-1;
	while(tab_longueur[arrive.x][arrive.y]==-1 && maj==1){
		maj = 0; //au départ, aucune case à -1 modifiée
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				if(tab_longueur[i][j]==-1){
					int valeur_min=N*M;
					if(tab_longueur[i-1][j]>=0 && valeur_min>tab_longueur[i-1][j]) 
						valeur_min=tab_longueur[i-1][j];
					if(tab_longueur[i+1][j]>=0 && valeur_min>tab_longueur[i+1][j]) 
						valeur_min=tab_longueur[i+1][j];
					if(tab_longueur[i][j-1]>=0 && valeur_min>tab_longueur[i][j-1]) 
						valeur_min=tab_longueur[i][j-1];
					if(tab_longueur[i][j+1]>=0 && valeur_min>tab_longueur[i][j+1]) 
						valeur_min=tab_longueur[i][j+1];

					if(valeur_min!=N*M){
						tab_longueur[i][j]=valeur_min+1;
						maj = 1; //maj d'une case
					}
				}
			}
		}
	}
	
	if(tab_longueur[arrive.x][arrive.y]!=-1){ //on a trouvé un chemin, on fait avancer le monstre sur la prochaine case
		chemin_trouve = 1;
		/*Recuperation du chemin*/
		i=arrive.x;
		j=arrive.y;
		//afficher_chemin(tab_longueur);
		while(tab_longueur[i][j]!=1){
			/*Recherche des coordonnées de la prochaine coordonnée*/
			if(i-1>=0 && tab_longueur[i-1][j]==tab_longueur[i][j]-1) i--;
			else if(i+1<N && tab_longueur[i+1][j]==tab_longueur[i][j]-1) i++;
			else if(j-1>=0 && tab_longueur[i][j-1]==tab_longueur[i][j]-1) j--;
			else if(j+1<M && tab_longueur[i][j+1]==tab_longueur[i][j]-1) j++;
		}
		arrive.x=i;
		arrive.y=j;
		permutation_monstre_agr(grille,depart,arrive);
	} 
	
	return chemin_trouve;
}

int recherche_chemin_monstre_def(t_case grille[N][M],t_coord depart,t_coord arrive){
	int tab_longueur[N][M];
	int i,j;
	int chemin_trouve=0;
	int maj = 1; //Au début, pas de chemin trouvé
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
				/*les chemins sont nommés -1*/
				if(grille[i][j]==vide || grille[i][j]==couloir || grille[i][j]==monstre_agressif  || grille[i][j]==monstre_defensif){
					tab_longueur[i][j]=-1;
				}
				/*les murs sont nommés -2*/
				else tab_longueur[i][j]=-2;
		}
	}
	tab_longueur[depart.x][depart.y]=0;
	tab_longueur[arrive.x][arrive.y]=-1;
	while(tab_longueur[arrive.x][arrive.y]==-1 && maj==1){
		maj = 0; //au départ, aucune case à -1 modifiée
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				if(tab_longueur[i][j]==-1){
					int valeur_min=N*M;
					if(tab_longueur[i-1][j]>=0 && valeur_min>tab_longueur[i-1][j]) 
						valeur_min=tab_longueur[i-1][j];
					if(tab_longueur[i+1][j]>=0 && valeur_min>tab_longueur[i+1][j]) 
						valeur_min=tab_longueur[i+1][j];
					if(tab_longueur[i][j-1]>=0 && valeur_min>tab_longueur[i][j-1]) 
						valeur_min=tab_longueur[i][j-1];
					if(tab_longueur[i][j+1]>=0 && valeur_min>tab_longueur[i][j+1]) 
						valeur_min=tab_longueur[i][j+1];

					if(valeur_min!=N*M){
						tab_longueur[i][j]=valeur_min+1;
						maj = 1; //maj d'une case
					}
				}
			}
		}
	}
	
	if(tab_longueur[arrive.x][arrive.y]!=-1){ //on a trouvé un chemin, on fait avancer le monstre sur la prochaine case
		chemin_trouve = 1;
		/*Recuperation du chemin*/
		i=arrive.x;
		j=arrive.y;
		//afficher_chemin(tab_longueur);
		while(tab_longueur[i][j]!=1){
			/*Recherche des coordonnées de la prochaine coordonnée*/
			if(i-1>=0 && tab_longueur[i-1][j]==tab_longueur[i][j]-1) i--;
			else if(i+1<N && tab_longueur[i+1][j]==tab_longueur[i][j]-1) i++;
			else if(j-1>=0 && tab_longueur[i][j-1]==tab_longueur[i][j]-1) j--;
			else if(j+1<M && tab_longueur[i][j+1]==tab_longueur[i][j]-1) j++;
		}
		arrive.x=i;
		arrive.y=j;
		permutation_monstre_agr(grille,depart,arrive);
	} 
	
	return chemin_trouve;
}


/*fonction permutant 2 objets de la grille*/
void permutation_monstre_agr(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr){
	t_case tampon;
	en_tete();
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
			ajout_droit(pos_ini);
			break;
		case monstre_defensif:
			ajout_droit(pos_ini);
			break;
		case monstre_inactif:
			ajout_droit(pos_ini);
			break;
		case porte:
			if(pos_ini.x==pos_arr.x){
				if(pos_arr.y==pos_ini.y-1){
					pos_arr.y--;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;

					ajout_droit(pos_arr);
				}
				else if(pos_arr.y==pos_ini.y+1){
					pos_arr.y++;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
				
					ajout_droit(pos_arr);
				}
			}
			else if(pos_ini.y==pos_arr.y){
				if(pos_arr.x==pos_ini.x-1){
					pos_arr.x--;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;

					ajout_droit(pos_arr);
				}
				else if(pos_arr.x==pos_ini.x+1){
					pos_arr.x++;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;

					ajout_droit(pos_arr);
				}
			}			
			break;
		case hero:
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=vide;
			ajout_droit(pos_arr);
			break;		
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;

			ajout_droit(pos_arr);
			break;
	}
	
}


void permutation_monstre_def(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr){
t_case tampon;
	en_tete();
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
			ajout_droit(pos_ini);
			break;
		case monstre_defensif:
			ajout_droit(pos_ini);
			break;
		case monstre_inactif:
			ajout_droit(pos_ini);
			break;
		case hero:
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=vide;
			ajout_droit(pos_arr);
			break;	
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;

			ajout_droit(pos_arr);
			break;
	}
	
}
void chemin_aleatoire(t_case grille[N][M],t_coord depart){
	srand(time(NULL));
	int nbr_alea;
	nbr_alea=rand()%4;
	t_coord arrive;
	switch (nbr_alea){
		case 0:
			arrive.x=depart.x+1;
			arrive.y=depart.y;
			break;
		case 1:
			arrive.x=depart.x-1;
			arrive.y=depart.y;
			break;	
		case 2:
			arrive.x=depart.x;
			arrive.y=depart.y+1;
			break;		
		case 3:
			arrive.x=depart.x;
			arrive.y=depart.y-1;
			break;
	}
	if(grille[arrive.x][arrive.y]==vide || grille[arrive.x][arrive.y]==couloir){
		permutation_monstre_def(grille,depart,arrive);
	}

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

void generation_mob_suivante(t_case grille[N][M],t_coord personnage){
	t_coord coordonnee;
	init_liste();
	for(coordonnee.x=0;coordonnee.x<N;coordonnee.x++){
		for(coordonnee.y=0;coordonnee.y<M;coordonnee.y++){
			if(grille[coordonnee.x][coordonnee.y]==monstre_agressif && !est_present(coordonnee)){
				// déplace le monstre vers le personnage s'il existe un chemin, ne fait rien sinon
				recherche_chemin_monstre_agr(grille,coordonnee,personnage);
			}
			else if(grille[coordonnee.x][coordonnee.y]==monstre_defensif && !est_present(coordonnee)){
				if(recherche_chemin_monstre_def(grille,coordonnee,personnage));
				else chemin_aleatoire(grille,coordonnee);
			}
			else if(grille[coordonnee.x][coordonnee.y]==monstre_inactif) chemin_aleatoire(grille,coordonnee);
		}
	}
	vider_liste();
}

