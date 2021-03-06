/**
    *\file IA.c
    *\brief Fonctions gerant les deplacements et les interactions des monstres
    *\author PAVARD Valentin Gerbault Maxime Decrand Baptiste
    *\version 2.0
    *\date 17/12/2015
    *\fn int recherche_chemin_monstre_agr(t_case grille[N][M],t_coord depart,t_coord arrive)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		t_coord depart est le point de depart lors de la recherche du chemin(position du monstre)
    		t_coord arrive est le point d'arrivee de la recherche(position du hero)
    *\brief Recherche un chemin si il est trouve le monstre agr se deplace d'une case
    *\return 1 quand le chemin est trouve 0 sinon
    *\fn int recherche_chemin_monstre_def(t_case grille[N][M],t_coord depart,t_coord arrive)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		t_coord depart est le point de depart lors de la recherche du chemin(position du monstre)
    		t_coord arrive est le point d'arrivee de la recherche(position du hero)
    *\brief Recherche un chemin si il est trouve le monstre def se deplace d'une case
    *\return 1 quand le chemin est trouve 0 sinon
    *\fn void permutation_monstre_agr(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		t_coord pos_ini est la position initiale du monstre
    		t_coord pos_arr est la position visée du monstre
    *\brief Deplace le monstre vers la case pos_arr si cela est possible
    *\return void
    *\fn void permutation_monstre_def(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		t_coord pos_ini est la position initiale du monstre
    		t_coord pos_arr est la position visée du monstre
    *\brief Deplace le monstre vers la case pos_arr si cela est possible
    *\return void
    *\fn void permutation_monstre_alea(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		t_coord pos_ini est la position initiale du monstre
    		t_coord pos_arr est la position visée du monstre
    *\brief Deplace le monstre vers la case pos_arr si cela est possible
    *\return void
    *\fn void chemin_aleatoire(t_case grille[N][M],t_coord depart)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		t_coord depart est la position du monstre
    *\brief genere une direction aleatoire autour du monstre et le deplace
    *\return void
     *\fn void generation_mob_suivante(t_case grille[N][M],t_coord personnage)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		t_coord personnage est la position du personnage à attaquer
    *\brief Pour chaque monstres de la liste on les deplacent d'une case
    *\return void
*/

#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "IA.h"
#include "jeu.h"
#include "liste_mob.h"
#include "structure.h"
#include "personnage.h"

/*Fonctions generant le deplacement prochain d'un monstre agressif*/
/***********************************************************************/
/*Fonction recherche_chemin_monstre_agr
* recherche un chemin si il est trouve le monstre agr se deplace d'une case
*renvoie 1 quand le chemin est trouve 0 sinon
*/
int recherche_chemin_monstre_agr(t_case grille[N][M],t_coord depart,t_coord arrive){
	int tab_longueur[N][M];
	int i,j;
	int chemin_trouve=0;
	int maj = 1; //Au debut, pas de chemin trouve
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
				/*les cases parcourables sont nommes -1*/
				if(grille[i][j]==vide || grille[i][j]==couloir || grille[i][j]==porte || grille[i][j]==monstre_agressif  || grille[i][j]==monstre_defensif){
					tab_longueur[i][j]=-1;
				}
				/*les non parcourables sont nommes -2*/
				else tab_longueur[i][j]=-2;
		}
	}
	tab_longueur[depart.x][depart.y]=0;
	tab_longueur[arrive.x][arrive.y]=-1;
	/*Tant que l'arrive n'est pas atteinte ou que l'on ne trouve pas de chemin*/
	while(tab_longueur[arrive.x][arrive.y]==-1 && maj==1){
		maj = 0; //au depart, aucune case -1 modifie
		/*On parcourt la grille*/
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				/*Et si une case non parcouru  */
				if(tab_longueur[i][j]==-1){
					/*contient un ou des voisins parcouru alors sa valeur est la plus petite parmis ses voisins + 1*/
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
						maj = 1; /*Un chemin a ete trouve*/
					}
				}
			}
		}
	}

	if(tab_longueur[arrive.x][arrive.y]!=-1){ //on a trouve un chemin, on fait avancer le monstre sur la prochaine case
		chemin_trouve = 1;
		/*Recuperation du chemin*/
		i=arrive.x;
		j=arrive.y;
		//afficher_chemin(tab_longueur);
		while(tab_longueur[i][j]!=1){
			/*Recherche des coordonnees de la prochaine coordonnee*/
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
/*************************************************************************/
/*Fonction recherche_chemin_monstre_def
* recherche un chemin si il est trouve le monstre def se deplace d'une case
*renvoie 1 quand le chemin est trouve 0 sinon
*/
int recherche_chemin_monstre_def(t_case grille[N][M],t_coord depart,t_coord arrive){
	int tab_longueur[N][M];
	int i,j;
	int chemin_trouve=0;
	int maj = 1; //Au debut, pas de chemin trouve
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
				/*les chemins sont nommes -1*/
				if(grille[i][j]==vide || grille[i][j]==couloir || grille[i][j]==monstre_agressif  || grille[i][j]==monstre_defensif){
					tab_longueur[i][j]=-1;
				}
				/*les murs sont nommes -2*/
				else tab_longueur[i][j]=-2;
		}
	}
	tab_longueur[depart.x][depart.y]=0;
	tab_longueur[arrive.x][arrive.y]=-1;
	while(tab_longueur[arrive.x][arrive.y]==-1 && maj==1){
		maj = 0; //au depart, aucune case  -1 modifiee
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

	if(tab_longueur[arrive.x][arrive.y]!=-1){ //on a trouve un chemin, on fait avancer le monstre sur la prochaine case
		chemin_trouve = 1;
		/*Recuperation du chemin*/
		i=arrive.x;
		j=arrive.y;
		//afficher_chemin(tab_longueur);
		while(tab_longueur[i][j]!=1){
			/*Recherche des coordonnees de la prochaine coordonnee*/
			if(i-1>=0 && tab_longueur[i-1][j]==tab_longueur[i][j]-1) i--;
			else if(i+1<N && tab_longueur[i+1][j]==tab_longueur[i][j]-1) i++;
			else if(j-1>=0 && tab_longueur[i][j-1]==tab_longueur[i][j]-1) j--;
			else if(j+1<M && tab_longueur[i][j+1]==tab_longueur[i][j]-1) j++;
		}
		arrive.x=i;
		arrive.y=j;
		permutation_monstre_def(grille,depart,arrive);
	}

	return chemin_trouve;
}

/**********************************************************************/
/*fonction permutation_monstre_agr
*Deplace le monstre vers la case pos_arr si cela est possible
*/
void permutation_monstre_agr(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr){
	t_case tampon;
	t_mob mob;
	valeur_mob(&mob);
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
		case monstre_defensif:
		case monstre_inactif:
			break;
			/*Si le monstre se dirige vers un porte celui-ci passe derriere*/
		case porte:
			if(pos_ini.x==pos_arr.x){
				if(pos_arr.y==pos_ini.y-1){
					pos_arr.y--;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_mob(mob);
				}
				else if(pos_arr.y==pos_ini.y+1){
					pos_arr.y++;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_mob(mob);
				}
			}
			else if(pos_ini.y==pos_arr.y){
				if(pos_arr.x==pos_ini.x-1){
					pos_arr.x--;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_mob(mob);
				}
				else if(pos_arr.x==pos_ini.x+1){
					pos_arr.x++;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_mob(mob);
				}
			}
			break;
		case hero:
			if(!rand()%4)
				degat_personnage();
			break;
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;
			mob.position.x=pos_arr.x;
			mob.position.y=pos_arr.y;
			modif_mob(mob);
			break;
	}

}
/*********************************************************************/
/*fonction permutation_monstre_def
*Deplace le monstre vers la case pos_arr si cela est possible
*/
void permutation_monstre_def(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr){
	t_case tampon;
	t_mob mob;
	valeur_mob(&mob);
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
			break;
		case monstre_defensif:
			break;
		case monstre_inactif:
			break;
		case hero:
			degat_personnage();
		break;
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;
			mob.position.x=pos_arr.x;
			mob.position.y=pos_arr.y;
			modif_mob(mob);
			break;
	}

}
/**************************************************************/
/*fonction permutation_monstre_alea
*Deplace le monstre vers la case pos_arr si cela est possible
*/
void permutation_monstre_alea(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr){
	t_case tampon;
	t_mob mob;
	valeur_mob(&mob);
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
		case monstre_defensif:
		case monstre_inactif:
		case mur_contour:
		case mur:
		case porte:
		case coffre:
		case cle:
			break;
		/*Si un monstre se deplace aleatoirement sur un bonus ce bonus devient un monstre de type defensif*/
		case bonus:
			grille[pos_arr.x][pos_arr.y]=monstre_defensif;
			mob.position=pos_arr;
			mob.race_mob=monstre_defensif;
			mob.PV=1;
			ajout_gauche(mob);
			break;
		/*Si un monstre se deplace aleatoirement sur un piege le monstre perd un PV*/
		case piege:
			mob_perte_PV(grille,1);
			break;
		/*Si un monstre se deplace aleatoirement vers un hero celui-ci perd un PV*/
		case hero:
			degat_personnage();
			break;
		/*Le monstre se deplace vers la direction*/
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;
			mob.position.x=pos_arr.x;
			mob.position.y=pos_arr.y;
			modif_mob(mob);
			break;
	}
}
/*******************************************************/
/*Fonction chemin_aleatoire
*genere une direction aleatoire autour du monstre et le deplace
*/
void chemin_aleatoire(t_case grille[N][M],t_coord depart){
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
		permutation_monstre_alea(grille,depart,arrive);


}
/*****************************************************/
/*Fonction generation_mob_suivante
*Pour chaque monstres de la liste on les deplacent d'une case
*/
void generation_mob_suivante(t_case grille[N][M],t_coord personnage){
	t_mob mob;
	en_tete();
	/*On recupere les monstres */
  while(!hors_liste_mob()){
		valeur_mob(&mob);
		switch(mob.race_mob){
			// les monstres agressifs se deplacent vers le personnage
			case monstre_agressif:
				recherche_chemin_monstre_agr(grille,mob.position,personnage);
				break;
			// les monstres defensifs se deplacent vers le personnage si possible sinon 
			case monstre_defensif:
				if(recherche_chemin_monstre_def(grille,mob.position,personnage));
				else chemin_aleatoire(grille,mob.position);
				break;
			case monstre_inactif:
				chemin_aleatoire(grille,mob.position);
				break;
			default: break;

		}
		suivant();
	}
}
