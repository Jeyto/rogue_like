/**	
	*\file personnage.c
    *\brief Fonction gerant les caracteristiques du personnage
    *\author PAVARD Valentin Gerbault Maxime Decrand Baptiste
    *\version 2.0
    *\date 17/12/2015
    *\fn void init_personnage(void)
    *\param void
    *\brief Initialise la variable personnage en allouant un adresse t_personnage
    *\return void
    *\fn void init_valeur_personnage(void)
    *\param void
    *\brief Initialise les valeurs du personnage
    *\return void
    *\fn void init_etage_personnage(void)
    *\param void
    *\brief Initialise le personnage lors d'un changement de niveau
    *\return void
    *\fn void gain_bonus_personnage(int gain)
    *\param void
    *\brief Ajoute gain au score
    *\return void
    *\fn void valeur_personnage(t_personnage *valeur)
    *\param t_personnage *valeur contiendra les valeurs de personnage
    *\brief Permet de connaitre les valeurs de personnage
    *\return void
    *\fn void modif_personnage(t_personnage nperso)
    *\param t_personnage nperso contiendra les valeurs de personnage
    *\brief Modifie les valeurs de personnage avec les valeurs de nperso
    *\return void
    *\fn void modif_position_personnage(t_coord npos)
    *\param t_coord npos contient la nouvelle position du heros
    *\brief Modifie la position du personnage avec les coordonnees npos
    *\return void
    *\fn int valeur_cle_personnage(void)
    *\param void
    *\brief Permet de connaitre la valeur de la cle(0 ou 1)
    *\return personnage->cle est la valeur de la clé
    *\fn void modif_cle_personnage(int valeur)
    *\param int valeur est la nouvelle valeur de la cle
    *\brief Modifie la valeur de la cle avec la valeur valeur
    *\return void
    *\fn int valeur_PV_personnage(void)
    *\param void
    *\brief Permet de connaitre la valeur de PV
    *\return personnage->PV est la valeur PV du personnage
    *\fn int valeur_score_personnage(void)
    *\param void
    *\brief Permet de connaitre la valeur du score
    *\return personnage->score_bonus est le score du personnage
    *\fn int valeur_invi_personnage(void)
    *\param void
    *\brief Permet de connaitre la valeur de l'invisibilite (0 ou 1)
    *\return personnage->invisible est la valeur de l'invisibilite
    *\fn void modif_invi_personnage(int valeur)
    *\param int valeur est la nouvelle valeur de l'invisibilite
    *\brief Modifie la valeur de l'invisibilite avec la valeur
    *\return void
    *\fn int valeur_armure_personnage(void)
    *\param void
    *\brief Permet de connaitre la valeur de l'armure (0 ou 1)
    *\return personnage->armure est la valeur de l'armure
    *\fn void gain_armure_personnage(int valeur)
    *\param int valeur est la nouvelle valeur de l'armure
    *\brief Modifie la valeur de l'armure avec la valeur 
    *\return void
    *\fn void degat_personnage(void)
    *\param void
    *\brief si le joueur perd un combat(piege,monstre), il perd un point de vie
			il est invisible pendant un certain nombre de deplacements
    *\return void
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#include "personnage.h"
#include "liste_mob.h"
#include "structure.h"

t_personnage *personnage;
/***************Fonction Personnage***************/

/*Fonction init_personnage
*Initialise la variable personnage en allouant un adresse t_personnage
*/
void init_personnage(void){
	personnage=malloc(sizeof(t_personnage));
}

/*Fonction init_valeur_personnage
*Initialise les valeurs du personnage
*/
void init_valeur_personnage(void){
	personnage->PV=3;
	personnage->score_bonus=0;
	personnage->cle=0;
	personnage->invisible=0;
	personnage->armure=0;
}

/*Fonction init_etage_personnage
*Initialise le personnage lors d'un changement de niveau
*/
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
