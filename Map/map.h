#ifndef MAP
#define MAP

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define N 40
#define M 120
#define nombre_piece 8
typedef enum{nord=0, sud, ouest, est} t_direction;
typedef enum{mur_contour=-1,mur,vide,couloir,porte,coffre,cle,piege,hero,monstre_agressif,monstre_defensif,monstre_inactif} t_case;
typedef struct{int x;int y;} t_coord;
typedef struct{int x_D;int y_D;int x_A;int y_A;} t_pos;


void init_matrice(t_case matrice[N][M]);
void afficher_matrice(t_case matrice[N][M]);
void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction);
void piece_ronde(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction);
void generer_piece_matrice(t_case matrice[N][M]);
void afficher_chemin(int grille[N][M]);
void recherche_chemin(t_case grille[N][M],t_coord depart,t_coord arrive);
void generer_matrice_tot(t_case matrice[N][M]);
void spawn_item(t_case matrice[N][M]);

#endif
