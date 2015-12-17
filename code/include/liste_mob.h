#ifndef LISTE
#define LISTE

#include "structure.h"

void init_liste_mob(void);

int liste_vide_mob(void);

int hors_liste_mob(void);

void en_tete(void);

void en_queue(void);

void precedent(void);

void suivant(void);

void valeur_mob(t_mob*);

void modif_mob(t_mob);

void oter_mob(void);

void ajout_droit(t_mob);

void ajout_gauche(t_mob);

void vider_liste_mob(void);

void init_liste_mob(t_case grille[N][M]);

int position_mob(t_coord pos);

void mob_perte_PV(t_case grille[N][M],int perte);
#endif
