#define N 7
#define M 7
#define t_max N*M
#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
typedef enum{vide,mur,joueur,ennemi}t_cellule;

typedef struct{int x; int y;}t_coord;
typedef struct element{t_coord valeur;struct element *pred;struct element *succ;} t_element;

#endif
