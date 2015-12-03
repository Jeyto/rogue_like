/* Mise en oeuvre contigue d'un tableau de listes d'entiers */
#include<stdio.h>
#include<stdlib.h>
#include "../include/struct.h"
/* Déclaration des indices de queue et d'élément courant */
t_element *drapeau;
t_element *ec;

/* Primitives de manipulation des listes */

void init_liste()
{		
	drapeau = malloc(sizeof(t_element));
	drapeau->pred = drapeau;
	drapeau->succ = drapeau;
	ec = drapeau;
}

int liste_vide()
{
	return drapeau->pred==drapeau;
}

int hors_liste()
{
	return ec==drapeau;
}

void en_tete()
{
	if (!liste_vide())
		ec = drapeau->succ;
}

void en_queue()
{
	if (!liste_vide())
		ec = drapeau->pred;
}

void precedent()
{	
	if (!hors_liste())
		ec = ec->pred;
}

void suivant()
{
	if (!hors_liste())
		ec = ec->succ;
}

void valeur_elt(t_coord *v)
{
	if (!hors_liste())
		v->x = ec->valeur.x;
		v->y = ec->valeur.y;
}

void modif_elt(t_coord v)
{
	if (!hors_liste())
		ec->valeur.x = v.x;
		ec->valeur.y =v.y;
}

void oter_elt()
{	
	t_element * temp;

	if (!hors_liste())
	{	
		(ec->succ)->pred = ec->pred;
		(ec->pred)->succ = ec->succ;
		temp = ec;
		ec = ec->pred;
		free(temp);
	}
}

void ajout_droit(t_coord v)
{	
	t_element* nouv;
	if (liste_vide() || !hors_liste())
	{	
		nouv = malloc(sizeof(t_element));
		nouv->valeur.x = v.x;
		nouv->valeur.y = v.y;
		nouv->pred = ec;
		nouv->succ = ec->succ;
		(ec->succ)->pred = nouv;
		ec->succ = nouv;
		ec = nouv;
	}
}

void ajout_gauche(t_coord v)
{	
	t_element* nouv;

	if (liste_vide() || !hors_liste())
	{	
		nouv = malloc(sizeof(t_element));
		nouv->valeur.x = v.x;
		nouv->valeur.y = v.y;
		nouv->succ = ec;
		nouv->pred = ec->pred;
		(ec->pred)->succ = nouv;
		ec->pred = nouv;
		ec = nouv;
	}
}

