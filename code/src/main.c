#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <unistd.h>
#include <ncurses.h>

#include "jeu.h"
#include "liste_ptr_coord.h"
#include "structure.h"
#include "sauvegarde.h"


int main(void){
   	srand(time(NULL));
	//declaration
	int ch, ch2;//choix de l'utilisateur
	int nb_col, col, row, level;	
	t_case matrice[N][M];
	init_liste();
	init_personnage();
	//declaration ncurses
	initscr();
  	noecho();
  	curs_set(FALSE);
 	keypad(stdscr, TRUE);
 	raw();
	
	do{	//affichage du menu
		
		//traitement
		getmaxyx(stdscr,row,col); /* get the number of rows and columns */
		nb_col= col/2;
		
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
						mvprintw(20,nb_col-20,"&: Contour des pieces infranchissable");
						mvprintw(21,nb_col-20,"X: mur infranchissable");
						mvprintw(22,nb_col-20,"(vide): Deplacement autorise");
						mvprintw(23,nb_col-20,"P: porte");
						mvprintw(24,nb_col-20,"@: hero");
						mvprintw(25,nb_col-20,"K: cle");
						mvprintw(26,nb_col-20,"C: coffre");
						mvprintw(27,nb_col-20,"^: piege");
						mvprintw(28,nb_col-20,"M: monstre agressif");
						mvprintw(29,nb_col-20,"D: monstre defensif");
						mvprintw(30,nb_col-20,"I: monstre inactif");
						mvprintw(31,nb_col-20,"?: bonus");
						
						refresh();
						getch();
						break;
					case 7: 
						clear(); 
						break;
						
					default:
						mvprintw(19,nb_col-20,"Erreur: votre choix doit être compris entre 1 et 7");
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
		}
	}while(ch!=3);
	
	endwin();
	return 0;
}
