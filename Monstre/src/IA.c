#include "../include/struct.h"
#include<stdio.h>

/*Fonctions generant le deplacement prochain d'un monstre agressif*/
/*http://www.maths-algo.fr/algo/exercices/grille_plus_court_chemin.htm*/

/**
 \fn void push(int x,int y,t_coord pile[t_max],int *sommet);
 \brief ajoute les coordonnees x,y a une pile
 \param (coordonn�e x,coordonn�e y,pile de type t_coord,sommet de la pile)
 */
void push(int x,int y,t_coord pile[t_max],int *sommet){
    if(*sommet<t_max-1){
        *sommet=*sommet+1;
        pile[*sommet].x=x;
        pile[*sommet].y=y;
    }
}

/**
 \fn void depush(int *sommet);
 \brief enleve les coordonnees x,y du sommet d'une pile
 \param (sommet de la pile)
 */
void depush(int *sommet){
    if(*sommet>-1){
        *sommet=*sommet-1;
    }
}

/**
 \fn void initpile(int *sommet);
 \brief initialise une pile
 \param (sommet de la pile)
 */
void initpile(int *sommet){
    *sommet=-1;
}

/**
 \fn int sommetpile(t_coord pile[t_max],int *sommet,t_coord *adr_coord_pile);
 \brief recupere les coordonnees du sommet d'une pile
 \param (la pile de type t_coord,sommet de la pile,les coordonn�es � indenter)
 */
void sommetpile(t_coord pile[t_max],int *sommet,t_coord *adr_coord_pile){
        if(*sommet>-1){
			adr_coord_pile->x=pile[*sommet].x;
			adr_coord_pile->y=pile[*sommet].y;
    }
}
/*affiche la grille chemin*/
void afficher(int grille[N][M]){
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
void permutation(t_cellule *grille[N][M],t_coord pos_ini,t_coord pos_arr){
	int tampon=*grille[pos_arr.x][pos_arr.y];
	*grille[pos_arr.x][pos_arr.y]=*grille[pos_ini.x][pos_ini.y];
	*grille[pos_ini.x][pos_ini.y]=tampon;
}

/*Affiche la recherche du plus court chemin*/
void recherche_chemin(t_cellule grille[N][M],t_coord depart,t_coord arrive){
	
	int tab_longueur[N][M];
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(grille[i][j]==0) tab_longueur[i][j]=-1;
			else if (grille[i][j]==1) tab_longueur[i][j]=-2;
		}
	}
	tab_longueur[depart.x][depart.y]=0;
	afficher(tab_longueur);
	while(tab_longueur[arrive.x][arrive.y]==-1){
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				if(tab_longueur[i][j]==-1){
					int valeur_min=0;
					if(tab_longueur[i-1][j]>=0) valeur_min=tab_longueur[i-1][j]+1;
					if(tab_longueur[i+1][j]>=0 && valeur_min<=tab_longueur[i+1][j]) valeur_min=tab_longueur[i+1][j]+1;
					if(tab_longueur[i][j-1]>=0 && valeur_min<=tab_longueur[i][j-1]) valeur_min=tab_longueur[i][j-1]+1;
					if(tab_longueur[i][j+1]>=0 && valeur_min<=tab_longueur[i][j+1]) valeur_min=tab_longueur[i][j+1]+1;
					if(valeur_min!=0) tab_longueur[i][j]=valeur_min;
				}
			}
		}
	afficher(tab_longueur);
	}
		
	/*Recuperation du chemin*/
	t_coord chemin_pile[t_max];
	int chemin_sommet;
	initpile(&chemin_sommet);
	i=arrive.x;
	j=arrive.y;
	while(tab_longueur[i][j]!=0){
		push(i,j,chemin_pile,&chemin_sommet);
		/*Recherche des coordonn�es de la prochaine coordonn�e*/
		if(tab_longueur[i-1][j]==tab_longueur[i][j]-1) i--;
		else if(tab_longueur[i+1][j]==tab_longueur[i][j]-1 ) i++;
		else if(tab_longueur[i][j-1]==tab_longueur[i][j]-1) j--;
		else if(tab_longueur[i][j+1]==tab_longueur[i][j]-1) j++;
	}
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(grille[i][j]==0) tab_longueur[i][j]=0;
			else if (grille[i][j]==2) tab_longueur[i][j]=1;
			else if (grille[i][j]==1) tab_longueur[i][j]=-2;
		}
	}
	afficher(tab_longueur);
}
