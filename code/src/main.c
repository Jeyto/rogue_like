/**
    *\author PAVARD Valentin Gerbault Maxime Decrand Baptiste
    *\version 2.0
    *\date 17/12/2015
    *\mainpage Roguelike
    *\file main.c
    *\brief Fichier principale qui appelle les differentes fonctions crees pour le deroulement du jeu
            Permet soit de jouer au Roguelike et de choisir le niveau, soit de charger une partie sauvegardée ou quitter
*/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>
#include <ncurses.h>

#include "jeu.h"
#include "liste_mob.h"
#include "structure.h"
#include "sauvegarde.h"
#include "personnage.h"

int main(void){
   	srand(time(NULL));
	//declaration
	int ch, ch2;//choix de l'utilisateur
	int nb_col, col, row, level;
	t_case matrice[N][M];
	init_liste_mob();
	init_personnage();
	//declaration ncurses
	initscr();
  	noecho();
  	curs_set(FALSE);
 	keypad(stdscr, TRUE);
 	raw();
 	start_color();

 	/**********Affichage**********/
 	//couleur init ( hero portes )
 	init_pair(1, COLOR_WHITE, COLOR_BLACK);
 	//couleur mur
 	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
 	//couleur mur contour
 	init_pair(3, COLOR_WHITE, COLOR_BLACK);
 	// salle couloir
 	init_pair(4, COLOR_BLACK, COLOR_BLACK);
 	//monstres et pieges
 	init_pair(5, COLOR_RED, COLOR_BLACK);
 	// bonus
 	init_pair(6, COLOR_CYAN, COLOR_BLACK);
 	//vie hero
 	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
 	init_pair(8, COLOR_RED, COLOR_BLACK);
 	// objectifs ( sortie coffre cle )
 	init_pair(9, COLOR_GREEN, COLOR_BLACK);


	do{	//affichage du menu

		//traitement
		getmaxyx(stdscr,row,col); /* get the number of rows and columns */
		nb_col= col/2;


		attron(COLOR_PAIR(1)); //initialisation de la couleur d'affichage
		clear();
		mvprintw(0,nb_col-27,"*****************************************************");
		mvprintw(1,nb_col-27,"*     ROGUELIKE by Valentin - Baptiste - Maxime     *");
		mvprintw(2,nb_col-27,"*****************************************************");

		//affichage du menu
		mvprintw(4,nb_col-20,"Menu :");
		mvprintw(5,nb_col-20," 1 - Jouer");
		mvprintw(6,nb_col-20," 2 - Charger une partie sauvegardee");
		mvprintw(7,nb_col-20," 3 - Quitter");
		mvprintw(8,nb_col-18,"Votre choix : ");
		refresh();
		
		//choix du menu principal
		ch= getch();
		ch= ch-'0';

		//traitement du choix de l'utilisateur
		switch(ch){
			case 1 ://affichage du menu
				mvprintw(10,nb_col-20,"Menu des niveaux :");
				mvprintw(11,nb_col-20," 1 - Niveau 1");
				mvprintw(12,nb_col-20," 2 - Niveau 2");
				mvprintw(13,nb_col-20," 3 - Niveau 3");
				mvprintw(14,nb_col-20," 4 - Niveau 4");
				mvprintw(15,nb_col-20," 5 - Niveau 5");
				mvprintw(16,nb_col-20," 6 - Explication items");
				mvprintw(17,nb_col-20," 7 - Retour");
				mvprintw(18,nb_col-18,"Votre choix : ");
				refresh();
				
				//choix du niveau
				ch2= getch();
				ch2= ch2-'0';

				//traitement du choix de l'utilisateur
				switch(ch2){
					case 1:
						init_valeur_personnage();
						generation_level(matrice, 1);
						jeu(matrice,1);
						getch();
						break;
					case 2:
						init_valeur_personnage();
						generation_level(matrice, 2);
						jeu(matrice,2);
						getch();
						break;
					case 3:
						init_valeur_personnage();
						generation_level(matrice, 3);
						jeu(matrice,3);
						getch();
						break;
					case 4:
						init_valeur_personnage();
						generation_level(matrice, 4);
						jeu(matrice,4);
						getch();
						break;
					case 5:
						init_valeur_personnage();
						generation_level(matrice, 5);
						jeu(matrice,5);
						getch();
						break;
					case 6:
						
						//affichage de la légende dans les menus avec la couleur
						attron(COLOR_PAIR(2));
						mvprintw(20,nb_col-20,"X: mur infranchissable");

						attron(COLOR_PAIR(3));
						mvprintw(21,nb_col-20,"&: Contour des pieces infranchissable");

						attron(COLOR_PAIR(1));
						mvprintw(22,nb_col-20,"(vide): Deplacement autorise");
						mvprintw(23,nb_col-20,"P: porte");
						mvprintw(24,nb_col-20,"@: hero");

						attron(COLOR_PAIR(9));
						mvprintw(25,nb_col-20,"K: cle");
						mvprintw(26,nb_col-20,"C: coffre");
						mvprintw(27,nb_col-20,"S: sortie");

						attron(COLOR_PAIR(5));
						mvprintw(28,nb_col-20,"^: piege");
						mvprintw(29,nb_col-20,"M: monstre agressif");
						mvprintw(30,nb_col-20,"D: monstre defensif");
						mvprintw(31,nb_col-20,"I: monstre inactif");

						attron(COLOR_PAIR(6));
						mvprintw(32,nb_col-20,"?: bonus");

						refresh();
						getch();
						attron(COLOR_PAIR(1));
						break;
					case 7:
						clear();
						break;

					default:
						mvprintw(19,nb_col-20,"Erreur: votre choix devait être compris entre 1 et 7");
						getch();
				}
				break;	
			case 2:
				level=generer_map_sauvegarde(matrice);
				jeu(matrice,level);
				break;
			case 3:
				break;
			default:
				mvprintw(9,nb_col-20,"Erreur: votre choix doit être compris entre 1 et 3");
				getch();
		}
	}while(ch!=3);

	endwin();
	return 0;
}
