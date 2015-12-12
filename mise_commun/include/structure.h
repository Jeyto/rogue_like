#ifndef struc
#define struc

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define N 40
#define M 120
#define t_max N*M
typedef enum{nord=0, sud, ouest, est} t_direction;
typedef enum{mur_contour=0,mur,vide,couloir,porte,coffre,cle,bonus,piege,hero,monstre_agressif,monstre_defensif,monstre_inactif,sortie} t_case;
typedef struct{int x;int y;} t_coord;
typedef struct{int PV; int score_bonus;t_coord position_spawn;}t_personnage;
typedef struct{int x_D;int y_D;int x_A;int y_A;} t_pos;
typedef struct element{t_coord valeur;struct element *pred;struct element *succ;} t_element;

#endif
