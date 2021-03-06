/**	
	*\file sauvegarde.c
    *\brief Fonctions gerant la sauvegarde et la partie sauvegardee
    *\author PAVARD Valentin Gerbault Maxime Decrand Baptiste
    *\version 2.0
    *\date 17/12/2015

    *\fn void convertion_int_enum(t_case matrice[N][M], int i, int j, int valeur)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		int i est le numero de la ligne
    		int j est le numero de la colonne
    		int valeur est l'entier a convertir
    *\brief Permet de convertir un entier en fonction de sa valeur dans une enumeration
			Modifie la valeur de la case matrice[i][j] en fonction de l'entier valeur
    *\return void
    *\fn void convertion_int_enum_monstre(t_mob * mob,int valeur)
    *\param t_mob * mob est la structure ou l'on modifie la race du monstre directement
    		int valeur est l'entier a convertir
    *\brief Permet de convertir un entier en fonction de sa valeur dans une enumeration
			Modifie la race d'un monstre en fonction de l'entier valeur
    *\return void
    *\fn void sauvegarde_map(t_case matrice[N][M],int level)
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    		int level est le niveau de la partie actuelle (difficulte)
    *\brief Ecriture de la map(matrice) dans le fichier txt
			Sauvegarde des données du personnage et des monstres
    *\return void
    *\fn int generer_map_sauvegarde(t_case matrice[N][M])
    *\param t_case grille[N][M], matrice de taille N*M representant chaque case jouable
    *\brief Generer map à partir d'un fichier txt
			Recuperation des valeurs du pesonnage et des monstres
    *\return level, le niveau de la partie sauvegardee
*/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "IA.h"
#include "jeu.h"
#include "liste_mob.h"
#include "map.h"
#include "structure.h"
#include "sauvegarde.h"

/*****************************************************************/
/*Fonction convertion_int_enum
*Permet de convertir un entier en fonction de sa valeur dans une enumeration
*Modifie la valeur de la case matrice[i][j] en fonction de l'entier valeur
*/
void convertion_int_enum(t_case matrice[N][M], int i, int j, int valeur){
	switch(valeur){
		case 0: matrice[i][j]=mur_contour; break;
		case 1: matrice[i][j]=mur; break;
		case 2: matrice[i][j]=vide; break;
		case 3: matrice[i][j]=couloir; break;
		case 4: matrice[i][j]=porte; break;
		case 5: matrice[i][j]=coffre; break;
		case 6: matrice[i][j]=cle; break;
		case 7: matrice[i][j]=bonus; break;
		case 8: matrice[i][j]=piege; break;
		case 9: matrice[i][j]=hero; break;
		case 10: matrice[i][j]=monstre_agressif; break;
		case 11: matrice[i][j]=monstre_defensif; break;
		case 12: matrice[i][j]=monstre_inactif; break;
		case 13: matrice[i][j]=sortie; break;
	}
}

/*Fonction convertion_int_enum
*Permet de convertir un entier en fonction de sa valeur dans une enumeration
*Modifie la race d'un monstre en fonction de l'entier valeur
*/
void convertion_int_enum_monstre(t_mob * mob,int valeur){
	switch(valeur){
		case 10: mob->race_mob=monstre_agressif; break;
		case 11: mob->race_mob=monstre_defensif; break;
		case 12: mob->race_mob=monstre_inactif; break;
	}
}

/*****************************************************************/
/*Fonction sauvedarde_map
*Ecriture de la map(matrice) dans le fichier txt
*Sauvegarde des données du personnage et des monstres
*/
void sauvegarde_map(t_case matrice[N][M],int level){
	//declaration
	int i,j;
	t_personnage perso;
	valeur_personnage(&perso);
	t_mob mob;
	FILE * fichier;

	//traitement
	fichier=fopen("save_map.txt","w");
	//sauvegarde personnage(score, vie, position, objectif)
	fprintf(fichier,"%i ",level);
	fprintf(fichier,"%i ",perso.score_bonus);
	fprintf(fichier,"%i ",perso.PV);
	fprintf(fichier,"%i %i ",perso.position.x,perso.position.y);
	fprintf(fichier,"%i ",perso.cle);
	fprintf(fichier,"%i \n",perso.invisible);
	//sauvegarde monstre(vie, position, race)
	en_tete();
	while(!hors_liste_mob()){
		valeur_mob(&mob);
		fprintf(fichier,"%i ",mob.PV);
		fprintf(fichier,"%i %i ",mob.position.x,mob.position.y);
		fprintf(fichier,"%i \n",mob.race_mob);
		suivant();
	}
	fprintf(fichier,"-1 \n"); //marqueur pour la fin de la liste utilisé dans la fonction suivante
	//sauvegarde de la matrice
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			fprintf(fichier,"%i ",matrice[i][j]);
		}
		fprintf(fichier,"\n");
	}
	fclose(fichier);
}

/*******************************************************************/
/*Fonction generer_map_sauvegarde
*Generer map à partir d'un fichier txt
*Recuperation des valeurs du pesonnage et des monstres
*/
int generer_map_sauvegarde(t_case matrice[N][M]){
	//declaration
	int i=0;
	int j=0;
	int level;
	int valeur;
	int valeur_mob;
	init_personnage();
	t_personnage perso_save;
	t_mob mob;
	FILE * fichier;

	//traitement
	fichier=fopen("save_map.txt","r");
	//recuperation personnage et ses caracteristiques
	fscanf(fichier,"%i",&level);
	fscanf(fichier,"%i",&perso_save.score_bonus);
	fscanf(fichier,"%i",&perso_save.PV);
	fscanf(fichier,"%i %i",&perso_save.position.x,&perso_save.position.y);
	fscanf(fichier,"%i",&perso_save.cle);
	fscanf(fichier,"%i",&perso_save.invisible);
	modif_personnage(perso_save);
	//recuperation mob et remplissage de la liste
	vider_liste_mob();
	en_tete();
	fscanf(fichier,"%i \n",&mob.PV);
	while(mob.PV!=-1){
		fscanf(fichier,"%i %i\n",&mob.position.x,&mob.position.y);
		fscanf(fichier,"%i \n",&valeur_mob);
		convertion_int_enum_monstre(&mob,valeur_mob);
		ajout_droit(mob);
		fscanf(fichier,"%i \n",&mob.PV);
	}
	//remplissage de la matrice
	while(!feof(fichier)){
		fscanf(fichier,"%i",&valeur);
		convertion_int_enum(matrice,i,j,valeur);
		j++;
	}
	fclose(fichier);
	afficher_ecran(matrice,level);
	return level;
}
