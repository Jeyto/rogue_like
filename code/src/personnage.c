#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#include "personnage.h"
#include "IA.h"
#include "structure.h"

t_personnage *personnage;
/***************Fonction Personnage***************/
/*Fonction init_personnage
*Initialise la variable personnage
*/
void init_valeur_personnage(void){
	personnage->PV=3;
	personnage->score_bonus=0;
	personnage->cle=0;
	personnage->invisible=0;
	personnage->armure=0;
}
void init_personnage(void){
	personnage=malloc(sizeof(t_personnage));
}

void init_etage_personnage(void){
	personnage->PV=3;
	personnage->cle=0;
	personnage->invisible=0;
	personnage->armure=0;
}

/*Fonction gain_bonus_personnage(int gain)
*Ajoute gain au score
*/
void gain_bonus_personnage(int gain){
	personnage->score_bonus=personnage->score_bonus+gain;
}

/*Fonction valeur_personnage
*Permet de connaitre les valeurs de personnage
*/
void valeur_personnage(t_personnage *valeur){
	valeur->PV=personnage->PV;
	valeur->score_bonus=personnage->score_bonus;
	valeur->position.x=personnage->position.x;
	valeur->position.y=personnage->position.y;
	valeur->cle=personnage->cle;
	valeur->invisible=personnage->invisible;
	valeur->armure=personnage->armure;
}

/*Fonction modif_personnage
*Modifie les valeurs de personnage avec les valeurs de nperso
*/
void modif_personnage(t_personnage nperso){
	personnage->PV=nperso.PV;
	personnage->score_bonus=nperso.score_bonus;
	personnage->cle=nperso.cle;
	personnage->invisible=nperso.invisible;
	personnage->position.x=nperso.position.x;
	personnage->position.y=nperso.position.y;
	personnage->armure=nperso.armure;
}

/*Fonction modif__position_personnage
*Modifie la position du personnage avec les coordonnees npos
*/
void modif_position_personnage(t_coord npos){
	personnage->position.x=npos.x;
	personnage->position.y=npos.y;
}

/*Fonction valeur_position_personnage
*Permet de connaitre la position du personnage
*/
void valeur_position_personnage(t_coord *pos){
	pos->x=personnage->position.x;
	pos->y=personnage->position.y;
}

/*Fonction valeur_cle_personnage
*Permet de connaitre la valeur de la cle(0 ou 1)
*/
int valeur_cle_personnage(void){
	return personnage->cle;
}

/*Fonction modif_cle_personnage
*Modifie la valeur de la cle avec la valeur "valeur"
*/
void modif_cle_personnage(int valeur){
	personnage->cle=valeur;

}

/*Fonction valeur_PV_personnage
*Permet de connaitre la valeur de PV
*/
int valeur_PV_personnage(void){
	return personnage->PV;
}

/*Fonction valeur_score_personnage
*Permet de connaitre la valeur du score
*/
int valeur_score_personnage(void){
	return personnage->score_bonus;

}

/*Fonction valeur_invi_personnage
*Permet de connaitre la valeur de l'invisibilite (0 ou 1)
*/
int valeur_invi_personnage(void){
	return personnage->invisible;
}

/*Fonction modif_invi_personnage
*Modifie la valeur de l'invisibilite avec la valeur "valeur"
*/
void modif_invi_personnage(int valeur){
	personnage->invisible=valeur;
}

/*Fonction valeur_armure_personnage
*Permet de connaitre la valeur de l'armure (0 ou 1)
*/
int valeur_armure_personnage(void){
	return personnage->armure;
}

/*Fonction modif_armure_personnage
*Modifie la valeur de l'armure avec la valeur "valeur"
*/
void gain_armure_personnage(int valeur){
	personnage->armure=personnage->armure+valeur;
}

/******************************************************************/
/*Fonction degat_personnage
*si le joueur perd un combat(piege,monstre), il perd un point de vie
*il est invisible pendant un certain nombre de deplacements
*/
void degat_personnage(void){
	if(personnage->armure>0){
		personnage->armure=personnage->armure-1;
	}
	else{
		personnage->PV=personnage->PV-1;
	}
	personnage->invisible=1;
}

void attaque_personnage(t_case matrice[N][M],int ax,int ay){
	t_coord pos_attaque;
	pos_attaque.x = personnage->position.x+ax;
	pos_attaque.y = personnage->position.y+ay;

	if(position_elt(pos_attaque)){
		mob_perte_PV(matrice,1);
	}
	else if(matrice[pos_attaque.x][pos_attaque.y] == vide ){
		mvprintw( pos_attaque.x, pos_attaque.y,"+");	
	}
			
}
