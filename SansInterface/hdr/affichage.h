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

    // Affiche une piece en fonction de sa couleur avec le code UNICODE correspondant
    void AfficherCouleur(Piece* piece);

    void AfficherPlateau(Plateau* plateau);

    // Affiche l'ecran principale ou est visible le nomdu joueur, le score, les prochaines pieces et le plateau
    void AfficherJeu(char nom[], int* score, Piece* tabPieces[], Plateau* plateau);

    // Affiche le texte (passe en argument) avec un effet de chargement
    void EffetChargement(char* texte);

    // Affiche et renvoie la reponse de l'utilisateur pour savoir s'il veut inserer, decaler ou sauvegarder
    char ChoixUtilisateur(char nom[], int* score, Piece* tabPieces[], Plateau* plateau, char res2);

    // Affiche le logo du jeu
    void Logo(void);

    // Affiche et gere le deroulement du jeu
    int DeroulementJeu(char nom[], int* score, Plateau* plateau, char* res, Piece* tabPieces[], char res2);


#endif /* AFFICHAGE_H */
