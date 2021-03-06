/**	
	*\file liste_mob.c
    *\brief Fonctions gerant la liste et les caracteristiques des monstres
    *\author PAVARD Valentin Gerbault Maxime Decrand Baptiste
    *\version 2.0
    *\date 17/12/2015
    *\fn void init_liste_mob()
    *\param void
    *\brief Initialise la liste de mob en allouant de la memoire pour le drapeau
    *\return void
    *\fn void init_carac_mob(t_case grille[N][M])
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    *\brief Recupere dans une grille les monstres,les ajoute dans la liste avec leurs caractèristique
    *\return void
    *\fn int liste_vide_mob()
    *\param void
    *\brief Connaitre si la liste est vide
    *\return vrai si la liste est vide faux sinon
    *\fn int hors_liste_mob()
    *\param void
    *\brief Connaitre si hors liste
    *\return vrai si on est hors liste faux sinon
    *\fn void en_tete()
    *\param void
    *\brief place l'element courant en tete la liste
    *\return void
    *\fn void en_queue()
    *\param void
    *\brief place l'element courant en queue de la liste
    *\return void
    *\fn void precedent()
    *\param void
    *\brief place l'elt courant sur l'element precedent
    *\return void
    \fn void suivant()
    *\param void
    *\brief place l'elt courant sur l'element suivant
    *\return void
    \fn void valeur_mob(t_mob *v)
    *\param t_mob *v
    *\brief place dans v la valeur de mob
    *\return void
    \fn void modif_mob(t_mob v)
    *\param t_mob v
    *\brief modifie la valeur de l'element courant par v
    *\return void
    *\fn void vider_liste_mob()
    *\param void
    *\brief ote les elements de la liste
    *\return void
    *\fn void oter_mob()
    *\param void
    *\brief ote l'element courant,l'element courant devient le precedent
    *\return void
    *\fn void ajout_droit(t_mob v)
    *\param t_mob v
    *\brief ajout a droite de l'element courant un monstre, l'element courant se place sur l'élement ajouter
    *\return void
    *\fn void ajout_gauche(t_mob v)
    *\param t_mob v
    *\brief ajout a gauche de l'element courant un monstre, l'element courant se place sur l'élement ajouter
    *\return void
    *\fn int position_mob(t_coord pos)
    *\param t_coord pos
    *\brief place l'element courant sur monstre situer aux coordonnees pos
    *\return 0 s'il n'a pas trouve le mob sinon 1
    *\fn void mob_perte_PV(t_case grille[N][M],int perte)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		int perte est le nombre de point de vie perdu
    *\brief fait perdre des pv au monstre courant si celui-ci meurs il concede des points bonus au personnage et disparait de la liste 
    *\return void
*/

#include<stdio.h>
#include<stdlib.h>

#include "liste_mob.h"
#include "structure.h"
#include "personnage.h"

/* Déclaration des indices de queue et d'élément courant */
t_element *drapeau;
t_element *ec;

/* Primitives de manipulation des listes */

/* Fonction init_liste_mob
* Initialise la liste de mob en allouant de la memoire pour le drapeau
*/
void init_liste_mob(){
	drapeau = malloc(sizeof(t_element));
	drapeau->pred = drapeau;
	drapeau->succ = drapeau;
	ec = drapeau;
}
/*Fonction init_carac_mob
*Recupere dans une grille les monstres,les ajoute dans la liste avec leurs caractèristique
*/
void init_carac_mob(t_case grille[N][M]){
	t_mob valeur;
	vider_liste_mob();
	en_tete();
	for(valeur.position.x=0;valeur.position.x<N;valeur.position.x++){
		for(valeur.position.y=0;valeur.position.y<M;valeur.position.y++){
			switch(grille[valeur.position.x][valeur.position.y]){
				/*La liste contient pour chaques monstres son type,sa position et ces PV initiales*/
				case monstre_inactif:
					valeur.race_mob=monstre_inactif;
					valeur.PV=1;
					ajout_droit(valeur);
					break;
				case monstre_agressif:
					valeur.race_mob=monstre_agressif;
					valeur.PV=2;
					ajout_droit(valeur);
					break;
				case monstre_defensif:
					valeur.race_mob=monstre_defensif;
					valeur.PV=1;
					ajout_droit(valeur);
					break;
				default: break;
			}
		}
	}
}

/*Fonction liste_vide_mob
* retourne vrai si la liste est vide faux sinon
*/
int liste_vide_mob(){
	return drapeau->pred==drapeau;
}

/*Fonction hors_liste_mob
* retourne vrai si on est hors liste faux sinon
*/
int hors_liste_mob(){
	return ec==drapeau;
}
/*Fonction en_tete()
*place l'element courant en tete la liste
*/
void en_tete(){
	if (!liste_vide_mob())
		ec = drapeau->succ;
}
/*Fonction en_queue()
*place l'element courant en queue de la liste
*/
void en_queue(){
	if (!liste_vide_mob())
		ec = drapeau->pred;
}
/*Fonction precedent()
*place l'elt courant sur l'element precedent
*/
void precedent(){
	if (!hors_liste_mob())
		ec = ec->pred;
}
/*Fonction suivant()
*place l'elt courant sur l'element suivant
*/
void suivant(){
	if (!hors_liste_mob())
		ec = ec->succ;
}
/*Fonction valeur_mob(t_mob *v)
*place dans v la valeur de mob
*/
void valeur_mob(t_mob *v){
	if (!hors_liste_mob())
		v->position.x = ec->valeur.position.x;
		v->position.y = ec->valeur.position.y;
		v->PV=ec->valeur.PV;
		v->race_mob=ec->valeur.race_mob;
}
/*Fonction modif_mob(t_mob v)
*modifie la valeur de l'element courant par v
*/
void modif_mob(t_mob v){
	if (!hors_liste_mob())
		ec->valeur.position.x = v.position.x;
		ec->valeur.position.y = v.position.y;
		ec->valeur.PV = v.PV;
		ec->valeur.race_mob = v.race_mob;
}
/*Fonction vider_liste_mob()
* ote les elements de la liste
*/
void vider_liste_mob(){
	if(!liste_vide_mob()){
		en_queue();//on commence en fin de liste car on utilise oter_mob() qui se positionne sur le predecesseur
		/*on enleve les elements un par un jusqu'a ce que la liste soit vide*/
		while(!hors_liste_mob()){
			oter_mob();
		}
	}
}
/*Fonction oter_mob()
* ote l'element courant,l'element courant devient le precedent
*/
void oter_mob(){
	t_element * temp;
	if (!hors_liste_mob()){
		(ec->succ)->pred = ec->pred;
		(ec->pred)->succ = ec->succ;
		temp = ec;
		ec = ec->pred;
		free(temp);
	}
}
/*Fonction ajout_droit(t_mob v)
*ajout a droite de l'element courant un monstre, l'element courant se place sur l'élement ajouter
*/
void ajout_droit(t_mob v){
	t_element* nouv;
	if (liste_vide_mob() || !hors_liste_mob()){
		nouv = malloc(sizeof(t_element));
		nouv->valeur.position.x = v.position.x;
		nouv->valeur.position.y = v.position.y;
		nouv->valeur.PV = v.PV;
		nouv->valeur.race_mob = v.race_mob;
		nouv->pred = ec;
		nouv->succ = ec->succ;
		(ec->succ)->pred = nouv;
		ec->succ = nouv;
		ec = nouv;
	}
}
/*Fonction ajout_gauche(t_mob v)
*ajout a gauche de l'element courant un monstre, l'element courant se place sur l'élement ajouter
*/
void ajout_gauche(t_mob v){
	t_element* nouv;
	if (liste_vide_mob() || !hors_liste_mob()){
		nouv = malloc(sizeof(t_element));
		nouv->valeur.position.x = v.position.x;
		nouv->valeur.position.y = v.position.y;
		nouv->valeur.PV = v.PV;
		nouv->valeur.race_mob = v.race_mob;
		nouv->succ = ec;
		nouv->pred = ec->pred;
		(ec->pred)->succ = nouv;
		ec->pred = nouv;
		ec = nouv;
	}
}

/*Fonction position_mob(t_coord pos)
*place l'element courant sur monstre situer aux coordonnees pos
*/
int position_mob(t_coord pos){
	t_mob mob;
	if(!liste_vide_mob()){
		en_tete();
		while(!hors_liste_mob()){
			valeur_mob(&mob);
			if(mob.position.x==pos.x && mob.position.y==pos.y) return 1;
			suivant();
		}
	}
	return 0;
}

/*Fonction mob_perte_PV(t_case grille[N][M],int perte)
*fait perdre des pv au monstre courant si celui-ci meurs il concede des points bonus au personnage et disparait de la liste 
*/
void mob_perte_PV(t_case grille[N][M],int perte){
	t_mob mob;
	valeur_mob(&mob);
	mob.PV=mob.PV-perte;
	if(mob.PV>0){

	 	modif_mob(mob);
	}
	else{
		switch(mob.race_mob){
			case monstre_agressif:
				gain_bonus_personnage(40);
				break;
			case monstre_defensif:
				gain_bonus_personnage(30);
				break;
			case monstre_inactif:
				gain_bonus_personnage(20);
				break;
			default: break;
		}
		grille[mob.position.x][mob.position.y]=vide;
		oter_mob();
	}
}
