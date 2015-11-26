#ifndef MAP
#define MAP

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define N 20
#define M 40
typedef enum{nord=0, sud, ouest, est} t_direction;

void init_matrice(char matrice[N][M]);
void afficher_matrice(char matrice[N][M]);
void piece(int hauteur, int largeur, char matrice[N][M],int pt_x, int pt_y);
void couloir(int longueur, t_direction direction,char matrice[N][M],int pt_x, int pt_y);
void generer_matrice(char matrice[N][M]);


#endif
