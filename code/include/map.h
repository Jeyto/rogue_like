#ifndef MAP
#define MAP

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "structure.h"
#define nombre_piece_max 10

void init_matrice(t_case matrice[N][M]);

void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction);

int generer_piece_matrice(t_case matrice[N][M], int level);

void recherche_chemin_couloir(t_case grille[N][M],t_coord depart,t_coord arrive);

int generer_matrice_tot(t_case matrice[N][M], int level);

void spawn_item(t_case matrice[N][M], int nb_piece, int level);

void afficher_matrice(t_case matrice[N][M]);

void afficher_legende(int level);

void afficher_ecran(t_case matrice[N][M],int level);

#endif
