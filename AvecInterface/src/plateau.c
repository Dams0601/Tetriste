/* GESTION DU PLATEAU */

#include "../hdr/plateau.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

Plateau* InitialiserPlateau(void){
    Plateau* plateau = malloc(sizeof(Plateau));
    if (plateau==NULL){
        return NULL;
    }
    // Mettre qu'il n'y a pas de premier pour l'instant
    plateau->premier = NULL;
    // Initialiser la taille max et la cardinal
    plateau->card = 0;
    plateau->tailleMax = MAX_PIECES; // MAX_PIECES etant fixe par l'enonce à 15
    return plateau;
}

Piece* RechercherDernier(Plateau* plateau){
    Piece* actuel = plateau->premier;
    // Si le plateau n'a aucun ou un element
    if (plateau->card == 0 || plateau->card == 1){
        return plateau->premier;
    }
    // Sinon on passe au suivant
    actuel = actuel->suiv;
    // On parcourt toute la liste pour atteindre le "dernier" (:= l'element le plus a droite)
    while (actuel != plateau->premier){
        if (actuel->suiv == plateau->premier){
            return actuel;
        }
        actuel = actuel->suiv;
    }
    return actuel;
}

Piece* TrouverDernierForme(Plateau* plateau, char nouvelleForme){
    // CAS : Aucune piece sur le plateau
    if (plateau->card == 0){
        return NULL; // return NULL
    }
    // CAS : Une piece sur le plateau
    else if (plateau->card == 1){
        // Si la seule piece presente a la "bonne" forme
        if (plateau->premier->forme == nouvelleForme){
            return plateau->premier->precForme;
        }
        else {
            return NULL;
        }
    }
    // Teste le premier element
    Piece* tmp = plateau->premier;
    if (tmp->forme == nouvelleForme){
            return plateau->premier->precForme;
    }
    // Passe au suivant
    tmp = tmp->suiv; // On se place sur le deuxieme element
    if (tmp==NULL){
        return NULL;
    }
    // Plus de deux elements dans le tableau
    while(tmp->forme != nouvelleForme && tmp!=plateau->premier){
        tmp = tmp->suiv;
    }
    // On a parcouru toute la liste et on est revenu au debut
    if (tmp==plateau->premier){
        return NULL;
    }
    // Sinon
    else {
        return tmp->precForme;
    }
}

Piece* TrouverDernierCouleur(Plateau* plateau, char nouvelleCouleur){
    Piece* tmp = plateau->premier;
    Piece* dernier = NULL;
    // CAS : Aucune piece sur le plateau
    if (plateau->card == 0){
        return dernier; // return NULL
    }
    // CAS : Une piece sur le plateau
    else if (plateau->card == 1){
        // Si la seule piece presente a la "bonne" couleur
        if (plateau->premier->couleur == nouvelleCouleur){
            return plateau->premier->precCouleur;
        }
        else {
            return NULL;
        }
    }
    // Teste le premier element
    if (tmp->couleur == nouvelleCouleur){
        return plateau->premier->precCouleur;
    }
    tmp = tmp->suiv; // On se place sur le deuxieme element
    if (tmp==NULL){
        return NULL;
    }
    // Plus de deux elements dans le tableau
    while(tmp->couleur != nouvelleCouleur && tmp!=plateau->premier){
        tmp = tmp->suiv;
    }
    // On a parcouru tous les elements et on est revenu au debut
    if (tmp==plateau->premier){
        return NULL;
    }
    else {
        return tmp->precCouleur; // Retourner le precedent en couleur du premier := le dernier de cette couleur
    }
}
