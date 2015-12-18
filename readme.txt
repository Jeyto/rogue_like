				  JEU ROGUELIKE
	    cr�� par PAVARD VALENTIN, DECRAND BAPTISTE, GERBAULT MAXIME
*********************************************************************************
*										*
*  		    Bienvenue dans la notice du jeu ROGUELIKE			*
*										*
*********************************************************************************

I]Fonctions et dossiers
---------------------------------------------------------------------------------
Toutes les fonctions fonctionnent correctement. Elles ont �t� test�es sur Linux 
et Mac. Dans l'archive, vous aurez acc�s �:
-un dossier Doxygen
-un dossier code contenant:
	-un dossier bin contenant l�ex�cutable du jeu
	-un dossier include contenant tous les *.h du code
	-un dossier src contenant tous les *.c du code
	-un makefile contenant les commandes de compilation
	-trois fichiers .txt contenant la sauvegarde ou des fichiers utiles au 
	jeu.

II]Lancement du programme
---------------------------------------------------------------------------------
L'objet de ce document est de vous aider � executer le fichier executable afin de
pouvoir jouer au ROGUELIKE.
-Tout d'abord, vous avez r�cup�r� une archive poss�dant tous les dossiers et 
fichiers utiles pour le bon developpement du jeu.
-Il vous suffira d'ouvrir votre terminal, et de ce placer dans le dossier code.
-Une fois � l'int�rieur de ce dossier, executez la commande: "make", afin de 
lancer un makefile contenant toutes les commandes de compilation du programme.
-Grace � ce makefile, l'executable du jeu se trouvera dans le fichier "bin". Il 
vous faut alors executer la commande suivante dans le terminal afin de se placer
dans le fichier contenant l'executable: "cd bin".
-A ce stade, il ne vous reste qu'� executer la commande suivante et de jouer au
ROGUELIKE: "main.exe".
-Vous aurez alors acces � un menu de 3possibilit�s o� vous pourrez jouer, charger
une partie sauvegard�e ou tout simplement quitter.
-Ensuite, en executant la commande "make clean" vous pouvez supprimer tous les *.o
et .gch.