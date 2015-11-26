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
	int taille_largeur_piece;
	int taille_longueur_piece;
	t_direction cote;
	int taille_longueur_couloir;

	srand(time(NULL));
	//random pour connaitre la position de départ de la génération de la matrice
	positionD_x=rand()%N;
	positionD_y=rand()%M;
	
	//random pour connaitre la largeur et la longueur de la pièce(limitée à 3*3cases minimum et 15*15cases maximum)
	taille_largeur_piece=rand()%13+3;
	taille_longueur_piece=rand()%13+3;
	while(positionD_x+taille_longueur_piece>N-2 || positionD_y+taille_largeur_piece>M-2 || positionD_x<1 || positionD_x>N-2 || positionD_y<1 || positionD_y>M-2){
		positionD_x=rand()%N;
		positionD_y=rand()%M;
		taille_largeur_piece=rand()%13+2;
		taille_longueur_piece=rand()%13+2;
	}

	//création pièce avec les infos récoltées précédemment
	piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD_x,positionD_y);

	//random pour connaitre le coté de la pièce où partira le couloir
	cote=rand()%4;
	//random pour connaitre la longueur du couloir(limité à 2*1cases minimum et 10*1cases maximum)
	taille_longueur_couloir=rand()%8+2;
	//création couloir à coté de la pièce précédente en vérifiant que le couloir peut être placé(minimum 2 cases de libres autour)
	switch(cote){
		case nord:
			positionD_x=positionD_x;
			positionD_y=positionD_y+(taille_largeur_piece/2);
			if(positionD_x>2){			
				while(positionD_x-taille_longueur_couloir<1){
					taille_longueur_couloir=rand()%8+2;
				}
				couloir(taille_longueur_couloir,nord,matrice,positionD_x,positionD_y);
			}
			break;
		case sud:
			positionD_x=positionD_x+taille_longueur_piece;
			positionD_y=positionD_y+(taille_largeur_piece/2);
			if(positionD_x<N-2){
				while(positionD_x+taille_longueur_couloir>N-2){
					taille_longueur_couloir=rand()%8+2;
				}
				couloir(taille_longueur_couloir,sud,matrice,positionD_x,positionD_y);
			}
			break;
		case ouest:
			positionD_x=positionD_x+(taille_longueur_piece/2);
			positionD_y=positionD_y;
			if(positionD_y>2){
				while(positionD_y-taille_longueur_couloir<1){
					taille_longueur_couloir=rand()%8+2;
				}
				couloir(taille_longueur_couloir,ouest,matrice,positionD_x,positionD_y);
			}
			break;
		case est:
			positionD_x=positionD_x+(taille_longueur_piece/2);
			positionD_y=positionD_y+taille_largeur_piece;
			if(positionD_y<M-2){
				while(positionD_y+taille_longueur_couloir>M-2){
					taille_longueur_couloir=rand()%8+2;
				}
				couloir(taille_longueur_couloir,est,matrice,positionD_x,positionD_y);
			}
			break;
	}
	printf("\n dir %i",cote);
	printf("\n dir %i",taille_longueur_couloir);
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
