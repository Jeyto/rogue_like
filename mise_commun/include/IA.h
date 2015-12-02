#include "structure.h"

void recherche_chemin(t_case grille[N][M],t_coord depart,t_coord arrive);
void permutation(t_case grille[N][M],t_coord pos_ini,t_coord pos_arr);
int chemin_possible(t_case grille[N][M],t_coord a,t_coord b);
void generation_mob_suivante(t_case grille[N][M],t_coord personnage);
void afficher_chemin(int grille[N][M]);