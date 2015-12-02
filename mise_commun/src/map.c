#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "../include/map.h"
#include "../include/structure.h"
#include "../include/couleur.h"

t_pos tab_coord_positionD_piece[50];

/*****************************************************************/
/*Creer une pièce de taille hauteur*largeur à partir du point de coordonnées(pt_x,pt_y)
*Chaque x,i,hauteur sont liés et chaque y,j,largeur sont liés
*Creer une pièce du Nord-Ouest au Sud-Est
*prend en paramètre la direction de la porte et genere une porte par pièce
*/
void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction){
	int i,j;
	t_coord position_porte;
	
	//mur de la piece indestructible
	for(i=pt_x-1;i<hauteur+pt_x+1 && i<N-1;i++){
		for(j=pt_y-1;j<largeur+pt_y+1 && j<M-1;j++){
			matrice[i][j]=mur_contour;
		}
	}
	
	//piece vide
	for(i=pt_x;i<hauteur+pt_x && i<N-1;i++){
		for(j=pt_y;j<largeur+pt_y && j<M-1;j++){
			matrice[i][j]=vide;
		}
	}

	//position porte
	switch(direction){
		case nord:	position_porte.x=pt_x-1;
					position_porte.y=pt_y+(largeur/2);
					matrice[position_porte.x][position_porte.y]=porte;
					break;

		case sud:	position_porte.x=pt_x+hauteur;
					position_porte.y=pt_y+(largeur/2);
					matrice[position_porte.x][position_porte.y]=porte;
					break;

		case ouest:	position_porte.x=pt_x+(hauteur/2);
					position_porte.y=pt_y-1;
					matrice[position_porte.x][position_porte.y]=porte;		
					break;

		case est:	position_porte.x=pt_x+(hauteur/2);
					position_porte.y=pt_y+largeur;
					matrice[position_porte.x][position_porte.y]=porte;	
					break;
	}
	
}

/*****************************************************************/
/*fonction init_matrice qui remplie la matrice de mur*/
void init_matrice(t_case matrice[N][M]){
	//declaration
	int i,j;
	//remplissage avec mur indestructible
	for(i=0; i<N; i++) {
        for(j=0; j<M; j++) {
           	matrice[i][j]=mur_contour;
       	}
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
	t_coord positionD;
	int taille_largeur_piece;
	int taille_longueur_piece;
	int compteur_piece=0;
	int random_porte;
	const int nb_mur_autour_piece=3;
	t_direction dir_porte;
	srand(time(NULL));
	
	//piece principale
		//random pour connaitre la largeur et la longueur de la première pièce(limitée à 15*15cases minimum et 20*20cases maximum)
		taille_largeur_piece=rand()%5+15;
		taille_longueur_piece=rand()%5+15;
		//positionnement piece principale au centre de la map
		positionD.x=N/2-taille_longueur_piece/2;
		positionD.y=M/2-taille_largeur_piece/2;
		//verification
		while(positionD.x+taille_longueur_piece>N-2 || positionD.y+taille_largeur_piece>M-2 || positionD.x<2 || positionD.y<2){
			taille_largeur_piece=rand()%5+15;
			taille_longueur_piece=rand()%5+15;
			positionD.x=N/2-taille_longueur_piece/2;
			positionD.y=M/2-taille_largeur_piece/2;
		}
		//création pièce avec les infos récoltées précédemment
		//random pour la direction de la porte
		random_porte=rand()%4;
		switch(random_porte){
			case 0:	if(positionD.x<3) dir_porte=sud;
					else dir_porte=nord;
					break;

			case 1:	if(positionD.x>N-3) dir_porte=nord;
					else dir_porte=sud;
					break;
		
			case 2:	if(positionD.y<3) dir_porte=est;
					else dir_porte=ouest;
					break;

			case 3:	if(positionD.y<N-3) dir_porte=ouest;
					else dir_porte=est;
					break;
		}
		piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,dir_porte);
		tab_coord_positionD_piece[compteur_piece].x_D=positionD.x;
		tab_coord_positionD_piece[compteur_piece].y_D=positionD.y;
		tab_coord_positionD_piece[compteur_piece].x_A=positionD.x+taille_longueur_piece;
		tab_coord_positionD_piece[compteur_piece].y_A=positionD.y+taille_largeur_piece;
		compteur_piece++;
		
	//autre piece
		while(compteur_piece<nombre_piece){
			//random pour connaitre la position de départ de la génération de la matrice
			positionD.x=rand()%N+1;
			positionD.y=rand()%M+1;
			//random pour connaitre la largeur et la longueur de la pièce(limitée à 7*7cases minimum et 15*15cases maximum)
			taille_largeur_piece=rand()%8+7;
			taille_longueur_piece=rand()%8+7;
			//verification de la possibilité de créer une pièce dans un espace composé que de mur, on vérifie également la présence d'un mur de 3 rangs autour de la pièce à créer pour eviter les rapprochements des pièces
			for(i=positionD.x-nb_mur_autour_piece;i<positionD.x+taille_longueur_piece+nb_mur_autour_piece;i++){	//
				for(j=positionD.y-nb_mur_autour_piece;j<positionD.y+taille_largeur_piece+nb_mur_autour_piece;j++){
					while(matrice[i][j]==vide || matrice[i][j]==mur_contour || positionD.x+taille_longueur_piece>N-2 || positionD.y+taille_largeur_piece>M-2 || positionD.x<2 || positionD.y<2){
						positionD.x=rand()%N+1;
						positionD.y=rand()%M+1;
						taille_largeur_piece=rand()%8+7;
						taille_longueur_piece=rand()%8+7;
						i=positionD.x-nb_mur_autour_piece;
						j=positionD.y-nb_mur_autour_piece;
					}
				}		
			}
			
			//création pièce avec les infos récoltées précédemment
			random_porte=rand()%4;
			switch(random_porte){
				case 0:	if(positionD.x<2) dir_porte=sud;
						else dir_porte=nord;
						break;

				case 1:	if(positionD.x>N-2) dir_porte=nord;
						else dir_porte=sud;
						break;
		
				case 2:	if(positionD.y<2) dir_porte=est;
						else dir_porte=ouest;
						break;

				case 3:	if(positionD.y<N-2) dir_porte=ouest;
						else dir_porte=est;
						break;
			}
			piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,dir_porte);
			tab_coord_positionD_piece[compteur_piece].x_D=positionD.x;
			tab_coord_positionD_piece[compteur_piece].y_D=positionD.y;
			tab_coord_positionD_piece[compteur_piece].x_A=positionD.x+taille_longueur_piece;
			tab_coord_positionD_piece[compteur_piece].y_A=positionD.y+taille_largeur_piece;
			compteur_piece++;
		}
	
}
/********************************************************************************/
/*Affiche la recherche du plus court chemin*/
void recherche_chemin_couloir(t_case matrice[N][M],t_coord depart,t_coord arrive){
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

/*******************************************************************/
void generer_matrice_tot(t_case matrice[N][M]){
	generer_piece_matrice(matrice);
	t_coord depart;
	t_coord arrive;
	t_coord tab_porte[nombre_piece];
	int i,j,a;
	//recupere coordonnées des portes
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
	//creer un chemin liant toutes les portes
	for(a=0;a<passage-1;a++){
		depart.x=tab_porte[a].x;
		depart.y=tab_porte[a].y;
		arrive.x=tab_porte[a+1].x;
		arrive.y=tab_porte[a+1].y;
		recherche_chemin_couloir(matrice,depart,arrive);
	}
}

/*****************************************************************/
void spawn_item(t_case matrice[N][M]){
	int a;
	t_coord position_hero;
	t_pos position_gauche;
	position_gauche.x_D=tab_coord_positionD_piece[0].x_D;
	position_gauche.y_D=tab_coord_positionD_piece[0].y_D;
	position_gauche.x_D=tab_coord_positionD_piece[0].x_A;
	position_gauche.y_D=tab_coord_positionD_piece[0].y_A;
	t_coord position_monstre_agressif;
	t_pos position_droite;
	position_droite.x_D=tab_coord_positionD_piece[0].x_D;
	position_droite.y_D=tab_coord_positionD_piece[0].y_D;
	position_droite.x_D=tab_coord_positionD_piece[0].x_A;
	position_droite.y_D=tab_coord_positionD_piece[0].y_A;
	
	t_coord position_monstre_defensif;
	t_coord position_monstre_inactif;
	t_coord position_coffre;
	t_coord position_cle;
	t_coord position_piege;
	
	
	for(a=1;a<nombre_piece;a++){
		//recuperation des coordonnées des salles les plus éloignées
		if(tab_coord_positionD_piece[a].y_D<position_gauche.y_D){
			position_gauche.x_D=tab_coord_positionD_piece[a].x_D;
			position_gauche.y_D=tab_coord_positionD_piece[a].y_D;
			position_gauche.x_A=tab_coord_positionD_piece[a].x_A;
			position_gauche.y_A=tab_coord_positionD_piece[a].y_A;
		}
		if(tab_coord_positionD_piece[a].y_D>position_droite.y_D){
			position_droite.x_D=tab_coord_positionD_piece[a].x_D;
			position_droite.y_D=tab_coord_positionD_piece[a].y_D;
			position_droite.x_A=tab_coord_positionD_piece[a].x_A;
			position_droite.y_A=tab_coord_positionD_piece[a].y_A;
		}
	}
	
	//positionnement de piege un peu partout meme dans les couloirs(limité à 15)
	/*for(a=0;a<15;a++){
		position_piege.x=rand()%N;
		position_piege.y=rand()%M;
		if(matrice[position_piege.x][position_piege.y]==vide || matrice[position_piege.x][position_piege.y]==couloir )matrice[position_piege.x][position_piege.y]=piege;
	}*/
	//position monstre inactif aléatoirement dans une case vide d'une pièce
	for(a=0;a<nombre_piece;a++){
		if(rand()%3==0){
			position_monstre_inactif.x=rand()%(tab_coord_positionD_piece[a].x_A-tab_coord_positionD_piece[a].x_D)+tab_coord_positionD_piece[a].x_D;
			position_monstre_inactif.y=rand()%(tab_coord_positionD_piece[a].y_A-tab_coord_positionD_piece[a].y_D)+tab_coord_positionD_piece[a].y_D;
			if(matrice[position_monstre_inactif.x][position_monstre_inactif.y]==vide)matrice[position_monstre_inactif.x][position_monstre_inactif.y]=monstre_inactif;
		}
	}
	//position monstre defensif dans la moitié des salles
	for(a=0;a<nombre_piece/2;a++){
		position_monstre_defensif.x=(tab_coord_positionD_piece[a].x_D+tab_coord_positionD_piece[a].x_A)/2;
		position_monstre_defensif.y=(tab_coord_positionD_piece[a].y_D+tab_coord_positionD_piece[a].y_A)/2;
		if(matrice[position_monstre_defensif.x][position_monstre_defensif.y]==vide)matrice[position_monstre_defensif.x][position_monstre_defensif.y]=monstre_defensif;
	}
	//position monstre agressif à l'opposé du héro
	position_monstre_agressif.x=(position_droite.x_A+position_droite.x_D)/2;
	position_monstre_agressif.y=(position_droite.y_A+position_droite.y_D)/2;
	matrice[position_monstre_agressif.x][position_monstre_agressif.y]=monstre_agressif;
	//position coffre à l'opposé du hero
	position_coffre.x=position_droite.x_A-1;
	position_coffre.y=position_droite.y_A-1;
	matrice[position_coffre.x][position_coffre.y]=coffre;
	//position clé au milieu de la map
	position_cle.x=rand()%(tab_coord_positionD_piece[0].x_A-tab_coord_positionD_piece[0].x_D)+tab_coord_positionD_piece[0].x_D;
	position_cle.y=rand()%(tab_coord_positionD_piece[0].y_A-tab_coord_positionD_piece[0].y_D)+tab_coord_positionD_piece[0].y_D;
	matrice[position_cle.x][position_cle.y]=cle;
	//position hero
	position_hero.x=(position_gauche.x_A+position_gauche.x_D)/2;
	position_hero.y=(position_gauche.y_A+position_gauche.y_D)/2;
	matrice[position_hero.x][position_hero.y]=hero;
	
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
				if(matrice[i][j]==mur_contour){
					printf("&");
				}
				else if(matrice[i][j]==mur){
					printf("X");
				}
				else if(matrice[i][j]==vide){
					printf(" ");
				}
				else if(matrice[i][j]==couloir){
					printf(".");
				}
				else if(matrice[i][j]==porte){
					printf("P");
				}
				else if(matrice[i][j]==coffre){
					printf("C");
				}
				else if(matrice[i][j]==cle){
					printf("K");
				}
				else if(matrice[i][j]==piege){
					printf("?");
				}
				else if(matrice[i][j]==hero){
					printf("@");
				}
				else if(matrice[i][j]==monstre_agressif){
					printf("M");
				}
				else if(matrice[i][j]==monstre_defensif){
					printf("D");
				}
				else if(matrice[i][j]==monstre_inactif){
					printf("I");
				}
        	}
       		printf("\n\t");
    	}
    	printf("\n");
}
