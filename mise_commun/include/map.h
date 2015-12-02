#ifndef MAP
#define MAP

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "../include/structure.h"
#define nombre_piece 8

void init_matrice(t_case matrice[N][M]);
void afficher_matrice(t_case matrice[N][M]);

void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction);
void piece_ronde(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction);
void generer_piece_matrice(t_case matrice[N][M]);
void recherche_chemin_couloir(t_case grille[N][M],t_coord depart,t_coord arrive);
void generer_matrice_tot(t_case matrice[N][M]);

void spawn_item(t_case matrice[N][M]);

#endif
