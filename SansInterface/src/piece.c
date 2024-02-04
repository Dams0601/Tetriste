/* GESTION DE LA PIECE */

#include "../hdr/piece.h"

Piece* InitialiserPiece(char nouvelleForme, char nouvelleCouleur){
    Piece* piece = malloc(sizeof(Piece));
    if (piece==NULL){
        return NULL;
    }
    // Mettre aux arguments forme et couleur
    piece->forme = nouvelleForme;
    piece->couleur = nouvelleCouleur;
    // Mettre à NULL pour le suivant sur le plateau
    piece->suiv = NULL;
    // Mettre à NULL pour le suivant/precedent couleur/forme de la piece en question
    piece->precCouleur = NULL;
    piece->suivCouleur = NULL;
    piece->precForme = NULL;
    piece->suivForme = NULL;
    return piece;
}

Piece* GenererPieceAleatoire(void) {
    // Differentes formes et couleurs possibles
    char formes[] = {'C', 'L', 'R', 'T'};
    char couleurs[] = {'B', 'J', 'R', 'V'};
    // Choix aleatoire d'une forme et d'une couleur
    Piece* nouvellePiece = InitialiserPiece(formes[rand() % 4], couleurs[rand() % 4]);
    
    return nouvellePiece;
}