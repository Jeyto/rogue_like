#ifndef PERSONNAGE
#define PERSONNAGE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structure.h"

void init_personnage(void);

void init_valeur_personnage(void);

void init_etage_personnage(void);

void gain_bonus_personnage(int gain);

void valeur_personnage(t_personnage *valeur);

void modif_personnage(t_personnage nperso);

void modif_position_personnage(t_coord npos);

void valeur_position_personnage(t_coord *pos);

void spawn_death(void);

int valeur_cle_personnage(void);

void modif_cle_personnage(int valeur);

int valeur_PV_personnage(void);

int valeur_score_personnage(void);

int valeur_invi_personnage(void);

void modif_invi_personnage(int valeur);

#endif
