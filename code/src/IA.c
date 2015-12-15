#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "IA.h"
#include "jeu.h"
#include "liste_ptr_coord.h"
#include "structure.h"

/*Fonctions generant le deplacement prochain d'un monstre agressif*/
/*http://www.maths-algo.fr/algo/exercices/grille_plus_court_chemin.htm*/

void init_liste_mob(t_case grille[N][M]){
	t_mob valeur;
	vider_liste();
	en_tete();
	for(valeur.position.x=0;valeur.position.x<N;valeur.position.x++){
		for(valeur.position.y=0;valeur.position.y<M;valeur.position.y++){
			switch(grille[valeur.position.x][valeur.position.y]){
				/*La liste contient pour chaques monstres son type,sa position et ces PV initiales*/
				case monstre_inactif:
					valeur.race_mob=monstre_inactif;
					valeur.PV=3;
					ajout_droit(valeur);
					break;
				case monstre_agressif:
					valeur.race_mob=monstre_agressif;
					valeur.PV=1;
					ajout_droit(valeur);
					break;
				case monstre_defensif:
					valeur.race_mob=monstre_defensif;
					valeur.PV=2;
					ajout_droit(valeur);
					break;
				default: break;
			}
		}
	}
}

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
* renvoie vrai si chemin trouve, faux sinon
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

int recherche_chemin_monstre_def(t_case grille[N][M],t_coord depart,t_coord arrive){
	int tab_longueur[N][M];
	int i,j;
	int chemin_trouve=0;
	int maj = 1; //Au d�but, pas de chemin trouv�
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
				/*les chemins sont nomm�s -1*/
				if(grille[i][j]==vide || grille[i][j]==couloir || grille[i][j]==monstre_agressif  || grille[i][j]==monstre_defensif){
					tab_longueur[i][j]=-1;
				}
				/*les murs sont nomm�s -2*/
				else tab_longueur[i][j]=-2;
		}
	}
	tab_longueur[depart.x][depart.y]=0;
	tab_longueur[arrive.x][arrive.y]=-1;
	while(tab_longueur[arrive.x][arrive.y]==-1 && maj==1){
		maj = 0; //au d�part, aucune case � -1 modifi�e
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

	if(tab_longueur[arrive.x][arrive.y]!=-1){ //on a trouv� un chemin, on fait avancer le monstre sur la prochaine case
		chemin_trouve = 1;
		/*Recuperation du chemin*/
		i=arrive.x;
		j=arrive.y;
		//afficher_chemin(tab_longueur);
		while(tab_longueur[i][j]!=1){
			/*Recherche des coordonn�es de la prochaine coordonn�e*/
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
	t_mob mob;
	valeur_elt(&mob);
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
			break;
		case monstre_defensif:
			break;
		case monstre_inactif:
			break;
		case porte:
			if(pos_ini.x==pos_arr.x){
				if(pos_arr.y==pos_ini.y-1){
					pos_arr.y--;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_elt(mob);
				}
				else if(pos_arr.y==pos_ini.y+1){
					pos_arr.y++;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_elt(mob);
				}
			}
			else if(pos_ini.y==pos_arr.y){
				if(pos_arr.x==pos_ini.x-1){
					pos_arr.x--;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_elt(mob);
				}
				else if(pos_arr.x==pos_ini.x+1){
					pos_arr.x++;
					grille[pos_arr.x][pos_arr.y]=monstre_agressif;
					grille[pos_ini.x][pos_ini.y]=vide;
					mob.position.x=pos_arr.x;
					mob.position.y=pos_arr.y;
					modif_elt(mob);
				}
			}
			break;
		case hero:
			spawn_death();
			break;
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;
			mob.position.x=pos_arr.x;
			mob.position.y=pos_arr.y;
			modif_elt(mob);
			break;
	}

}

void permutation_monstre_def(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr){
	t_case tampon;
	t_mob mob;
	valeur_elt(&mob);
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
			break;
		case monstre_defensif:
			break;
		case monstre_inactif:
			break;
		case hero:
			spawn_death();
		break;
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;
			mob.position.x=pos_arr.x;
			mob.position.y=pos_arr.y;
			modif_elt(mob);
			break;
	}

}

void permutation_monstre_alea(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr){
	t_case tampon;
	t_mob mob;
	valeur_elt(&mob);
	switch(grille[pos_arr.x][pos_arr.y]){
		case monstre_agressif:
			break;
		case monstre_defensif:
			break;
		case monstre_inactif:
			break;
		case mur_contour:
			break;
		case mur:
			break;
		case porte:
			break;
		case coffre:
			break;
		case cle:
			break;
		case bonus:
			/*grille[pos_arr.x][pos_arr.y]=monstre_agressif;
			mob.position=pos_arr;
			mob.race_mob=monstre_agressif;
			mob.PV=3;
			ajout_gauche(mob);*/
			break;
		case piege:
			mob_perte_PV(grille,1);
			break;
		case hero:
			spawn_death();
			break;
		default:
			tampon=grille[pos_arr.x][pos_arr.y];
			grille[pos_arr.x][pos_arr.y]=grille[pos_ini.x][pos_ini.y];
			grille[pos_ini.x][pos_ini.y]=tampon;
			mob.position.x=pos_arr.x;
			mob.position.y=pos_arr.y;
			modif_elt(mob);
			break;
	}
}

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
int position_elt(t_coord pos){
	t_mob mob;
	if(!liste_vide()){
		en_tete();
		while(!hors_liste()){
			valeur_elt(&mob);
			if(mob.position.x==pos.x && mob.position.y==pos.y) return 1;
			suivant();
		}
	}
	return 0;
}
void mob_perte_PV(t_case grille[N][M],int perte){
	t_mob mob;
	valeur_elt(&mob);
	mob.PV=mob.PV-perte;
	if(mob.PV>0) modif_elt(mob);
	else{ 	
		grille[mob.position.x][mob.position.y]=vide;
		oter_elt();
	}
}
void generation_mob_suivante(t_case grille[N][M],t_coord personnage){
	t_mob mob;
	en_tete();
  while(!hors_liste()){
		valeur_elt(&mob);
		switch(mob.race_mob){
			case monstre_agressif:
				recherche_chemin_monstre_agr(grille,mob.position,personnage);
				break;
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
