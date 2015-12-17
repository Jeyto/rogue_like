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
*Permet de convertir un entier en fonction de sa valeur dans un enum
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
	//sauvegarde personnage et valeur
	fprintf(fichier,"%i ",level);
	fprintf(fichier,"%i ",perso.score_bonus);
	fprintf(fichier,"%i ",perso.PV);
	fprintf(fichier,"%i %i ",perso.position.x,perso.position.y);
	fprintf(fichier,"%i ",perso.cle);
	fprintf(fichier,"%i \n",perso.invisible);
	//sauvegarde monstre
	en_tete();
	while(!hors_liste_mob()){
		valeur_mob(&mob);
		fprintf(fichier,"%i ",mob.PV);
		fprintf(fichier,"%i %i ",mob.position.x,mob.position.y);
		fprintf(fichier,"%i \n",mob.race_mob);
		suivant();
	}
	fprintf(fichier,"-1 \n");
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
*generer map à partir d'un fichier txt
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
	//recuperation personnage
	fscanf(fichier,"%i",&level);
	fscanf(fichier,"%i",&perso_save.score_bonus);
	fscanf(fichier,"%i",&perso_save.PV);
	fscanf(fichier,"%i %i",&perso_save.position.x,&perso_save.position.y);
	fscanf(fichier,"%i",&perso_save.cle);
	fscanf(fichier,"%i",&perso_save.invisible);
	modif_personnage(perso_save);
	//recuperation mob
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
	while(!feof(fichier)){
		fscanf(fichier,"%i",&valeur);
		convertion_int_enum(matrice,i,j,valeur);
		j++;
	}
	fclose(fichier);
	afficher_ecran(matrice,level);
	return level;
}
