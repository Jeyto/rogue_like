#ifndef JEU
#define JEU

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "../include/structure.h"

void generation_level(t_case matrice[N][M], int level);
void game_over(t_case matrice[N][M]);
void game_win(t_case matrice[N][M]);
void spawn_death(t_case matrice[N][M],t_personnage * gestion_personnage,t_coord * pos_personnage);
void jeu(t_case matrice[N][M], int level,t_personnage gestion_personnage);

#endif