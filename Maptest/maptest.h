#ifndef MAP
#define MAP

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define N 40
#define M 100
#define nombre_piece 8
typedef enum{nord=0, sud, ouest, est} t_direction;
typedef enum{mur_contour=-1,mur,vide,porte,piege,hero,monstre} t_case;
typedef struct{int x;int y;} t_coord;
typedef struct{int x;int y;t_direction direction;} t_point;

void init_matrice(t_case matrice[N][M]);
void piece(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction_piece);
void couloir(int longueur,t_case matrice[N][M],int pt_x, int pt_y, t_direction direction_couloir);
void piece_ronde(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction_piece);
int verif_espace(int hauteur, int largeur, t_case matrice[N][M],int pt_x, int pt_y,t_direction direction_espace);
void generer_matrice_tot(t_case matrice[N][M]);
void afficher_matrice(t_case matrice[N][M]);


#endif
