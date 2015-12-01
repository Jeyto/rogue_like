/* Mise en oeuvre contigue d'une liste d'entiers */
#include<stdio.h>
#include <stdlib.h>
#include "../include/struct.h"
/* Déclaration des indices de queue et d'élément courant */
t_element *drapeau;
t_element *ec;
void init_liste(void)
/* Initialise la liste à vide */
{	
	drapeau=(t_element *)malloc(sizeof(t_element));
	drapeau->pred=drapeau;
	drapeau->succ=drapeau;
	ec=drapeau;
}

int liste_vide(void)
/* Rend vrai si la liste est vide, faux sinon */
{	
	return (drapeau->pred==drapeau->succ);
}

int hors_liste(void)
/* Rend vrai si l'elt courant est hors de la liste, faux sinon */
{	
	return(ec==drapeau);
}

void en_tete(void)
/* Positionne en tete de la liste */
{	
	if(!liste_vide()) 
		ec = drapeau->succ;
}

void en_queue(void)
/* Positionne en queue de la liste */
{	
	if(!liste_vide()) 
		ec = drapeau->pred;
}

void precedent(void)
/* Positionne sur l'elt precedent*/
{	
	if(!hors_liste()) 
		ec=ec->pred;
}

void suivant(void)
/* Positionne sur l'elt suivant*/
{	
	if(!hors_liste()) 
		ec=ec->succ;
}

void valeur_elt(t_coord* v)
/* Renvoie dans v la valeur de l'elt courant */
{	
	if(!hors_liste()){
		v->x=ec->valeur.x;
		v->y=ec->valeur.y;
	}
}

void modif_elt(t_coord v)
/* Affecte v à l'elt courant */
{	
	if(!hors_liste()){
		ec->valeur.x=v.x;
		ec->valeur.y=v.y;
	}
}

void oter_elt(void)
/* Supprime l'elt courant et positionne sur le precedent */
{	
	if(!hors_liste())
	{
		t_element *precedent=ec->pred;
		ec->pred->succ=ec->succ;
		ec->succ->pred=ec->pred;
		free(ec);
		ec=precedent;	
	}
}

void ajout_droit(t_coord e) {
	t_element * nouv;
	if(liste_vide() || !hors_liste()) {
		/* Création du nouvel élément */
		nouv = malloc(sizeof(t_element));
		/* Initialisation du nouvel élément */
		nouv->valeur.x = e.x;
		nouv->valeur.y = e.y;
		nouv->pred = ec;
		nouv->succ = ec->succ;
		/* Mise à jour des chaînages des voisins */
		(ec->succ)->pred = nouv;
		ec->succ = nouv;
		/* On se positionne sur le nouvel élément */
		ec = nouv;
	}
}

void ajout_gauche(t_coord e) {
    	t_element * nouv;
	if(liste_vide() || !hors_liste()) {
		/* Création du nouvel élément */
		nouv = malloc(sizeof(t_element));
		/* Initialisation du nouvel élément */
		nouv->valeur.x = e.x;
		nouv->valeur.y = e.y;
		nouv->succ = ec;
		nouv->pred = ec->pred;
		/* Mise à jour des chaînages des voisins */
		(ec->pred)->succ = nouv;
		ec->pred = nouv;
		/* On se positionne sur le nouvel élément */
		ec = nouv;
	}
}
