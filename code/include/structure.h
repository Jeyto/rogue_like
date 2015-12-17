#ifndef STRUCT
#define STRUCT

/**
	*\struct t_direction
    *\brief Enumeration contenant les quatres directions possibles lors d'un placement d'une porte
	*\struct t_case
    *\brief Enumeration contenant tous les items possibles dans une case de la matrice(items et decors)
    *\struct t_coord
    *\brief Structure qui contient un entier indiquant la ligne, un entier indiquant la colonne. Cette structure represente une coordonnees d'une case.
    *\struct t_personnage
    *\brief Structure listant toutes les caractéristiques du personnage(vie, score, position, cle, invisible, armure)
    *\struct t_pos
    *\brief Structure contenant les coordonnees de depart et d'arrivee d'une piece
    *\struct t_mob
    *\brief Structure listant toutes les caractéristiques d'un mosntre(vie, position, race)
    *\struct t_element
    *\brief Structure representant un element de la liste
*/
    
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define N 40
#define M 120
#define t_max N*M

typedef enum{nord=0, sud, ouest, est} t_direction;

typedef enum{mur_contour=0,mur,vide,couloir,porte,coffre,cle,bonus,piege,hero,monstre_agressif,monstre_defensif,monstre_inactif,sortie} t_case;

typedef struct{int x;int y;} t_coord;

typedef struct{int PV; int score_bonus;t_coord position; int cle;int invisible;int armure;}t_personnage;

typedef struct{int x_D;int y_D;int x_A;int y_A;} t_pos;

typedef struct{int PV; t_coord position; t_case race_mob;} t_mob;

typedef struct element{t_mob valeur;struct element *pred;struct element *succ;} t_element;

#endif
