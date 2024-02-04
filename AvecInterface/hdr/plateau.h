#ifndef PLATEAU_H
    #define PLATEAU_H

    #include "piece.h"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>

    // Structure pour representer le plateau de jeu
    typedef struct Plateau {
        Piece* premier;
        int card; // Nombre d'elements actuellement dans la liste
        int tailleMax; // Taille max de la chaîne qui peut être actualisee avec un realloc
    } Plateau;

    // Initialise Le plateau vide
    Plateau* InitialiserPlateau(void);

    // Affiche le plateau
    void AfficherPlateau(Plateau* plateau);

    // Trouve et renvoie le dernier element (le plus a droite) du plateau
    Piece* RechercherDernier(Plateau* plateau);

    // Trouve et renvoie le dernier ayant la forme de la piece a inserer
    Piece* TrouverDernierForme(Plateau* plateau, char forme);

    // Trouve et renvoie le dernier ayant la couleur de la piece a inserer
    Piece* TrouverDernierCouleur(Plateau* plateau, char couleur);

#endif /* PLATEAU_H */