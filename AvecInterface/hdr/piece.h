#ifndef PIECE_H
    #define PIECE_H

    #define POINT_AJOUT 10
    #define POINT_DECALAGE 30
    #define MAX_PIECES 15
    #define MAX_JOUEURS 10
    #define MAX_NOM 50

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>

    // Structure pour representer une piece
    typedef struct Piece {
        char forme; // sa forme
        char couleur; // sa couleur
        struct Piece* suivForme; // suivant en forme
        struct Piece* precForme; // precedant en forme
        struct Piece* suivCouleur; // suivant en couleur
        struct Piece* precCouleur; // precedant en couleur
        struct Piece* suiv; // suivant dans l’ordre de la liste chaînee
    } Piece;

    // Initialise une piece avec une forme et une couleur donnees
    Piece* InitialiserPiece(char forme, char couleur);

    // Genere une piece aleatoire
    Piece* GenererPieceAleatoire(void);

#endif /* PIECE_H */