#ifndef CLASSEMENT_H
    #define CLASSEMENT_H

    #include "plateau.h"
    #include "chainage.h"
    #include "affichage.h"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>

    // Trouve un joueur par son nom et retourne sa position
    int PositionJoueur(char* nom, const char classementsNom[][MAX_NOM], int nbJoueurs);

    // Tri le nouveau classement
    void TriInsertion(char classementsNom[][MAX_NOM], int classementsScore[], int nbJoueurs);

    // Ecris (si necessaire) dans le fichier 'classement.txt' pour le mettre a jour
    void EcrireClassement(char* nom, int score);

    // Affiche avec une certaine forme le classment
    void AfficherClassement(void);

    // Ajoute au score le nombre de points correspondant
    void AjouterPoint(int* score, char typeDeSuppression, int combo);
    

#endif /* CLASSEMENT_H */