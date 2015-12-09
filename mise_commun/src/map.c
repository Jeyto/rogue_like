#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "../include/map.h"
#include "../include/structure.h"
#include "../include/couleur.h"

t_pos tab_coord_positionD_piece[50];

/*****************************************************************/
/*Fonction piece
*Creer une piece de taille hauteur*largeur a partir du point de coordonnees(pt_x,pt_y)
*Chaque x,i,hauteur sont lies et chaque y,j,largeur sont lies
*Creer une piece du Nord-Ouest au Sud-Est
*Prend en parametre la direction de la porte et genere une porte par piece
*/
void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction){
	//declaration
	int i,j;
	t_coord position_porte;
	
	//traitement
	//mur contour piece indestructible
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
	//position porte en fonction de la direction choisie
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
/*fonction init_matrice
*Remplie la matrice de murs destructibles entoures de murs indestructibles
*/
void init_matrice(t_case matrice[N][M]){
	//declaration
	int i,j;
	
	//traitement
	//remplissage avec murs indestructibles
	for(i=0; i<N; i++) {
        for(j=0; j<M; j++) {
           	matrice[i][j]=mur_contour;
       	}
	}
	//remplissage avec murs destructibles
	for(i=1; i<N-1; i++) {
        for(j=1; j<M-1; j++) {
           	matrice[i][j]=mur;
       	}
	}
}

/***************************************************************/
/*Fontion generer_piece_matrice
*Creer une piece principale centree sur la map
*Creer plein de petite piece sur la map limite a nombre_piece_max
*Stock position de depart des pieces
*retourne le nombre de piece generees
*/
int generer_piece_matrice(t_case matrice[N][M], int level){
	//declaration
	int i,j;
	//piece
	int taille_largeur_piece;
	int taille_longueur_piece;
	int taille_max_piece_principale;
	int taille_max_piece_secondaire;
	int compteur_piece=0;
	int nombre_piece;
	t_coord positionD;
	const int nb_mur_autour_piece=3;
	//porte
	int random_porte;
	t_direction dir_porte;
	//random
	srand(time(NULL));
	int passage;
	
	//permet de reduire le nombre de pieces pour les niveaux debutants
	if(level==1 || level==2){
		nombre_piece=2;
		taille_max_piece_principale=25;
		taille_max_piece_secondaire=taille_max_piece_principale;
	}
	else if(level==3){
		nombre_piece=nombre_piece_max/2;
		taille_max_piece_principale=20;
		taille_max_piece_secondaire=10;
	}
	else{
		nombre_piece=nombre_piece_max;
		taille_max_piece_principale=15;
		taille_max_piece_secondaire=10;
	}
	
	//piece principale
		//random pour connaitre la largeur et la longueur de la premiere piece(limitee à 25*25cases minimum et 30*30cases maximum pour niveau <3, 20*20cases minimum et 25*25cases maximum pour niveau=3, 15*15cases minimum et 20*20cases maximum pour niveau >3)
		taille_largeur_piece=rand()%5+taille_max_piece_principale;
		taille_longueur_piece=rand()%5+taille_max_piece_principale;
		//positionnement piece principale au centre de la map pour niveau >2 ou à gauche pour niveau <3
		if(level==1 || level==2){
			positionD.x=(N-taille_max_piece_principale)/2;
			positionD.y=5;
		}else{
			positionD.x=N/2-taille_longueur_piece/2;
			positionD.y=M/2-taille_largeur_piece/2;
			//verification espace
			while(positionD.x+taille_longueur_piece>N-2 || positionD.y+taille_largeur_piece>M-2 || positionD.x<2 || positionD.y<2){
				taille_largeur_piece=rand()%5+taille_max_piece_principale;
				taille_longueur_piece=rand()%5+taille_max_piece_principale;
				positionD.x=N/2-taille_longueur_piece/2;
				positionD.y=M/2-taille_largeur_piece/2;
			}
		}
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
		
		//creation piece avec les infos récoltees precedemment
		piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,dir_porte);
		
		//stock de la position de la piece
		tab_coord_positionD_piece[compteur_piece].x_D=positionD.x;
		tab_coord_positionD_piece[compteur_piece].y_D=positionD.y;
		tab_coord_positionD_piece[compteur_piece].x_A=positionD.x+taille_longueur_piece;
		tab_coord_positionD_piece[compteur_piece].y_A=positionD.y+taille_largeur_piece;
		compteur_piece++;
	//autre piece
		while(compteur_piece<nombre_piece){
			//random pour connaitre la position de depart de la creation de la piece
			if(level==1 || level==2){
				positionD.x=(N-taille_max_piece_principale)/2;
				positionD.y=positionD.y+taille_largeur_piece + 40;
			}else{
				positionD.x=rand()%N+1;
				positionD.y=rand()%M+1;
			}
			//random pour connaitre la largeur et la longueur de la piece(limitee à 35*35cases minimum et 40*40cases maximum pour niveau <3, 10*10cases minimum et 15*15cases maximum pour niveau=3, 10*10cases minimum et 15*15cases maximum pour niveau >3)
			taille_largeur_piece=rand()%5+taille_max_piece_secondaire;
			taille_longueur_piece=rand()%5+taille_max_piece_secondaire;
			//verification de la possibilite de creer une piece dans un espace compose que de mur
			//on verifie egalement la presence d'un mur de 3 rangs autour de la piece à creer pour eviter les rapprochements des pieces
			passage=0;
			for(i=positionD.x-nb_mur_autour_piece;i<positionD.x+taille_longueur_piece+nb_mur_autour_piece;i++){	//
				for(j=positionD.y-nb_mur_autour_piece;j<positionD.y+taille_largeur_piece+nb_mur_autour_piece;j++){
					while(matrice[i][j]==vide || matrice[i][j]==mur_contour || positionD.x+taille_longueur_piece>N-2 || positionD.y+taille_largeur_piece>M-2 || positionD.x<2 || positionD.y<2){
						positionD.x=rand()%N+1;
						positionD.y=rand()%M+1;
						taille_largeur_piece=rand()%5+taille_max_piece_secondaire;
						taille_longueur_piece=rand()%5+taille_max_piece_secondaire;
						i=positionD.x-nb_mur_autour_piece;
						j=positionD.y-nb_mur_autour_piece;
						passage ++;
						//pas de place possible, on arrete la generation de piece, seules les anciennes pieces deja realisees seront affichees
						//plusieurs break pour sortir de la boucle while initiale
						if(passage>500) break;
					}
					if(passage>500) break;
				}
				if(passage>500) break;
			}
			if(passage>500) break;
			//random pour la direction de la porte
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
			//creation piece avec les infos récoltees precedemment
			piece(taille_longueur_piece,taille_largeur_piece,matrice,positionD.x,positionD.y,dir_porte);
			//stock de la position de la piece
			tab_coord_positionD_piece[compteur_piece].x_D=positionD.x;
			tab_coord_positionD_piece[compteur_piece].y_D=positionD.y;
			tab_coord_positionD_piece[compteur_piece].x_A=positionD.x+taille_longueur_piece;
			tab_coord_positionD_piece[compteur_piece].y_A=positionD.y+taille_largeur_piece;
			compteur_piece++;
		}
	return compteur_piece;
}
/********************************************************************************/
/*Affiche la recherche du plus court chemin*/
void recherche_chemin_couloir(t_case matrice[N][M],t_coord depart,t_coord arrive){
	//declaration
	int tab_longueur[N][M];
	int i,j;
	
	//traitement
	//initialisation matrice fantome utilisee pour la recherche du chemin
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
	//recuperation du chemin
	i=arrive.x;
	j=arrive.y;
	while(tab_longueur[i][j]!=1){
	//recherche des coordonnees de la prochaine coordonnee et creation de couloir de largeur 2
		if(i-1>=0 && tab_longueur[i-1][j]==tab_longueur[i][j]-1){
			i--;
			matrice[i][j]=couloir;
			if(matrice[i][j+1]==mur)matrice[i][j+1]=couloir;
			else if(matrice[i][j-1]==mur)matrice[i][j-1]=couloir;
		}
		else if(i+1<N && tab_longueur[i+1][j]==tab_longueur[i][j]-1){
			i++;
			matrice[i][j]=couloir;
			if(matrice[i][j+1]==mur)matrice[i][j+1]=couloir;
			else if(matrice[i][j-1]==mur)matrice[i][j-1]=couloir;
		}
		else if(j-1>=0 && tab_longueur[i][j-1]==tab_longueur[i][j]-1){
			j--;
			matrice[i][j]=couloir;
			if(matrice[i-1][j]==mur)matrice[i-1][j]=couloir;
			else if(matrice[i+1][j]==mur)matrice[i+1][j]=couloir;
		}
		else if(j+1<M && tab_longueur[i][j+1]==tab_longueur[i][j]-1){
			j++;
			matrice[i][j]=couloir;
			if(matrice[i-1][j]==mur)matrice[i-1][j]=couloir;
			else if(matrice[i+1][j]==mur)matrice[i+1][j]=couloir;
		}
	}
}

/*******************************************************************/
/*Fonction generer_matrice_tot
*Genere des couloirs liant chaque piece
*Finalise la map
*retourne le nombre de piece generees
*/
int generer_matrice_tot(t_case matrice[N][M], int level){
	//declaration
	int i,j,a;
	int nb_piece;
	t_coord depart;
	t_coord arrive;
	t_coord tab_porte[nombre_piece_max];
	
	//traitement
	nb_piece=generer_piece_matrice(matrice,level);
	//recupere coordonnees des portes
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
	return nb_piece;
}

/*****************************************************************/
/*Fonction spawn_item
*Place aléatoirement des items dans la map en fonction des niveaux
*hero et monstre agressif toujours eloignes au maximum
*hero eloigne au maximum du coffre
*/
void spawn_item(t_case matrice[N][M], int nb_piece, int level){
	//declaration
	int a;
	//position hero
	t_coord position_hero;
	t_pos position_gauche;
	position_gauche.x_D=tab_coord_positionD_piece[0].x_D;
	position_gauche.y_D=tab_coord_positionD_piece[0].y_D;
	position_gauche.x_D=tab_coord_positionD_piece[0].x_A;
	position_gauche.y_D=tab_coord_positionD_piece[0].y_A;
	//position monstre agressif
	t_coord position_monstre_agressif;
	t_pos position_droite;
	position_droite.x_D=tab_coord_positionD_piece[0].x_D;
	position_droite.y_D=tab_coord_positionD_piece[0].y_D;
	position_droite.x_D=tab_coord_positionD_piece[0].x_A;
	position_droite.y_D=tab_coord_positionD_piece[0].y_A;
	//position autre item
	t_coord position_monstre_defensif;
	t_coord position_monstre_inactif;
	t_coord position_coffre;
	t_coord position_cle;
	t_coord position_piege;
	
	for(a=1;a<nb_piece;a++){
		//recuperation des coordonnees des salles les plus eloignees
		//salle gauche
		if(tab_coord_positionD_piece[a].y_D<position_gauche.y_D){
			position_gauche.x_D=tab_coord_positionD_piece[a].x_D;
			position_gauche.y_D=tab_coord_positionD_piece[a].y_D;
			position_gauche.x_A=tab_coord_positionD_piece[a].x_A;
			position_gauche.y_A=tab_coord_positionD_piece[a].y_A;
		}
		//salle droite
		if(tab_coord_positionD_piece[a].y_D>position_droite.y_D){
			position_droite.x_D=tab_coord_positionD_piece[a].x_D;
			position_droite.y_D=tab_coord_positionD_piece[a].y_D;
			position_droite.x_A=tab_coord_positionD_piece[a].x_A;
			position_droite.y_A=tab_coord_positionD_piece[a].y_A;
		}
	}
	
	//hero,cle,coffre
	if(level==1){
		//position coffre a l'oppose du hero (a droite de la map)
		position_coffre.x=position_droite.x_A-1;
		position_coffre.y=position_droite.y_A-1;
		matrice[position_coffre.x][position_coffre.y]=coffre;
		//position clé au milieu de la map
		position_cle.x=rand()%(tab_coord_positionD_piece[0].x_A-tab_coord_positionD_piece[0].x_D)+tab_coord_positionD_piece[0].x_D;
		position_cle.y=rand()%(tab_coord_positionD_piece[0].y_A-tab_coord_positionD_piece[0].y_D)+tab_coord_positionD_piece[0].y_D;
		if(matrice[position_cle.x][position_cle.y]==coffre || matrice[position_cle.x][position_cle.y]==hero){
			position_cle.x++;
		}
		else matrice[position_cle.x][position_cle.y]=cle;
		//position hero a gauche de la map
		position_hero.x=(tab_coord_positionD_piece[0].x_D+tab_coord_positionD_piece[0].x_A)/2;
		position_hero.y=(tab_coord_positionD_piece[0].y_D+tab_coord_positionD_piece[0].y_A)/2;
		if(matrice[position_hero.x][position_hero.y]==coffre || matrice[position_hero.x][position_hero.y]==cle){
			position_hero.x++;
		}
		else matrice[position_hero.x][position_hero.y]=hero;
	}
	
	//level 1 + ajout monstre inactif + piege
	else if(level==2){
		//positionnement de piege un peu partout(limite à 10)
		for(a=0;a<10;a++){
			position_piege.x=rand()%N;
			position_piege.y=rand()%M;
			if(matrice[position_piege.x][position_piege.y]==vide) matrice[position_piege.x][position_piege.y]=piege;
			if(matrice[position_piege.x][position_piege.y-1]==vide) matrice[position_piege.x][position_piege.y-1]=piege;
			if(matrice[position_piege.x][position_piege.y+1]==vide) matrice[position_piege.x][position_piege.y+1]=piege;
		}
		//position monstre inactif aleatoirement dans une case vide d'une piece
		for(a=0;a<nb_piece;a++){
			if(rand()%3==0){
				position_monstre_inactif.x=rand()%(tab_coord_positionD_piece[a].x_A-tab_coord_positionD_piece[a].x_D)+tab_coord_positionD_piece[a].x_D;
				position_monstre_inactif.y=rand()%(tab_coord_positionD_piece[a].y_A-tab_coord_positionD_piece[a].y_D)+tab_coord_positionD_piece[a].y_D;
				if(matrice[position_monstre_inactif.x][position_monstre_inactif.y]==vide)matrice[position_monstre_inactif.x][position_monstre_inactif.y]=monstre_inactif;
			}
		}
		//position coffre a l'oppose du hero (a droite de la map)
		position_coffre.x=position_droite.x_A-1;
		position_coffre.y=position_droite.y_A-1;
		matrice[position_coffre.x][position_coffre.y]=coffre;
		//position clé au milieu de la map
		position_cle.x=rand()%(tab_coord_positionD_piece[0].x_A-tab_coord_positionD_piece[0].x_D)+tab_coord_positionD_piece[0].x_D;
		position_cle.y=rand()%(tab_coord_positionD_piece[0].y_A-tab_coord_positionD_piece[0].y_D)+tab_coord_positionD_piece[0].y_D;
		if(matrice[position_cle.x][position_cle.y]==coffre || matrice[position_cle.x][position_cle.y]==hero){
			position_cle.x++;
		}
		else matrice[position_cle.x][position_cle.y]=cle;
		//position hero a gauche de la map
		position_hero.x=(tab_coord_positionD_piece[0].x_D+tab_coord_positionD_piece[0].x_A)/2;
		position_hero.y=(tab_coord_positionD_piece[0].y_D+tab_coord_positionD_piece[0].y_A)/2;
		if(matrice[position_hero.x][position_hero.y]==coffre || matrice[position_hero.x][position_hero.y]==cle){
			position_hero.x++;
		}
		else matrice[position_hero.x][position_hero.y]=hero;
	}
	
	//level 2 + ajout monstre defensif
	else if(level==3){
		//positionnement de piege un peu partout(limite à 10)
		for(a=0;a<10;a++){
			position_piege.x=rand()%N;
			position_piege.y=rand()%M;
			if(matrice[position_piege.x][position_piege.y]==vide) matrice[position_piege.x][position_piege.y]=piege;
			if(matrice[position_piege.x][position_piege.y-1]==vide) matrice[position_piege.x][position_piege.y-1]=piege;
			if(matrice[position_piege.x][position_piege.y+1]==vide) matrice[position_piege.x][position_piege.y+1]=piege;
		}
		//position monstre inactif aleatoirement dans une case vide d'une piece
		for(a=0;a<nb_piece;a++){
			if(rand()%3==0){
				position_monstre_inactif.x=rand()%(tab_coord_positionD_piece[a].x_A-tab_coord_positionD_piece[a].x_D)+tab_coord_positionD_piece[a].x_D;
				position_monstre_inactif.y=rand()%(tab_coord_positionD_piece[a].y_A-tab_coord_positionD_piece[a].y_D)+tab_coord_positionD_piece[a].y_D;
				if(matrice[position_monstre_inactif.x][position_monstre_inactif.y]==vide)matrice[position_monstre_inactif.x][position_monstre_inactif.y]=monstre_inactif;
			}
		}
		//position monstre defensif dans la moitie des salles
		for(a=0;a<nb_piece/2;a++){
			position_monstre_defensif.x=(tab_coord_positionD_piece[a].x_D+tab_coord_positionD_piece[a].x_A)/2;
			position_monstre_defensif.y=(tab_coord_positionD_piece[a].y_D+tab_coord_positionD_piece[a].y_A)/2;
			if(matrice[position_monstre_defensif.x][position_monstre_defensif.y]==vide)matrice[position_monstre_defensif.x][position_monstre_defensif.y]=monstre_defensif;
		}
		//position coffre a l'oppose du hero (a droite de la map)
		position_coffre.x=position_droite.x_A-1;
		position_coffre.y=position_droite.y_A-1;
		matrice[position_coffre.x][position_coffre.y]=coffre;
		//position clé au milieu de la map
		position_cle.x=rand()%(tab_coord_positionD_piece[0].x_A-tab_coord_positionD_piece[0].x_D)+tab_coord_positionD_piece[0].x_D;
		position_cle.y=rand()%(tab_coord_positionD_piece[0].y_A-tab_coord_positionD_piece[0].y_D)+tab_coord_positionD_piece[0].y_D;
		if(matrice[position_cle.x][position_cle.y]==coffre || matrice[position_cle.x][position_cle.y]==hero){
			position_cle.x++;
		}
		else matrice[position_cle.x][position_cle.y]=cle;
		//position hero a gauche de la map
		position_hero.x=(position_gauche.x_A+position_gauche.x_D)/2;
		position_hero.y=(position_gauche.y_A+position_gauche.y_D)/2;
		if(matrice[position_hero.x][position_hero.y]==coffre || matrice[position_hero.x][position_hero.y]==cle){
			position_hero.x++;
		}
		else matrice[position_hero.x][position_hero.y]=hero;
	}
	
	//level 3 + ajout monstre agressif
	else if(level==4){
		//positionnement de piege un peu partout(limite à 10)
		for(a=0;a<10;a++){
			position_piege.x=rand()%N;
			position_piege.y=rand()%M;
			if(matrice[position_piege.x][position_piege.y]==vide) matrice[position_piege.x][position_piege.y]=piege;
			if(matrice[position_piege.x][position_piege.y-1]==vide) matrice[position_piege.x][position_piege.y-1]=piege;
			if(matrice[position_piege.x][position_piege.y+1]==vide) matrice[position_piege.x][position_piege.y+1]=piege;
		}
		//position monstre inactif aleatoirement dans une case vide d'une piece
		for(a=0;a<nb_piece;a++){
			if(rand()%3==0){
				position_monstre_inactif.x=rand()%(tab_coord_positionD_piece[a].x_A-tab_coord_positionD_piece[a].x_D)+tab_coord_positionD_piece[a].x_D;
				position_monstre_inactif.y=rand()%(tab_coord_positionD_piece[a].y_A-tab_coord_positionD_piece[a].y_D)+tab_coord_positionD_piece[a].y_D;
				if(matrice[position_monstre_inactif.x][position_monstre_inactif.y]==vide)matrice[position_monstre_inactif.x][position_monstre_inactif.y]=monstre_inactif;
			}
		}
		//position monstre defensif dans la moitie des salles
		for(a=0;a<nb_piece/2;a++){
			position_monstre_defensif.x=(tab_coord_positionD_piece[a].x_D+tab_coord_positionD_piece[a].x_A)/2;
			position_monstre_defensif.y=(tab_coord_positionD_piece[a].y_D+tab_coord_positionD_piece[a].y_A)/2;
			if(matrice[position_monstre_defensif.x][position_monstre_defensif.y]==vide)matrice[position_monstre_defensif.x][position_monstre_defensif.y]=monstre_defensif;
		}
		//position monstre agressif à l'opposé du héro
		position_monstre_agressif.x=(position_droite.x_A+position_droite.x_D)/2;
		position_monstre_agressif.y=(position_droite.y_A+position_droite.y_D)/2;
		matrice[position_monstre_agressif.x][position_monstre_agressif.y]=monstre_agressif;
		//position coffre a l'oppose du hero (a droite de la map)
		position_coffre.x=position_droite.x_A-1;
		position_coffre.y=position_droite.y_A-1;
		matrice[position_coffre.x][position_coffre.y]=coffre;
		//position clé au milieu de la map
		position_cle.x=rand()%(tab_coord_positionD_piece[0].x_A-tab_coord_positionD_piece[0].x_D)+tab_coord_positionD_piece[0].x_D;
		position_cle.y=rand()%(tab_coord_positionD_piece[0].y_A-tab_coord_positionD_piece[0].y_D)+tab_coord_positionD_piece[0].y_D;
		if(matrice[position_cle.x][position_cle.y]==coffre || matrice[position_cle.x][position_cle.y]==hero){
			position_cle.x++;
		}
		else matrice[position_cle.x][position_cle.y]=cle;
		//position hero a gauche de la map
		position_hero.x=(position_gauche.x_A+position_gauche.x_D)/2;
		position_hero.y=(position_gauche.y_A+position_gauche.y_D)/2;
		if(matrice[position_hero.x][position_hero.y]==coffre || matrice[position_hero.x][position_hero.y]==cle){
			position_hero.x++;
		}
		else matrice[position_hero.x][position_hero.y]=hero;
	}
	
	//level 4 + la totale
	else if(level==5){
		//positionnement de piege un peu partout(limite à 20)
		for(a=0;a<20;a++){
			position_piege.x=rand()%N;
			position_piege.y=rand()%M;
			if(matrice[position_piege.x][position_piege.y]==vide) matrice[position_piege.x][position_piege.y]=piege;
			if(matrice[position_piege.x][position_piege.y-1]==vide) matrice[position_piege.x][position_piege.y-1]=piege;
			if(matrice[position_piege.x][position_piege.y+1]==vide) matrice[position_piege.x][position_piege.y+1]=piege;
		}
		//position monstre inactif aleatoirement dans une case vide d'une piece
		for(a=0;a<nb_piece;a++){
			position_monstre_inactif.x=rand()%(tab_coord_positionD_piece[a].x_A-tab_coord_positionD_piece[a].x_D)+tab_coord_positionD_piece[a].x_D;
			position_monstre_inactif.y=rand()%(tab_coord_positionD_piece[a].y_A-tab_coord_positionD_piece[a].y_D)+tab_coord_positionD_piece[a].y_D;
			if(matrice[position_monstre_inactif.x][position_monstre_inactif.y]==vide)matrice[position_monstre_inactif.x][position_monstre_inactif.y]=monstre_inactif;
		}
		//position monstre defensif dans toutes les salles
		for(a=0;a<nb_piece;a++){
			position_monstre_defensif.x=(tab_coord_positionD_piece[a].x_D+tab_coord_positionD_piece[a].x_A)/2;
			position_monstre_defensif.y=(tab_coord_positionD_piece[a].y_D+tab_coord_positionD_piece[a].y_A)/2;
			if(matrice[position_monstre_defensif.x][position_monstre_defensif.y]==vide)matrice[position_monstre_defensif.x][position_monstre_defensif.y]=monstre_defensif;
		}
		//position monstre agressif à l'opposé du héro et dans d'autres salles
		position_monstre_agressif.x=(position_droite.x_A+position_droite.x_D)/2;
		position_monstre_agressif.y=(position_droite.y_A+position_droite.y_D)/2;
		matrice[position_monstre_agressif.x][position_monstre_agressif.y]=monstre_agressif;
		
		//position coffre a l'oppose du hero (a droite de la map)
		position_coffre.x=position_droite.x_A-1;
		position_coffre.y=position_droite.y_A-1;
		matrice[position_coffre.x][position_coffre.y]=coffre;
		if(matrice[position_coffre.x-2][position_coffre.y-2]==vide)matrice[position_coffre.x-2][position_coffre.y-2]=monstre_agressif;
		
		//position clé au milieu de la map
		position_cle.x=rand()%(tab_coord_positionD_piece[0].x_A-tab_coord_positionD_piece[0].x_D)+tab_coord_positionD_piece[0].x_D;
		position_cle.y=rand()%(tab_coord_positionD_piece[0].y_A-tab_coord_positionD_piece[0].y_D)+tab_coord_positionD_piece[0].y_D;
		if(matrice[position_cle.x][position_cle.y]==coffre || matrice[position_cle.x][position_cle.y]==hero){
			position_cle.x++;
		}
		else matrice[position_cle.x][position_cle.y]=cle;
		if(matrice[position_cle.x-1][position_cle.y-1]==vide)matrice[position_cle.x-2][position_cle.y-2]=monstre_agressif;
		//position hero a gauche de la map
		position_hero.x=(position_gauche.x_A+position_gauche.x_D)/2;
		position_hero.y=(position_gauche.y_A+position_gauche.y_D)/2;
		if(matrice[position_hero.x][position_hero.y]==coffre || matrice[position_hero.x][position_hero.y]==cle){
			position_hero.x++;
		}
		else matrice[position_hero.x][position_hero.y]=hero;
	}
}

/*****************************************************************/
/*Fonction afficher_matrice
*Affiche chaque element d'une certaine maniere
*/
void afficher_matrice(t_case matrice[N][M]){
    //declaration
  	int i;
   	int j;
   	printf("\t");
   	for(i=0;i<N;i++){
        	for(j=0;j<M;j++){
				if(matrice[i][j]==mur_contour){
					//couleur(33);
					printf("&");
				}
				else if(matrice[i][j]==mur){
					//couleur(33);
					printf("X");
				}
				else if(matrice[i][j]==vide){
					printf(" ");
				}
				else if(matrice[i][j]==couloir){
					printf(" ");
				}
				else if(matrice[i][j]==porte){
					//couleur(0);
					printf("P");
				}
				else if(matrice[i][j]==coffre){
					//couleur(32);
					printf("C");
				}
				else if(matrice[i][j]==cle){
					//couleur(32);
					printf("K");
				}
				else if(matrice[i][j]==piege){
					//couleur(35);
					printf("^");
				}
				else if(matrice[i][j]==hero){
					//couleur(32);
					printf("@");
				}
				else if(matrice[i][j]==monstre_agressif){
					//couleur(35);
					printf("M");
				}
				else if(matrice[i][j]==monstre_defensif){
					//couleur(35);
					printf("D");
				}
				else if(matrice[i][j]==monstre_inactif){
					//couleur(35);
					printf("I");
				}
				else if(matrice[i][j]==bonus){
					//couleur(34);
					printf("?");
				}
				//couleur(0);
        	}
       		printf("\n\t");
    	}
    	printf("\n");
}

/*****************************************************************/
/*Fonction sauvedarde_map
*Ecriture de la map(matrice) dans le fichier txt
*/
void sauvegarde_map(t_case matrice[N][M],int level){
	int i,j;
	FILE * fichier;
	fichier=fopen("save_map.txt","w");
	fprintf(fichier,"%i\n",level);
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			fprintf(fichier,"%i ",matrice[i][j]);
		}
		fprintf(fichier,"\n");
	}
	fclose(fichier);
}

/*******************************************************************/
/*Fonction generer_map_sauvegarde
*generer map à partir d'un fichier txt
*/
int generer_map_sauvegarde(t_case matrice[N][M]){
	int i=0;
	int j=0;
	int level;
	FILE * fichier;
	fichier=fopen("save_map.txt","r");
	fscanf(fichier,"%i",&level);
	while(!feof(fichier)){
		fscanf(fichier,"%i",&matrice[i][j]);
		j++;
	}
	fclose(fichier);
	afficher_matrice(matrice);
	return level;
}
