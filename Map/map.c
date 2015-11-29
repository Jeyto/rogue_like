#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "map.h"
#include "couleur.h"


/*****************************************************************/
/*Creer une pièce de taille hauteur*largeur à partir du point de coordonnées(x,y)
chaque x,i,hauteur sont liés et chaque y,j,largeur sont liés
Créer une pièce du Nord-Ouest au Sud-Est
prend en paramètre la direction de la porte et genere une porte par pièce*/
void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction){
	int i,j;
	int position_porte_x;
	int position_porte_y;
	//mur de la piece indestructible
	i=pt_x-1;
    for(j=pt_y-1; j<pt_y+largeur+1; j++) {
        matrice[i][j]=mur_contour;
    }
	i=pt_x+hauteur;
	for(j=pt_y-1; j<pt_y+largeur+1; j++) {
        matrice[i][j]=mur_contour;
    }
	j=pt_y-1;
	for(i=pt_x-1; i<pt_x+hauteur+1; i++) {
        matrice[i][j]=mur_contour;
    }
	j=pt_y+largeur;
	for(i=pt_x; i<pt_x+hauteur+1; i++) {
        matrice[i][j]=mur_contour;
    }
	//piece
	for(i=pt_x;i<hauteur+pt_x && i<N-1;i++){
		for(j=pt_y;j<largeur+pt_y && j<M-1;j++){
			matrice[i][j]=vide;
		}
	}
	//postion porte
	switch(direction){
		case nord:	position_porte_x=pt_x-1;
					position_porte_y=pt_y+(largeur/2);
					matrice[position_porte_x][position_porte_y]=porte;
					break;

		case sud:	position_porte_x=pt_x+hauteur;
					position_porte_y=pt_y+(largeur/2);
					matrice[position_porte_x][position_porte_y]=porte;
					break;

		case ouest:	position_porte_x=pt_x+(hauteur/2);
					position_porte_y=pt_y-1;
					matrice[position_porte_x][position_porte_y]=porte;		
					break;

		case est:	position_porte_x=pt_x+(hauteur/2);
					position_porte_y=pt_y+largeur;
					matrice[position_porte_x][position_porte_y]=porte;	
					break;
	}
	
}

/*****************************************************************/
/*fonction init_matrice qui remplie la matrice de mur*/
void init_matrice(t_case matrice[N][M]){
	//declaration
	int i,j;
	//remplissage avec mur indestructible
	i=0;
    for(j=0; j<M; j++) {
        matrice[i][j]=mur_contour;
    }
	i=N-1;
	for(j=0; j<M; j++) {
        matrice[i][j]=mur_contour;
    }
	j=0;
	for(i=0; i<N; i++) {
        matrice[i][j]=mur_contour;
    }
	j=M-1;
	for(i=0; i<N; i++) {
        matrice[i][j]=mur_contour;
    }
	
	//remplissage avec mur destructible
	for(i=1; i<N-1; i++) {
        	for(j=1; j<M-1; j++) {
           		matrice[i][j]=mur;
       		}
	}
}

/***************************************************************/

void generer_piece_matrice(t_case matrice[N][M]){
	int i,j;
	int positionD_x;
	int positionD_y;
	int taille_largeur_piece;
	int taille_longueur_piece;
	int compteur_piece=0;
	int random_porte;
	const int nb_mur_autour_piece=3;
	t_direction dir_porte;
	srand(time(NULL));

	//random pour connaitre la position de départ de la génération de la matrice(ligne 0 et colonne 0 exclu)
	positionD_x=rand()%N+1;
	positionD_y=rand()%M+1;
	
	//random pour connaitre la largeur et la longueur de première pièce(limitée à 10*10cases minimum et 20*20cases maximum)
	taille_largeur_piece=rand()%10+10;
	taille_longueur_piece=rand()%10+10;
	while(positionD_x+taille_longueur_piece>N-2 || positionD_y+taille_largeur_piece>M-2 || positionD_x<2 || positionD_y<2){
		positionD_x=rand()%N+1;
		positionD_y=rand()%M+1;
		taille_largeur_piece=rand()%10+10;
		taille_longueur_piece=rand()%10+10;
	}
	//création pièce avec les infos récoltées précédemment
	//random pour la direction de la porte
	random_porte=rand()%4;
	switch(random_porte){
		case 0:	if(positionD_x<2) dir_porte=sud;
				else dir_porte=nord;
				break;

		case 1:	if(positionD_x>N-2) dir_porte=nord;
				else dir_porte=sud;
				break;
	
		case 2:	if(positionD_y<2) dir_porte=est;
				else dir_porte=ouest;
				break;

		case 3:	if(positionD_y<N-2) dir_porte=ouest;
				else dir_porte=est;
				break;
	}
	
	piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD_x,positionD_y,dir_porte);
	compteur_piece++;
	while(compteur_piece<nombre_piece){
		//random pour connaitre la position de départ de la génération de la matrice
		positionD_x=rand()%N+1;
		positionD_y=rand()%M+1;
		//random pour connaitre la largeur et la longueur de la pièce(limitée à 7*7cases minimum et 15*15cases maximum)
		taille_largeur_piece=rand()%8+7;
		taille_longueur_piece=rand()%8+7;
		//verification de la possibilité de créer une pièce dans un espace composé que de mur, on vérifie également la présence d'un mur de 3 rangs autour de la pièce à créer pour eviter les rapprochements des pièces
		for(i=positionD_x-nb_mur_autour_piece;i<positionD_x+taille_longueur_piece+nb_mur_autour_piece;i++){	//
			for(j=positionD_y-nb_mur_autour_piece;j<positionD_y+taille_largeur_piece+nb_mur_autour_piece;j++){
				while(matrice[i][j]==vide || matrice[i][j]==mur_contour || positionD_x+taille_longueur_piece>N-2 || positionD_y+taille_largeur_piece>M-2 || positionD_x<2 || positionD_y<2){
					positionD_x=rand()%N+1;
					positionD_y=rand()%M+1;
					taille_largeur_piece=rand()%8+7;
					taille_longueur_piece=rand()%8+7;
					i=positionD_x-nb_mur_autour_piece;
					j=positionD_y-nb_mur_autour_piece;
				}
			}		
		}
		
		//création pièce avec les infos récoltées précédemment
		random_porte=rand()%4;
		switch(random_porte){
			case 0:	if(positionD_x<2) dir_porte=sud;
					else dir_porte=nord;
					break;

			case 1:	if(positionD_x>N-2) dir_porte=nord;
					else dir_porte=sud;
					break;
	
			case 2:	if(positionD_y<2) dir_porte=est;
					else dir_porte=ouest;
					break;

			case 3:	if(positionD_y<N-2) dir_porte=ouest;
					else dir_porte=est;
					break;
		}
		piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD_x,positionD_y,dir_porte);
		compteur_piece++;
	}
	
}
/********************************************************************************/
/*Affiche la recherche du plus court chemin*/
void recherche_chemin(t_case matrice[N][M],t_coord depart,t_coord arrive){
	int tab_longueur[N][M];
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(matrice[i][j]==mur || matrice[i][j]==porte) tab_longueur[i][j]=-1;
			else if (matrice[i][j]==vide || matrice[i][j]==mur_contour) tab_longueur[i][j]=-2;
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
	/*Recuperation du chemin*/
	//afficher_chemin(tab_longueur);
	i=arrive.x;
	j=arrive.y;
	while(tab_longueur[i][j]!=1){
	/*Recherche des coordonnées de la prochaine coordonnée*/
		if(i-1>=0 && tab_longueur[i-1][j]==tab_longueur[i][j]-1) i--;
		else if(i+1<N && tab_longueur[i+1][j]==tab_longueur[i][j]-1) i++;
		else if(j-1>=0 && tab_longueur[i][j-1]==tab_longueur[i][j]-1) j--;
		else if(j+1<M && tab_longueur[i][j+1]==tab_longueur[i][j]-1) j++;
		matrice[i][j]=couloir;
	}
}
/*****************************************************************/
void afficher_chemin(int matrice[N][M]){
	int i,j;
	for(i=0;i<N;i++){
		printf("\n");
		for(j=0;j<M;j++){
			if(matrice[i][j]==-2) printf(" ");
			else printf("%d ",matrice[i][j]);
		}
	}
	printf("\n");
}
/*******************************************************************/
void generer_matrice_tot(t_case matrice[N][M]){
	generer_piece_matrice(matrice);
	t_coord depart;
	t_coord arrive;
	t_coord tab_porte[nombre_piece];
	int i,j,a;
	int passage=0;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(matrice[i][j]==porte){
				tab_porte[passage].x=i;
				tab_porte[passage].y=j;
				passage++;
			}
		}
	}
	for(a=0;a<passage-1;a++){
		depart.x=tab_porte[a].x;
		depart.y=tab_porte[a].y;
		arrive.x=tab_porte[a+1].x;
		arrive.y=tab_porte[a+1].y;
		recherche_chemin(matrice,depart,arrive);
	}
}

/*****************************************************************/
/*fonction afficher_matrice */
void afficher_matrice(t_case matrice[N][M]){
    //declaration
  	int i;
   	int j;

   	printf("\t");
   	for(i=0;i<N;i++){
        	for(j=0;j<M;j++){
				if(matrice[i][j]==mur)printf("X");
				else if(matrice[i][j]==mur_contour) printf("D");
				else if(matrice[i][j]==vide)printf(" ");
				else if(matrice[i][j]==porte)printf("P");
				else if(matrice[i][j]==piege)printf("?");
				else if(matrice[i][j]==hero)printf("@");
				else if(matrice[i][j]==monstre)printf("M");
				else if(matrice[i][j]==couloir)printf(".");
        	}
       		printf("\n\t");
    	}
    	printf("\n");
}
