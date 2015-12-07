#ifndef JEU
#define JEU

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "../include/structure.h"

void generation_level(t_case matrice[N][M], int level);
void jeu(t_case matrice[N][M], int level);
void game_over(t_case matrice[N][M]);

#endif