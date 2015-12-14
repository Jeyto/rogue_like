#ifndef LISTE
#define LISTE

#include "structure.h"

void init_liste(void);

int liste_vide(void);

int hors_liste(void);

void en_tete(void);

void en_queue(void);

void precedent(void);

void suivant(void);

void valeur_elt(t_mob*);

void modif_elt(t_mob);

void oter_elt(void);

void ajout_droit(t_mob);

void ajout_gauche(t_mob);

void vider_liste(void);

#endif
