#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "map.h"
#include "couleur.h"

/*****************************************************************/
/*Creer une pièce de taille hauteur*largeur à partir du point de coordonnées(x,y)
chaque x,i,hauteur sont liés et chaque y,j,largeur sont liés
Créer une pièce du Nord-Ouest au Sud-Est*/
void piece(int hauteur, int largeur, char matrice[N][M],int pt_x, int pt_y){
	int i,j;
	for(i=pt_x;i<hauteur+pt_x && i<N-1;i++){
		for(j=pt_y;j<largeur+pt_y && j<M-1;j++){
			matrice[i][j]=' ';
		}
	}
}
/*creer un couloir de taille L dans une direction donnée à partir du point de coordonnées(x,y)*/
void couloir(int longueur, t_direction direction,char matrice[N][M],int pt_x, int pt_y){
	if(direction==nord) piece(longueur,1,matrice,pt_x-longueur,pt_y);
	if(direction==sud) piece(longueur,1,matrice,pt_x,pt_y);
	if(direction==ouest) piece(1,longueur,matrice,pt_x,pt_y-longueur);
	if(direction==est) piece(1,longueur,matrice,pt_x,pt_y);
}

/*****************************************************************/
/*fonction init_matrice qui remplie la matrice de mur*/
void init_matrice(char matrice[N][M]){
	//declaration
	int i,j;
	for(i=0; i<N; i++) {
        	for(j=0; j<M; j++) {
           		matrice[i][j]='X';
       		}
	}
}

/***************************************************************/

void generer_matrice(char matrice[N][M]){
	int positionD_x;
	int positionD_y;
	int positionA_x;
	int positionA_y;
	int taille_largeur_piece;
	int taille_longueur_piece;
	int compteur_piece=0;
	t_emplacement tab[4];
	srand(time(NULL));

	//random pour connaitre la position de départ de la génération de la matrice
	positionD_x=rand()%N-2;
	positionD_y=rand()%M-2;
	
	//random pour connaitre la largeur et la longueur de la pièce(limitée à 3*3cases minimum et 10*10cases maximum)
	taille_largeur_piece=rand()%7+3;
	taille_longueur_piece=rand()%7+3;
	while(positionD_x+taille_longueur_piece>N-2 || positionD_y+taille_largeur_piece>M-2 || positionD_x<1 || positionD_y<1){
		positionD_x=rand()%N-2;
		positionD_y=rand()%M-2;
		taille_largeur_piece=rand()%7+2;
		taille_longueur_piece=rand()%7+2;
	}
	//création pièce avec les infos récoltées précédemment
	piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD_x,positionD_y);
	positionA_x=positionD_x+taille_longueur_piece;
	positionA_y=positionD_y+taille_largeur_piece;
	tab[0].positionD_x=positionD_x;
	tab[0].positionA_x=positionA_x;
	tab[0].positionD_y=positionD_y;
	tab[0].positionA_y=positionA_y;
	
	while(compteur_piece<3){
		//random pour connaitre la position de départ de la génération de la matrice
		positionD_x=rand()%N-2;
		positionD_y=rand()%M-2;
	
		//random pour connaitre la largeur et la longueur de la pièce(limitée à 3*3cases minimum et 10*10cases maximum)
		taille_largeur_piece=rand()%7+3;
		taille_longueur_piece=rand()%7+3;
		while(positionD_x+taille_longueur_piece>N-2 || positionD_y+taille_largeur_piece>M-2 || positionD_x<1 || positionD_y<1){
			positionD_x=rand()%N-2;
			positionD_y=rand()%M-2;
			taille_largeur_piece=rand()%7+2;
			taille_longueur_piece=rand()%7+2;
		}
		//création pièce avec les infos récoltées précédemment
		piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD_x,positionD_y);
		positionA_x=positionD_x+taille_longueur_piece;
		positionA_y=positionD_y+taille_largeur_piece;

		compteur_piece++;
	}
	
}

/*****************************************************************/
/*fonction afficher_matrice */
void afficher_matrice(char matrice[N][M]){
    //declaration
  	int i;
   	int j;
   	int a;

   	printf("\t");
    	//ligne du dessus
   	for(i=0;i<N;i++){
        printf("+");
        for(a=0;a<M;a++){
            printf("-+");
        }
        printf("\n\t|");
        for(j=0;j<M;j++){
            printf("%c|",matrice[i][j]);
        }
        printf("\n\t");
    }
    //ligne du bas
    printf("+");
    for(a=0;a<M;a++){
        printf("-+");
    }
    printf("\n");
}