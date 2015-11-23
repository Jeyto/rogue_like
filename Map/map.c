#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "map.h"
#include "couleur.h"

/*****************************************************************/
/*Creer une pièce de taille H*L à partir du point de coordonnées(x,y)
chaque x,i,H sont liés et chaque y,j,L sont liés
Créer une pièce du Nord-Ouest au Sud-Est*/
void piece(int H, int L, char matrice[N][M],int x, int y){
	int i,j;
	for(i=x;i<H+x;i++){
		for(j=y;j<L+y;j++){
			matrice[i][j]=' ';
		}
	}
}
/*creer un couloir de taille L dans une direction donnée à partir du point de coordonnées(x,y)*/
void couloir(int L, t_direction direction,char matrice[N][M],int x, int y){
	if(direction==nord) piece(L,1,matrice,x-L,y);
	if(direction==sud) piece(L,1,matrice,x,y);
	if(direction==ouest) piece(1,L,matrice,x,y-L);
	if(direction==est) piece(1,L,matrice,x,y);
}

/*****************************************************************/
/*fonction init_matrice*/
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
	piece(10,10,matrice,0,0);
	piece(10,8,matrice,20,20);
	couloir(10,nord,matrice,20,20);
	couloir(10,sud,matrice,20,20);
	couloir(10,ouest,matrice,20,20);
	couloir(10,est,matrice,20,20);
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
