#ifndef CHAINAGE_H
    #define CHAINAGE_H

    #include "plateau.h"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>

    // Supprime de la liste doublement chainee 'FORME'
    void SupprimerForme(Piece* piece);

    // Supprime de la liste doublement chainee 'COULEUR'
    void SupprimerCouleur(Piece* piece);

    // Supprime 3 pieces consecutives identiques par leur couleur/forme
    void DisparaitrePieces(Plateau* plateau, int* score, char typeDeSuppression, char* nom, Piece* tabPieces[], int combo);

    // Decale sur le plateau selon la forme
    void DecalageForme(Plateau* plateau, char forme);

    // Decale sur le plateau selon la couleur
    void DecalageCouleur(Plateau* plateau, char couleur);

    // Insere une piece à droite
    void InsererDroite(Plateau* plateau, Piece* piece);

    // Insere une piece à gauche
    void InsererGauche(Plateau* plateau, Piece* piece);

    // Libere la memoire allouee pour les pieces et le plateau
    void LibererMemoire(Plateau* plateau);

#endif /* CHAINAGE_H */