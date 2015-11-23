#ifndef MAP
#define MAP

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define N 30
#define M 40
typedef enum{nord, sud, ouest, est} t_direction;

void init_matrice(char matrice[N][M]);
void afficher_matrice(char matrice[N][M]);
void piece(int H, int L, char matrice[N][M],int x, int y);
void couloir(int L, t_direction direction,char matrice[N][M],int x, int y);
void generer_matrice(char matrice[N][M]);


#endif
