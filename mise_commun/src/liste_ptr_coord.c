/* Mise en oeuvre contigue d'un tableau de listes d'entiers */
#include<stdio.h>
#include<stdlib.h>
#include "../include/structure.h"
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

void valeur_elt(t_mob *v)
{
	if (!hors_liste())
		v->position.x = ec->valeur.position.x;
		v->position.y = ec->valeur.position.y;
		v->PV=ec->valeur.PV;
		v->race_mob=ec->valeur.race_mob;
}

void modif_elt(t_mob v)
{
	if (!hors_liste())
		ec->valeur.position.x = v.position.x;
		ec->valeur.position.y = v.position.y;
		ec->valeur.PV = v.PV;
		ec->valeur.race_mob = v.race_mob;
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

void ajout_droit(t_mob v)
{
	t_element* nouv;
	if (liste_vide() || !hors_liste())
	{
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

void ajout_gauche(t_mob v)
{
	t_element* nouv;

	if (liste_vide() || !hors_liste())
	{
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
