#ifndef IA
#define IA

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "structure.h"

void permutation_monstre_agr(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr);

void permutation_monstre_def(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr);

void permutation_monstre_def(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr);

void generation_mob_suivante(t_case grille[N][M],t_coord personnage);

void afficher_chemin(int grille[N][M]);

int recherche_chemin_monstre_def(t_case grille[N][M],t_coord depart,t_coord arrive);

int recherche_chemin_monstre_agr(t_case grille[N][M],t_coord depart,t_coord arrive);

void chemin_aleatoire(t_case grille[N][M],t_coord depart);

void init_liste_mob(t_case grille[N][M]);

int position_elt(t_coord pos);

void mob_perte_PV(t_case grille[N][M],int perte);
#endif
