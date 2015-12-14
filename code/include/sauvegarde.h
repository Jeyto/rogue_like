#ifndef SAUVEGARDE
#define SAUVEGARDE

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "structure.h"

void sauvegarde_map(t_case matrice[N][M], int level);

int generer_map_sauvegarde(t_case matrice[N][M]);

void convertion_int_enum(t_case matrice[N][M], int i, int j, int valeur);

void convertion_int_enum_monstre(t_mob * mob, int valeur);

#endif
