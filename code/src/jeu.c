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
#include "liste_ptr_coord.h"
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
	/* take two copies - one for now, one for later */
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));
	/* register cleanup handler, and set the new terminal mode */
	atexit(reset_terminal_mode);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit(){
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

/***********************************************************************/
/*Fonction generation_level
*Initialise la map, genere les pieces, fait spawn les items,affiche la matrice de jeu
*Tout cela pour un niveau donne
*Permet l'affichage de matrice de jeu avec une difficulte differente
*/
void generation_level(t_case matrice[N][M], int level){
	//declaration
	int nb_piece;
	
	//traitement
	init_matrice(matrice);
	nb_piece=generer_matrice_tot(matrice,level);
	spawn_item(matrice,nb_piece,level);
	init_liste_mob(matrice);
	afficher_ecran(matrice,level);
}

/*************************************************************/
/*Fonction game_message
*Modifie la matrice de jeu et affiche le message "game over" ou "good game"
*/
void game_message(t_case matrice[N][M], int niveau_termine, int level){
	int i=0;
	int j=0;
	int valeur;
	FILE * fichier;
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
	
	//position de la sortie 3cases du coffre
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
		while(valeur_PV_personnage()>0 && niveau_termine==0 && ch != 27){ //tant que la vie>0 et niveau en cours
			while (!kbhit() && valeur_PV_personnage()>0 ){	
				//si personnage meurt, 3 coups ou les monstres sont inactifs pour se sauver
				if(valeur_invi_personnage()==0)
					generation_mob_suivante(matrice,perso_position);
				
				else{
					if(valeur_invi_personnage()<=3) modif_invi_personnage(valeur_invi_personnage()+1);
					else modif_invi_personnage(0);
				}
				afficher_ecran(matrice,level);
				usleep(150000);
				while(ch == 'p') ch = getch();
			}
			
			ch = getch();
			switch(ch){
				case 'z':
					dx=-1; 
					dy=0;
					break;
				case 'q':
					dx=0; 
					dy=-1;
					break;
				case 's':
					dx=1; 
					dy=0;
					break;
				case 'd':
					dx=0; 
					dy=1;
					break;
				default: 
					dx=0; 
					dy=0;
					break;	
			}	
		
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
							if(valeur_cle_personnage()==0){
								perso_position.x=perso_position.x-dx; //personnage ne bouge pas
								perso_position.y=perso_position.y-dy;
								mvprintw(41, nb_col-12,"veuillez prendre la cle");
							}
							else{
								matrice[perso_position.x-dx][perso_position.y-dy]=vide;
								mvprintw(42, nb_col-6,"coffre pris");
								matrice[perso_position.x][perso_position.y]=hero;
								//creation piece sortie
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
							gain_bonus_personnage(20);
							matrice[perso_position.x][perso_position.y]=hero;
							break;						
						case piege:
						case monstre_agressif:
						case monstre_defensif:
						case monstre_inactif:
							if(position_elt(perso_position)){
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
			game_message(matrice,niveau_termine,level);
		}
		else{
			level++;
			if(level<=5){
				init_etage_personnage();
				generation_level(matrice, level);
				jeu(matrice,level);
			}
			else game_message(matrice,niveau_termine,level);
		}
	}
}
