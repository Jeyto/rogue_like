#ifndef JEU
#define JEU

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "../include/structure.h"

void generation_level(t_case matrice[N][M], int level);
void game_message(t_case matrice[N][M], int niveau_termine);
void spawn_death(void);
void jeu(t_case matrice[N][M], int level);
void init_personnage();
void gain_bonus_personnage(int gain);
void valeur_personnage(t_personnage *valeur);
void modif_position_personnage(t_coord npos);
void valeur_position_personnage(t_coord *pos);

#endif
