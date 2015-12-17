/* Mise en oeuvre contigue d'un tableau de listes d'entiers */
#include<stdio.h>
#include<stdlib.h>

#include "liste_mob.h"
#include "structure.h"
#include "personnage.h"

/* Déclaration des indices de queue et d'élément courant */
t_element *drapeau;
t_element *ec;

/* Primitives de manipulation des listes */

void init_liste_mob(){
	drapeau = malloc(sizeof(t_element));
	drapeau->pred = drapeau;
	drapeau->succ = drapeau;
	ec = drapeau;
}

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

int liste_vide_mob(){
	return drapeau->pred==drapeau;
}

int hors_liste_mob(){
	return ec==drapeau;
}

void en_tete(){
	if (!liste_vide_mob())
		ec = drapeau->succ;
}

void en_queue(){
	if (!liste_vide_mob())
		ec = drapeau->pred;
}

void precedent(){
	if (!hors_liste_mob())
		ec = ec->pred;
}

void suivant(){
	if (!hors_liste_mob())
		ec = ec->succ;
}

void valeur_mob(t_mob *v){
	if (!hors_liste_mob())
		v->position.x = ec->valeur.position.x;
		v->position.y = ec->valeur.position.y;
		v->PV=ec->valeur.PV;
		v->race_mob=ec->valeur.race_mob;
}

void modif_mob(t_mob v){
	if (!hors_liste_mob())
		ec->valeur.position.x = v.position.x;
		ec->valeur.position.y = v.position.y;
		ec->valeur.PV = v.PV;
		ec->valeur.race_mob = v.race_mob;
}

void vider_liste_mob(){
	if(!liste_vide_mob()){
		en_queue();//on commence en fin de liste car on utilise oter_mob() qui se positionne sur le predecesseur
		/*on enleve les elements un par un jusqu'� ce que la liste soit vide*/
		while(!hors_liste_mob()){
			oter_mob();
		}
	}
}

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
