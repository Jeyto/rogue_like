#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "maptest.h"
#include "couleur.h"

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

/*****************************************************************/
/*Creer une pièce de taille hauteur*largeur à partir du point de coordonnées(pt_x,pt_y)
*Chaque x,i,hauteur sont liés et chaque y,j,largeur sont liés
*Creer une piece dans une direction donnée
angleA#########angleC
  #..............#
  #..............#
  #..............#
angleB#########angleD
*/
void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction_piece){
	int i,j;
	t_coord angleA,angleB,angleC;
	//t_coord angleD;
	switch(direction_piece){
			case nord:	angleA.x=pt_x-hauteur;
						angleA.y=pt_y-largeur/2;
						angleB.x=pt_x-1;
						angleB.y=pt_y-largeur/2;
						angleC.x=pt_x-hauteur;
						angleC.y=pt_y+largeur/2;
						/*angleD.x=pt_x-1;
						angleD.y=pt_y+largeur/2;*/
						//creation piece plus grande de 2lignes, 2colonnes correspondant aux murs alentours
						/*for(i=angleA.x;i<=angleB.x;i++){
							for(j=angleA.y;j<angleC.y;j++){
								matrice[i][j]=mur_contour;
							}
						}*/
						//piece vide creusée dans la pièce précédente
						for(i=angleA.x;i<=angleB.x && i<N-1;i++){
							for(j=angleA.y;j<=angleC.y && i<M-1;j++){
								matrice[i][j]=vide;
							}
						}
						break;

			case sud:	angleA.x=pt_x+1;
						angleA.y=pt_y-largeur/2;
						angleB.x=pt_x+hauteur;
						angleB.y=pt_y-largeur/2;
						angleC.x=pt_x+1;
						angleC.y=pt_y+largeur/2;
						/*angleD.x=pt_x+hauteur;
						angleD.y=pt_y+largeur/2;*/
						//piece vide creusée dans la pièce précédente
						for(i=angleA.x;i<=angleB.x && i<N-1;i++){
							for(j=angleA.y;j<=angleC.y && i<M-1;j++){
								matrice[i][j]=vide;
							}
						}
						break;

			case ouest:	angleA.x=pt_x-hauteur/2;
						angleA.y=pt_y-largeur;
						angleB.x=pt_x+hauteur/2;
						angleB.y=pt_y-largeur;
						angleC.x=pt_x-hauteur/2;
						angleC.y=pt_y-1;
						/*angleD.x=pt_x+hauteur/2;
						angleD.y=pt_y-1;*/
						//piece vide creusée dans la pièce précédente
						for(i=angleA.x;i<=angleB.x && i<N-1;i++){
							for(j=angleA.y;j<=angleC.y && i<M-1;j++){
								matrice[i][j]=vide;
							}
						}
						break;

			case est:	angleA.x=pt_x-hauteur/2;
						angleA.y=pt_y+1;
						angleB.x=pt_x+hauteur/2;
						angleB.y=pt_y+1;
						angleC.x=pt_x-hauteur/2;
						angleC.y=pt_y+largeur;
						/*angleD.x=pt_x+hauteur/2;
						angleD.y=pt_y+largeur;*/
						//piece vide creusée dans la pièce précédente
						for(i=angleA.x;i<=angleB.x && i<N-1;i++){
							for(j=angleA.y;j<=angleC.y && i<M-1;j++){
								matrice[i][j]=vide;
							}
						}
						break;
	}
}

/****************************************************************/
/*creer un couloir de longeur donnée dans une direction donnée à partir du point de coordonnées(pt_x,pt_y)
angleA=angleB............angleC=angleD
*/
void couloir(int longueur,t_case matrice[N][M],int pt_x, int pt_y, t_direction direction_couloir){
	switch(direction_couloir){
			case nord:
						piece(longueur,1,matrice,pt_x,pt_y,direction_couloir);
						break;
			case sud:	
						piece(longueur,1,matrice,pt_x,pt_y,direction_couloir);
						break;
			case ouest:
						piece(1,longueur,matrice,pt_x,pt_y,direction_couloir);
						break;
			case est:
						piece(1,longueur,matrice,pt_x,pt_y,direction_couloir);
						break;
	}
}
/*****************************************************************/
/*Creer une pièce arrondi_lozange de taille hauteur*largeur à partir du point de coordonnées(pt_x,pt_y)
*Chaque x,i,hauteur sont liés et chaque y,j,largeur sont liés
*Creer une piece dans une direction donnée
angleA  #####  angleC
	  #.......#
	 #.........#
	  #.......#
angleB  #####  angleD
*/
void piece_ronde(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction_piece){
	int i,j,a;
	t_coord angleA;
	switch(direction_piece){
			case nord:	angleA.x=pt_x-hauteur;
						angleA.y=pt_y-largeur/2;
						a=0;
						//partie supérieur
						for(i=angleA.x; i<angleA.x+hauteur/2; i++){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						   
						// on inverse le code précédent pour obtenir la partie inférieure
						a=0;
						for(i=angleA.x+hauteur; i>=angleA.x+hauteur/2; i--){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						break;

			case sud:	angleA.x=pt_x+1;
						angleA.y=pt_y-largeur/2;
						a=0;
						//partie supérieur
						for(i=angleA.x; i<angleA.x+hauteur/2; i++){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						   
						// on inverse le code précédent pour obtenir la partie inférieure
						a=0;
						for(i=angleA.x+hauteur; i>=angleA.x+hauteur/2; i--){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						break;

			case ouest:	angleA.x=pt_x-hauteur/2;
						angleA.y=pt_y-largeur;
						a=0;
						//partie supérieur
						for(i=angleA.x; i<angleA.x+hauteur/2; i++){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						   
						// on inverse le code précédent pour obtenir la partie inférieure
						a=0;
						for(i=angleA.x+hauteur; i>=angleA.x+hauteur/2; i--){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						break;

			case est:	angleA.x=pt_x-hauteur/2;
						angleA.y=pt_y+1;
						a=0;
						//partie supérieur
						for(i=angleA.x; i<angleA.x+hauteur/2; i++){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						   
						// on inverse le code précédent pour obtenir la partie inférieure
						a=0;
						for(i=angleA.x+hauteur; i>=angleA.x+hauteur/2; i--){
							for(j=angleA.y+largeur/2-a; j<=angleA.y+largeur/2+a; j++)
								matrice[i][j]=vide;
							a++;
						}
						break;
	}
}
/***************************************************************/
/*fonction boolenne qui verifie si l'espace est libre*/
int verif_espace(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction_espace){
	int i,j;
	t_coord angleA,angleB,angleC;
	//t_coord angleD;
		
	switch(direction_espace){
			case nord:	angleA.x=pt_x-hauteur;
						angleA.y=pt_y-largeur/2;
						angleB.x=pt_x-1;
						angleB.y=pt_y-largeur/2;
						angleC.x=pt_x-hauteur;
						angleC.y=pt_y+largeur/2;
						/*angleD.x=pt_x-1;
						angleD.y=pt_y+largeur/2;*/
						//verification espace pour la piece et un mur autour
						if(pt_x-hauteur<4)return 0;
						for(i=angleA.x;i<=angleB.x;i++){
							for(j=angleA.y;j<=angleC.y;j++){
								if(matrice[i][j]!=mur) return 0;
							}
						}
						return 1;
						break;

			case sud:	angleA.x=pt_x+1;
						angleA.y=pt_y-largeur/2;
						angleB.x=pt_x+hauteur;
						angleB.y=pt_y-largeur/2;
						angleC.x=pt_x+1;
						angleC.y=pt_y+largeur/2;
						/*angleD.x=pt_x+hauteur;
						angleD.y=pt_y+largeur/2;*/
						//verification espace pour la piece et un mur autour
						if(pt_x+hauteur>N-4)return 0;
						for(i=angleA.x;i<=angleB.x;i++){
							for(j=angleA.y;j<=angleC.y;j++){
								if(matrice[i][j]!=mur) return 0;
							}
						}
						return 1;
						break;

			case ouest:	angleA.x=pt_x-hauteur/2;
						angleA.y=pt_y-largeur;
						angleB.x=pt_x+hauteur/2;
						angleB.y=pt_y-largeur;
						angleC.x=pt_x-hauteur/2;
						angleC.y=pt_y-1;
						/*angleD.x=pt_x+hauteur/2;
						angleD.y=pt_y-1;*/
						//verification espace pour la piece et un mur autour
						if(pt_y-largeur<4)return 0;
						for(i=angleA.x;i<=angleB.x;i++){
							for(j=angleA.y;j<=angleC.y;j++){
								if(matrice[i][j]!=mur) return 0;
							}
						}
						return 1;
						break;

			case est:	angleA.x=pt_x-hauteur/2;
						angleA.y=pt_y+1;
						angleB.x=pt_x+hauteur/2;
						angleB.y=pt_y+1;
						angleC.x=pt_x-hauteur/2;
						angleC.y=pt_y+largeur;
						/*angleD.x=pt_x+hauteur/2;
						angleD.y=pt_y+largeur;*/
						//verification espace pour la piece et un mur autour
						if(pt_y+largeur>M-4)return 0;
						for(i=angleA.x;i<=angleB.x;i++){
							for(j=angleA.y;j<=angleC.y;j++){
								if(matrice[i][j]!=mur) return 0;
							}
						}
						return 1;
						break;
	}
	return 0;
}

/***************************************************************/
/*genere pièce à la suite d'un couloir */
void generer_matrice_tot(t_case matrice[N][M]){
	srand(time(NULL));
	//declaration piece ou couloir
	t_coord positionD;
	int taille_largeur_piece;
	int taille_hauteur_piece;
	int longueur_couloir;
	int largeur_couloir=1;
	t_direction direction_piece;	//choix direction pour la création d'une piece
	t_direction direction_couloir;	//choix direction pour la création d'un couloir
	int espaceOk;					//valeur de retour de la fonction qui test si l'espace est disponible à la création d'une pièce ou d'un couloir
	int compteur_piece=0;	
	int compteur_couloir=0;
	t_point tab_coord_positionD_piece[50];	//tableau contenant toutes les coordonnées des positions de départ lors de la création d'une pièce
	t_point tab_coord_positionD_couloir[50];	//tableau contenant toutes les coordonnées des positions de départ lors de la création d'un couloir
	t_coord pos_porte;
	//random
	int choix_porte;
	int choix_piece;
	int a;
	
	//piece principale en centré à gauche
		//random pour connaitre la largeur et la longueur de la première pièce(limitée à 10*10cases minimum et 15*15cases maximum)
		taille_hauteur_piece=rand()%5+10;
		taille_largeur_piece=rand()%5+10;
		//positionnement piece principale centrée à gauche
		positionD.x=N/2;
		positionD.y=5;
		direction_piece=est;
		espaceOk=verif_espace(taille_hauteur_piece, taille_largeur_piece, matrice,positionD.x,positionD.y,direction_piece);
		int passage=0;
		while(espaceOk!=1){
			taille_hauteur_piece=rand()%5+10;
			taille_largeur_piece=rand()%5+10;
			espaceOk=verif_espace(taille_hauteur_piece, taille_largeur_piece, matrice,positionD.x,positionD.y,direction_piece);
			//si impossibilité de trouvé un emplacement
			passage++;
			if(passage>20) break;
		}
		//test de la sortie du while
		if(passage<19 && espaceOk==1){
			tab_coord_positionD_piece[compteur_piece].x=positionD.x;
			tab_coord_positionD_piece[compteur_piece].y=positionD.y;
			tab_coord_positionD_piece[compteur_piece].direction=direction_piece;
			piece(taille_hauteur_piece, taille_largeur_piece, matrice,positionD.x,positionD.y,direction_piece);
			compteur_piece++;
		}
	for(a=0;a<3;a++){
		//test couloir
		switch(direction_piece){
			//random pour la direction de la porte en fonction de la position de la piece
			case nord:	//porte sud impossible
						choix_porte=rand()%3;
						switch(choix_porte){
							case 0: direction_couloir=nord;
									pos_porte.x=positionD.x-taille_hauteur_piece-1;
									pos_porte.y=positionD.y;
									break;

							case 1:	direction_couloir=ouest;
									pos_porte.x=positionD.x-taille_hauteur_piece/2;
									pos_porte.y=positionD.y-taille_largeur_piece/2-1;
									break;
						
							case 2:	direction_couloir=est;
									pos_porte.x=positionD.x-taille_hauteur_piece/2;
									pos_porte.y=positionD.y+taille_largeur_piece/2+1;
									break;
						}
						break;
			case sud:	//porte nord impossible
						choix_porte=rand()%3;
						switch(choix_porte){
							case 0: direction_couloir=sud;
									pos_porte.x=positionD.x+taille_hauteur_piece+1;
									pos_porte.y=positionD.y;
									break;

							case 1:	direction_couloir=ouest;
									pos_porte.x=positionD.x+taille_hauteur_piece/2;
									pos_porte.y=positionD.y-taille_largeur_piece/2-1;
									break;
						
							case 2:	direction_couloir=est;
									pos_porte.x=positionD.x+taille_hauteur_piece/2;
									pos_porte.y=positionD.y+taille_largeur_piece/2+1;
									break;
						}
						break;
			case ouest:	//porte est impossible
						choix_porte=rand()%3;
						switch(choix_porte){
							case 0: direction_couloir=nord;
									pos_porte.x=positionD.x-taille_hauteur_piece/2-1;
									pos_porte.y=positionD.y-taille_largeur_piece/2;
									break;

							case 1:	direction_couloir=sud;
									pos_porte.x=positionD.x+taille_hauteur_piece/2+1;
									pos_porte.y=positionD.y-taille_largeur_piece/2;
									break;
						
							case 2:	direction_couloir=ouest;
									pos_porte.x=positionD.x;
									pos_porte.y=positionD.y-taille_largeur_piece-1;
									break;
						}
						break;
			case est:	//porte ouest impossible
						choix_porte=rand()%3;
						switch(choix_porte){
							case 0: direction_couloir=nord;
									pos_porte.x=positionD.x-taille_hauteur_piece/2-1;
									pos_porte.y=positionD.y+taille_largeur_piece/2;
									break;

							case 1:	direction_couloir=sud;
									pos_porte.x=positionD.x+taille_hauteur_piece/2+1;
									pos_porte.y=positionD.y+taille_largeur_piece/2;
									break;

							case 2:	direction_couloir=est;
									pos_porte.x=positionD.x;
									pos_porte.y=positionD.y+taille_largeur_piece+1;
									break;
						}
						break;
		}
		longueur_couloir=rand()%5+5;
		espaceOk=verif_espace(longueur_couloir,largeur_couloir,matrice,pos_porte.x,pos_porte.y,direction_couloir);
		if(espaceOk==1){
			tab_coord_positionD_couloir[compteur_couloir].x=pos_porte.x;
			tab_coord_positionD_couloir[compteur_couloir].y=pos_porte.y;
			tab_coord_positionD_couloir[compteur_couloir].direction=direction_couloir;
			couloir(longueur_couloir,matrice,pos_porte.x,pos_porte.y,direction_couloir);
			matrice[pos_porte.x][pos_porte.y]=porte;
			compteur_couloir++;
		}
		else{
			passage=0;
			while(espaceOk!=1 && passage<=3){ //si passage=3, tous les cotés testés
				switch(direction_piece){
					//random pour la direction de la porte en fonction de la position de la piece
					case nord:	//porte sud impossible
								choix_porte=rand()%3;
								switch(choix_porte){
									case 0: direction_couloir=nord;
											pos_porte.x=positionD.x-taille_hauteur_piece-1;
											pos_porte.y=positionD.y;
											break;

									case 1:	direction_couloir=ouest;
											pos_porte.x=positionD.x-taille_hauteur_piece/2;
											pos_porte.y=positionD.y-taille_largeur_piece/2-1;
											break;
								
									case 2:	direction_couloir=est;
											pos_porte.x=positionD.x-taille_hauteur_piece/2;
											pos_porte.y=positionD.y+taille_largeur_piece/2+1;
											break;
								}
								break;
					case sud:	//porte nord impossible
								choix_porte=rand()%3;
								switch(choix_porte){
									case 0: direction_couloir=sud;
											pos_porte.x=positionD.x+taille_hauteur_piece+1;
											pos_porte.y=positionD.y;
											break;

									case 1:	direction_couloir=ouest;
											pos_porte.x=positionD.x+taille_hauteur_piece/2;
											pos_porte.y=positionD.y-taille_largeur_piece/2-1;
											break;
								
									case 2:	direction_couloir=est;
											pos_porte.x=positionD.x+taille_hauteur_piece/2;
											pos_porte.y=positionD.y+taille_largeur_piece/2+1;
											break;
								}
								break;
					case ouest:	//porte est impossible
								choix_porte=rand()%3;
								switch(choix_porte){
									case 0: direction_couloir=nord;
											pos_porte.x=positionD.x-taille_hauteur_piece/2-1;
											pos_porte.y=positionD.y-taille_largeur_piece/2;
											break;

									case 1:	direction_couloir=sud;
											pos_porte.x=positionD.x+taille_hauteur_piece/2+1;
											pos_porte.y=positionD.y-taille_largeur_piece/2;
											break;
								
									case 2:	direction_couloir=ouest;
											pos_porte.x=positionD.x;
											pos_porte.y=positionD.y-taille_largeur_piece-1;
											break;
								}
								break;
					case est:	//porte ouest impossible
								choix_porte=rand()%3;
								switch(choix_porte){
									case 0: direction_couloir=nord;
											pos_porte.x=positionD.x-taille_hauteur_piece/2-1;
											pos_porte.y=positionD.y+taille_largeur_piece/2;
											break;

									case 1:	direction_couloir=sud;
											pos_porte.x=positionD.x+taille_hauteur_piece/2+1;
											pos_porte.y=positionD.y+taille_largeur_piece/2;
											break;

									case 2:	direction_couloir=est;
											pos_porte.x=positionD.x;
											pos_porte.y=positionD.y+taille_largeur_piece+1;
											break;
								}
								break;
				}
				longueur_couloir=rand()%5+5;
				espaceOk=verif_espace(longueur_couloir,largeur_couloir,matrice,pos_porte.x,pos_porte.y,direction_couloir);
				passage++;
			}
			//si test ok
			if(espaceOk==1 && passage<3){
				tab_coord_positionD_couloir[compteur_couloir].x=pos_porte.x;
				tab_coord_positionD_couloir[compteur_couloir].y=pos_porte.y;
				tab_coord_positionD_couloir[compteur_couloir].direction=direction_couloir;
				couloir(longueur_couloir,matrice,pos_porte.x,pos_porte.y,direction_couloir);
				matrice[pos_porte.x][pos_porte.y]=porte;
				compteur_couloir++;
			}
		}
	
	//autre piece
		switch(direction_couloir){
			//random pour la direction de la piece en fonction de la position de la porte
			case nord:	//porte sud impossible
						choix_piece=rand()%3;
						switch(choix_piece){
							case 0: direction_piece=nord;
									positionD.x=pos_porte.x-longueur_couloir-1;
									positionD.y=pos_porte.y;
									break;

							case 1:	direction_piece=ouest;
									positionD.x=pos_porte.x-longueur_couloir;
									positionD.y=pos_porte.y-1;
									break;
						
							case 2:	direction_piece=est;
									positionD.x=pos_porte.x-longueur_couloir;
									positionD.y=pos_porte.y+1;
									break;
						}
						break;
			case sud:	//porte nord impossible
						choix_piece=rand()%3;
						switch(choix_piece){
							case 0: direction_piece=sud;
									positionD.x=pos_porte.x+longueur_couloir+1;
									positionD.y=pos_porte.y;
									break;

							case 1:	direction_piece=ouest;
									positionD.x=pos_porte.x+longueur_couloir;
									positionD.y=pos_porte.y-1;
									break;
						
							case 2:	direction_piece=est;
									positionD.x=pos_porte.x+longueur_couloir;
									positionD.y=pos_porte.y+1;
									break;
						}
						break;
			case ouest:	//porte est impossible
						choix_piece=rand()%3;
						switch(choix_piece){
							case 0: direction_piece=nord;
									positionD.x=pos_porte.x-1;
									positionD.y=pos_porte.y-longueur_couloir;
									break;

							case 1:	direction_piece=sud;
									positionD.x=pos_porte.x-1;
									positionD.y=pos_porte.y-longueur_couloir;
									break;
						
							case 2:	direction_piece=ouest;
									positionD.x=pos_porte.x;
									positionD.y=pos_porte.y-longueur_couloir-1;
									break;
						}
						break;
			case est:	//porte ouest impossible
						choix_piece=rand()%3;
						switch(choix_piece){
							case 0: direction_piece=nord;
									positionD.x=pos_porte.x-1;
									positionD.y=pos_porte.y+longueur_couloir;
									break;

							case 1:	direction_piece=sud;
									positionD.x=pos_porte.x+1;
									positionD.y=pos_porte.y+longueur_couloir;
									break;

							case 2:	direction_piece=est;
									positionD.x=pos_porte.x;
									positionD.y=pos_porte.y+longueur_couloir+1;
									break;
						}
						break;
		}
		
		taille_hauteur_piece=rand()%5+10;
		taille_largeur_piece=rand()%5+10;
		espaceOk=verif_espace(taille_hauteur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,direction_piece);
		if(espaceOk==1){
			tab_coord_positionD_piece[compteur_piece].x=positionD.x;
			tab_coord_positionD_piece[compteur_piece].y=positionD.y;
			tab_coord_positionD_piece[compteur_piece].direction=direction_piece;
			piece(taille_hauteur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,direction_piece);
			matrice[positionD.x][positionD.y]=porte;
			compteur_piece++;
		}
		else{
			passage=0;
			while(espaceOk!=1 && passage<=3){ //si passage=3, tous les cotés testés
				switch(direction_couloir){
					//random pour la direction de la piece en fonction de la position de la porte
					case nord:	//porte sud impossible
								choix_piece=rand()%3;
								switch(choix_piece){
									case 0: direction_piece=nord;
											positionD.x=pos_porte.x-longueur_couloir-1;
											positionD.y=pos_porte.y;
											break;

									case 1:	direction_piece=ouest;
											positionD.x=pos_porte.x-longueur_couloir;
											positionD.y=pos_porte.y-1;
											break;
								
									case 2:	direction_piece=est;
											positionD.x=pos_porte.x-longueur_couloir;
											positionD.y=pos_porte.y+1;
											break;
								}
								break;
					case sud:	//porte nord impossible
								choix_piece=rand()%3;
								switch(choix_piece){
									case 0: direction_piece=sud;
											positionD.x=pos_porte.x+longueur_couloir+1;
											positionD.y=pos_porte.y;
											break;

									case 1:	direction_piece=ouest;
											positionD.x=pos_porte.x+longueur_couloir;
											positionD.y=pos_porte.y-1;
											break;
								
									case 2:	direction_piece=est;
											positionD.x=pos_porte.x+longueur_couloir;
											positionD.y=pos_porte.y+1;
											break;
								}
								break;
					case ouest:	//porte est impossible
								choix_piece=rand()%3;
								switch(choix_piece){
									case 0: direction_piece=nord;
											positionD.x=pos_porte.x-1;
											positionD.y=pos_porte.y-longueur_couloir;
											break;

									case 1:	direction_piece=sud;
											positionD.x=pos_porte.x-1;
											positionD.y=pos_porte.y-longueur_couloir;
											break;
								
									case 2:	direction_piece=ouest;
											positionD.x=pos_porte.x;
											positionD.y=pos_porte.y-longueur_couloir-1;
											break;
								}
								break;
					case est:	//porte ouest impossible
								choix_piece=rand()%3;
								switch(choix_piece){
									case 0: direction_piece=nord;
											positionD.x=pos_porte.x-1;
											positionD.y=pos_porte.y+longueur_couloir;
											break;

									case 1:	direction_piece=sud;
											positionD.x=pos_porte.x+1;
											positionD.y=pos_porte.y+longueur_couloir;
											break;

									case 2:	direction_piece=est;
											positionD.x=pos_porte.x;
											positionD.y=pos_porte.y+longueur_couloir+1;
											break;
								}
								break;
				}
				taille_hauteur_piece=rand()%10+2;
				taille_largeur_piece=rand()%10+2;
				espaceOk=verif_espace(taille_hauteur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,direction_piece);
				passage++;
			}
			
			//si test ok
			if(espaceOk==1 && passage<3){
				tab_coord_positionD_piece[compteur_piece].x=positionD.x;
				tab_coord_positionD_piece[compteur_piece].y=positionD.y;
				tab_coord_positionD_piece[compteur_piece].direction=direction_piece;
				piece(taille_hauteur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,direction_piece);
				matrice[positionD.x][positionD.y]=porte;
				compteur_piece++;
			}
			else{
				direction_couloir=est;
				couloir(5,matrice,positionD.x,positionD.y-1,direction_couloir);
			}
		}
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
				if(matrice[i][j]==mur){
					printf("X");
				}
				else if(matrice[i][j]==mur_contour){
					printf("#");
				}
				else if(matrice[i][j]==vide){
					printf(" ");
				}
				else if(matrice[i][j]==porte){
					printf("P");
				}
				else if(matrice[i][j]==piege){
					printf("?");
				}
				else if(matrice[i][j]==hero){
					printf("@");
				}
				else if(matrice[i][j]==monstre){
					printf("M");
				}
        	}
       		printf("\n\t");
    	}
    	printf("\n");
}
