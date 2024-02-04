#ifndef IA_H
    #define IA_H

    #include "plateau.h"
    #include "chainage.h"
    #include "classement.h"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>

    // Simule la disparition de pièce
    void DisparaitrePiecesBis(Plateau* plateau, int* score, char typeDeSuppression, char* nom, Piece* tabPieces[], int combo);

    // Une version modifiee et adaptee pour la simulation
    void LibererMemoire2(Plateau* plateau);

    // Cree une copie du plateau
    void CreerCopiePlateau(const Plateau* plateau, Plateau* nouveauPlateau);

    // Recherche le score maximal minimisant le nombre de coups
    int RechercherMax(int tabScore[], int tabCoups[]);

    // Affiche le conseil propose par l'ia
    void AfficherConseil(int indMax, int tabScore[], int tabCoups[]);

    // Calcule tous les coups
    int IntelligenceArtificielle(const Plateau* plateau, Piece* tabPieces[], int* score, char* nom, int tabCoups[], int tabScore[]);

#endif /* IA_H */