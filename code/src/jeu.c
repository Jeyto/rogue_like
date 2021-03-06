/**	
	*\file jeu.c
    *\brief Fonctions gerant le jeu en lui-meme, deplacement monstre et joueur
    *\author PAVARD Valentin Gerbault Maxime Decrand Baptiste
    *\version 2.0
    *\date 17/12/2015

    *\fn void generation_level(t_case matrice[N][M], int level)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		int level est le niveau de difficulte
    *\brief Fonction generation_level
			Initialise la map, genere les pieces, fait spawn les items, affiche la matrice de jeu
			Tout cela pour un niveau donne
			Permet l'affichage de la matrice de jeu avec une difficulte differente
    *\return void
    *\fn void game_message(t_case matrice[N][M], int niveau_termine, int level)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		int niveau_termine est la valeur de fin de partie: 0 le joueur a perdu, 1 le joueur a gagne
    		int level est le niveau de difficulte
    *\brief Modifie la matrice de jeu et affiche le message "game over" ou "good game"
    *\return void
    *\fn void jeu(t_case matrice[N][M], int level)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		int level est le niveau de difficulte
    *\brief Gere le jeu en lui-meme
			Deplacement des monstres en fonctions du temps
			Deplacement du joueur et traitement de son deplacement
    *\return void   
*/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>

#include <ncurses.h>
#include <string.h>
#include <sys/select.h>
#include <termios.h>

#include "IA.h"
#include "jeu.h"
#include "liste_mob.h"
#include "map.h"
#include "sauvegarde.h"
#include "structure.h"
#include "personnage.h"

/******************Fonction ncurses******************************/
struct termios orig_termios;

void reset_terminal_mode(){
	tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode(){
	struct termios new_termios;
	/* fais deux copies, une pour maintenant et une pour plus tard */
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));
	/* met les parametres de base, puis configure de nouveaux parametres */
	atexit(reset_terminal_mode);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
}

//fonction permettant de savoir si le joueur appuie sur une touche
int kbhit(){
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

/***********************************************************************/
/*Fonction generation_level
*Initialise la map, genere les pieces, fait spawn les items, affiche la matrice de jeu
*Tout cela pour un niveau donne
*Permet l'affichage de la matrice de jeu avec une difficulte differente
*/
void generation_level(t_case matrice[N][M], int level){
	//declaration
	int nb_piece;

	//traitement
	init_matrice(matrice);
	nb_piece=generer_matrice_tot(matrice,level);
	spawn_item(matrice,nb_piece,level);
	init_carac_mob(matrice);
	afficher_ecran(matrice,level);
}

/*************************************************************/
/*Fonction game_message
*Modifie la matrice de jeu et affiche le message "game over" ou "good game"
*/
void game_message(t_case matrice[N][M], int niveau_termine, int level){
	//declaration
	int i=0;
	int j=0;
	int valeur;
	FILE * fichier;
	
	//traitement en fonction du resultat du jeu
	if(niveau_termine==0) fichier=fopen("map_game_over.txt","r");
	else fichier=fopen("map_game_win.txt","r");
	//si aucun fichier de ce nom, affiche matrice rempli de mur
	if(fichier==NULL){
		init_matrice(matrice);
	}
	else{
		while(!feof(fichier)){
			fscanf(fichier,"%i",&valeur);
			convertion_int_enum(matrice,i,j,valeur);
			j++;
		}
		fclose(fichier);
	}
	afficher_ecran(matrice,level);
	getch();
}

/******************************************************************/
/*Fonction jeu
*Gere le jeu en lui-meme
*Deplacement des monstres en fonctions du temps
*Deplacement du joueur et traitement de son deplacement
*/
void jeu(t_case matrice[N][M], int level){
	//declaration ncurses
	int nb_col, col, row;
	int ch = 0;
	getmaxyx(stdscr,row,col); /* get the number of rows and columns */
	nb_col= col/2;
	//declaration
	int dx, dy;
	int i,j;
	t_coord pos_sortie;
	t_coord perso_position;
	int niveau_termine=0;

	//position de la sortie à 3cases du coffre mais invisible
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(matrice[i][j]==coffre){
				pos_sortie.x=i;
				pos_sortie.y=j-3;
			}
		}
	}

	//traitement
	if(level>=1){
		sauvegarde_map(matrice,level);
		//tant que la vie > 0 et niveau en cours et qu'on appuye pas sur echap
		while(valeur_PV_personnage()>0 && niveau_termine==0 && ch != 27){ 
			//Deplacment des monstres en fonction du temps
			while (!kbhit() && valeur_PV_personnage()>0 ){//tant que l'on n'appuie sur aucune touche, kbhit fais boucler
				//si personnage meurt, 3 coups pour se sauver car les monstres sont inactifs
				if(valeur_invi_personnage()==0)
					generation_mob_suivante(matrice,perso_position);

				else{
					if(valeur_invi_personnage()<=3) modif_invi_personnage(valeur_invi_personnage()+1);						
					else modif_invi_personnage(0);
				}
				//affichage du jeu avec uen temporisation de 1,5s, avec la touche p pour mettre le jeu en pause
				afficher_ecran(matrice,level);
				usleep(150000);
				while(ch == 'p') ch = getch();
			}
			//choix de deplacement (deplacement possible avec les touches zqsd, ZQSD ou les fleches directives)
			ch = getch();
			switch(ch){
				
				case 'z':
				case 'Z':
				case KEY_UP:
					dx=-1;
					dy=0;
					break;
				
				case 'q':
				case 'Q':
				case KEY_LEFT:
					dx=0;
					dy=-1;
					break;
				
				case 's':
				case 'S':
				case KEY_DOWN:
					dx=1;
					dy=0;
					break;
				
				case 'd':
				case 'D':
				case KEY_RIGHT:
					dx=0;
					dy=1;
					break;
				
				default:
					dx=0;
					dy=0;
					break;
			}
			//si deplacement choisi, traitement de la case
			if(dx != 0 || dy != 0){
				valeur_position_personnage(&perso_position);

				if(matrice[perso_position.x+dx][perso_position.y+dy]!=mur_contour && matrice[perso_position.x+dx][perso_position.y+dy]!=mur){
					perso_position.x=perso_position.x+dx;
					perso_position.y=perso_position.y+dy;
					//action en fonction de la nouvelle case

					switch(matrice[perso_position.x][perso_position.y]){
						case vide:
							matrice[perso_position.x-dx][perso_position.y-dy]=vide;
							matrice[perso_position.x][perso_position.y]=hero;
							break;
						case couloir:
							matrice[perso_position.x-dx][perso_position.y-dy]=vide;
							matrice[perso_position.x][perso_position.y]=hero;
							break;
						case porte:
							matrice[perso_position.x-dx][perso_position.y-dy]=vide;
							perso_position.x=perso_position.x+dx;
							perso_position.y=perso_position.y+dy;
							matrice[perso_position.x][perso_position.y]=hero;
							break;
						case cle:
							matrice[perso_position.x-dx][perso_position.y-dy]=vide;
							modif_cle_personnage(1);
							mvprintw(41, nb_col-5,"cle prise");
							matrice[perso_position.x][perso_position.y]=hero;
							break;
						case coffre:
							if(valeur_cle_personnage()==0){	//s'il n'a pas la cle
								perso_position.x=perso_position.x-dx; //personnage ne bouge pas
								perso_position.y=perso_position.y-dy;
								mvprintw(41, nb_col-12,"veuillez prendre la cle");
							}
							else{
								matrice[perso_position.x-dx][perso_position.y-dy]=vide;
								mvprintw(42, nb_col-6,"coffre pris");
								matrice[perso_position.x][perso_position.y]=hero;
								//creation piece sortie pour finir le niveau
								matrice[pos_sortie.x][pos_sortie.y]=sortie;
								matrice[pos_sortie.x-2][pos_sortie.y]=porte;
								matrice[pos_sortie.x-2][pos_sortie.y-1]=mur_contour;
								matrice[pos_sortie.x-2][pos_sortie.y+1]=mur_contour;
								matrice[pos_sortie.x-1][pos_sortie.y]=vide;
								matrice[pos_sortie.x-1][pos_sortie.y-1]=mur_contour;
								matrice[pos_sortie.x-1][pos_sortie.y+1]=mur_contour;
								matrice[pos_sortie.x][pos_sortie.y-1]=mur_contour;
								matrice[pos_sortie.x][pos_sortie.y+1]=mur_contour;
							}
							break;
						case bonus:
							matrice[perso_position.x-dx][perso_position.y-dy]=vide;
							if(rand()%3==0){//une chance sur 3 d'avoir un point d'armure
								gain_armure_personnage(1);
							}
							else{
								gain_bonus_personnage(20); //le bonus vaut 20points
							}
							matrice[perso_position.x][perso_position.y]=hero;
							break;
						case piege:
							degat_personnage();//perd un point de vie
							perso_position.x=perso_position.x-dx; //personnage ne bouge pas
							perso_position.y=perso_position.y-dy;
							break;
						case monstre_agressif:
						case monstre_defensif:
						case monstre_inactif:
							if(position_mob(perso_position)){
								mob_perte_PV(matrice,1);
							}
							perso_position.x=perso_position.x-dx; //personnage ne bouge pas
							perso_position.y=perso_position.y-dy;

							break;
						case sortie:
							niveau_termine=1;
							break;
						default:
							break;
					}
					modif_position_personnage(perso_position);
					afficher_ecran(matrice,level);
				}
			}
		}
		if(niveau_termine==0){
			game_message(matrice,niveau_termine,level); //defaite
		}
		else{
			level++;
			//generation niveau superieur
			if(level<=5){
				init_etage_personnage();
				generation_level(matrice, level);
				jeu(matrice,level);
			}
			//si niveau 5 termine, victoire
			else game_message(matrice,niveau_termine,level);
		}
	}
}
