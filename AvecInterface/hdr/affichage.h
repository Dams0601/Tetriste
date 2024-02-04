#ifndef AFFICHAGE_H
    #define AFFICHAGE_H

    #include "plateau.h"
    #include "chainage.h"
    #include "classement.h"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>
    #include <MLV/MLV_all.h>
    
    extern int quitter;
    extern MLV_Image *image;
    


    // Affiche une piece en fonction de sa couleur avec le code UNICODE correspondant
    



    // Affiche le texte (passe en argument) avec un effet de chargement
    void EffetChargement(char* texte);

    // Affiche et renvoie la reponse de l'utilisateur pour savoir s'il veut inserer, decaler ou sauvegarder
    char ChoixUtilisateur(char nom[], int* score, Piece* tabPieces[], Plateau* plateau);

    // Affiche le logo du jeu
    void Logo(void);

    // Affiche et gere le deroulement du jeu
    int DeroulementJeu(char nom[], int* score, Plateau* plateau, char* res, Piece* tabPieces[]);

	void dessine_pieces_plateau(char shapes[], char colors[], int size);
	void RecupPlateau(Plateau* plateau);
	void BoiteDeTexte(const char* text);
	void BoiteDeTexte1(const char* text);
	void RecupSuiv(Piece* tabPieces[]);
	void AfficherScore(const int* score);
	void gameOver(void);
	void sauvegarde(void);


#endif /* AFFICHAGE_H */
