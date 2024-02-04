/* GESTION DE L'IA */

#include "../hdr/affichage.h"
#include "../hdr/piece.h"
#include "../hdr/plateau.h"
#include "../hdr/ia.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void DisparaitrePiecesBis(Plateau* plateau, int* score, char typeDeSuppression, char* nom, Piece* tabPieces[], int combo){
    // Cas : card < 3
    if (plateau->card<3){
        return;
    }
    // Cas : card = 3
    else if (plateau->card==3){
        // Si on a les 3 formes identiques
        if (((plateau->premier->forme == plateau->premier->suiv->forme) && (plateau->premier->forme ==  plateau->premier->suiv->suiv->forme))||((plateau->premier->couleur == plateau->premier->suiv->couleur) && (plateau->premier->couleur ==  plateau->premier->suiv->suiv->couleur))){
            // Ajouter les points
            AjouterPoint(score, typeDeSuppression, combo);

            // Enlever des listes doublement chainees forme et couleur (mais tjrs presente sur le plateau)
            Piece* dernier = RechercherDernier(plateau);
            Piece* tmp = NULL;

            SupprimerForme(plateau->premier);
            SupprimerCouleur(plateau->premier);
            tmp = plateau->premier;
            dernier->suiv = plateau->premier->suiv;
            plateau->premier = plateau->premier->suiv;
            plateau->card--;
            free(tmp);

            SupprimerForme(plateau->premier);
            SupprimerCouleur(plateau->premier);
            tmp = plateau->premier;
            dernier->suiv = plateau->premier->suiv;
            plateau->premier = plateau->premier->suiv;
            plateau->card--;
            free(tmp);

            SupprimerForme(plateau->premier);
            SupprimerCouleur(plateau->premier);
            tmp = plateau->premier;
            plateau->premier = NULL;
            plateau->card--;
            free(tmp);
            

            DisparaitrePiecesBis(plateau, score, typeDeSuppression, nom, tabPieces, combo+1);
        }
    }
    else {
        // Teste la tete
        Piece* tete = plateau->premier;
        if ((tete->forme == tete->suiv->forme && tete->forme == tete->suiv->suiv->forme) || (tete->couleur == tete->suiv->couleur && tete->couleur == tete->suiv->suiv->couleur)){
            if(tete == plateau->premier){
                Piece* tmp = NULL;
                Piece* dernier = RechercherDernier(plateau);
                SupprimerForme(plateau->premier);
                SupprimerCouleur(plateau->premier);
                tmp = plateau->premier;
                plateau->premier = plateau->premier->suiv;
                dernier->suiv = plateau->premier;
                plateau->card--;
                free(tmp);

                SupprimerForme(plateau->premier);
                SupprimerCouleur(plateau->premier);
                tmp = plateau->premier;
                plateau->premier = plateau->premier->suiv;
                dernier->suiv = plateau->premier;
                plateau->card--;
                free(tmp);

                SupprimerForme(plateau->premier);
                SupprimerCouleur(plateau->premier);
                tmp = plateau->premier;
                plateau->premier = plateau->premier->suiv;
                dernier->suiv = plateau->premier;
                plateau->card--;
                free(tmp);

                

                // Ajouter les points
                AjouterPoint(score, typeDeSuppression, combo);

                // Rappeler recurssivement
                DisparaitrePiecesBis(plateau, score, typeDeSuppression, nom, tabPieces, combo+1);

                return;
            } 
        }
        while(tete->suiv->suiv->suiv != plateau->premier){
            if ((tete->suiv->forme == tete->suiv->suiv->forme && tete->suiv->forme == tete->suiv->suiv->suiv->forme)||(tete->suiv->couleur == tete->suiv->suiv->couleur && tete->suiv->couleur == tete->suiv->suiv->suiv->couleur)){
                Piece* tmp = NULL;
                SupprimerForme(tete->suiv);
                SupprimerCouleur(tete->suiv);
                tmp = tete->suiv;
                tete->suiv = tete->suiv->suiv;
                plateau->card--;
                free(tmp);

                SupprimerForme(tete->suiv); 
                SupprimerCouleur(tete->suiv);
                tmp = tete->suiv;
                tete->suiv = tete->suiv->suiv;
                plateau->card--;
                free(tmp);

                SupprimerForme(tete->suiv);
                SupprimerCouleur(tete->suiv);
                tmp = tete->suiv;
                tete->suiv = tete->suiv->suiv;
                plateau->card--;
                free(tmp);

                

                // Ajouter les points
                AjouterPoint(score, typeDeSuppression, combo);

                // Appeler recursivement
                DisparaitrePiecesBis(plateau, score, typeDeSuppression, nom, tabPieces, combo+1);


                return;
            }
            tete = tete->suiv; // On passe au suivant
        }
    }    
}

void LibererMemoire2(Plateau* plateau) {
    Piece* temp = plateau->premier;
    Piece* suivant;

    if (plateau->card==0){
        free(plateau);
        return;
    }

    if (plateau->card==1){
        free(temp);
        free(plateau);
        return;
    }

    temp = temp->suiv;
    // Libération de la mémoire des pièces
    do {
        suivant = temp->suiv;
        free(temp);
        temp = suivant;
    } while (temp != plateau->premier);

    free(plateau->premier);

    // Libération de la mémoire du plateau
    free(plateau);
}

void CreerCopiePlateau(const Plateau* plateau, Plateau* nouveauPlateau){
    // s'occupe du chainage simpla
    if (plateau->card == 0){
        return;
    }
    else if (plateau->card == 1){
        Piece* tmp = plateau->premier;
        InsererDroite(nouveauPlateau, tmp);
        return;
    }

    char formes[plateau->card];
	char couleurs[plateau->card];

    Piece* sauvegarde = plateau->premier;

	for (int j=0;j<plateau->card;j++){
		formes[j]=sauvegarde->forme;
		couleurs[j]=sauvegarde->couleur;
		sauvegarde=sauvegarde->suiv;
	}
	
    // s'occuppe du double chainage
    for (int i=0; i<plateau->card; i++){
        Piece* piece = InitialiserPiece(formes[i], couleurs[i]);
        InsererDroite(nouveauPlateau, piece);
    }
}

int RechercherMax(int tabScore[], int tabCoups[]){
    int max = tabScore[0];
    int ind = 0;

    for (int i=1; i<10; i++){
        if (max<tabScore[i] || (max==tabScore[i] && tabCoups[i]<tabCoups[ind])){
            max = tabScore[i];
            ind = i;
        }
    }
    return ind;
}

void AfficherConseil(int indMax, int tabScore[], int tabCoups[]){
    if (indMax == -1){
        printf("Pas de coup 'strategique'...\n");
        return;
    }
    printf("Conseil d'amis : tu devrais jouer %d fois le coup ", tabCoups[indMax]);
    if (indMax == 0){
        printf("DECALAGE CARRE");
    }
    else if (indMax == 1){
        printf("DECALAGE LOSANGE");
    }
    else if (indMax == 2){
        printf("DECALAGE TRIANGLE");
    }
    else if (indMax == 3){
        printf("DECALAGE ROND");
    }
    else if (indMax == 4){
        printf("DECALAGE ROUGE");
    }
    else if (indMax == 5){
        printf("DECALAGE VERT");
    }
    else if (indMax == 6){
        printf("DECALAGE BLEU");
    }
    else if (indMax == 7){
        printf("DECALAGE JAUNE");
    }
    else if (indMax == 8){
        printf("INSERER A GAUCHE");
    }
    else if (indMax == 9){
        printf("INSERER A DROITE");
    }
    printf(" pour gagner %d points\n", tabScore[indMax]);
}

int IntelligenceArtificielle(const Plateau* plateau, Piece* tabPieces[], int* score, char* nom, int tabCoups[], int tabScore[]){
    // Tester toutes les combinaisons et renvoie celle qui rapporte le plus de points
    
    // Decalage : FORME 
    // Carre
    int nouveauScore = *score;
    Plateau* nouveauPlateau = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau);
    int i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[0]++;
        i+=1;
        DecalageForme(nouveauPlateau, 'C');
        DisparaitrePiecesBis(nouveauPlateau, &nouveauScore, 'L', nom, tabPieces, 1);
    }
    tabScore[0] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau);

    // Losange
    nouveauScore = *score;
    Plateau* nouveauPlateau2 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau2);
    i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[1]++;
        i+=1;
        DecalageForme(nouveauPlateau2, 'L');
        DisparaitrePiecesBis(nouveauPlateau2, &nouveauScore, 'L', nom, tabPieces, 1);

    }
    tabScore[1] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau2);

    // Triangle
    nouveauScore = *score;
    Plateau* nouveauPlateau3 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau3);
    i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[2]++;
        i+=1;
        DecalageForme(nouveauPlateau3, 'T');
        DisparaitrePiecesBis(nouveauPlateau3, &nouveauScore, 'L', nom, tabPieces, 1);

    }
    tabScore[2] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau3);

    // Rond
    nouveauScore = *score;
    Plateau* nouveauPlateau4 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau4);
    i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[3]++;
        i+=1;
        DecalageForme(nouveauPlateau4, 'R');
        DisparaitrePiecesBis(nouveauPlateau4, &nouveauScore, 'L', nom, tabPieces, 1);

    }
    tabScore[3] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau4);

    // COULEUR
    // Rouge
    nouveauScore = *score;
    Plateau* nouveauPlateau5 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau5);
    i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[4]++;
        i+=1;
        DecalageCouleur(nouveauPlateau5, 'R');
        DisparaitrePiecesBis(nouveauPlateau5, &nouveauScore, 'L', nom, tabPieces, 1);

    }
    tabScore[4] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau5);

    // Vert
    nouveauScore = *score;
    Plateau* nouveauPlateau6 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau6);
    i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[5]++;
        i+=1;
        DecalageCouleur(nouveauPlateau6, 'V');
        DisparaitrePiecesBis(nouveauPlateau6, &nouveauScore, 'L', nom, tabPieces, 1);

    }
    tabScore[5] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau6);

    // Bleu
    nouveauScore = *score;
    Plateau* nouveauPlateau7 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau7);
    i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[6]++;
        i+=1;
        DecalageCouleur(nouveauPlateau7, 'B');
        DisparaitrePiecesBis(nouveauPlateau7, &nouveauScore, 'L', nom, tabPieces, 1);
    }
    tabScore[6] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau7);

    // Jaune
    nouveauScore = *score;
    Plateau* nouveauPlateau8 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau8);
    i = 0;
    while (i<15 && nouveauScore == *score){
        tabCoups[7]++;
        i+=1;
        DecalageCouleur(nouveauPlateau8, 'J');
        DisparaitrePiecesBis(nouveauPlateau8, &nouveauScore, 'L', nom, tabPieces, 1);
    }
    tabScore[7] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau8);

    // Inserer a gauche
    nouveauScore = *score;
    Plateau* nouveauPlateau9 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau9);
    Piece* tmp = InitialiserPiece(tabPieces[0]->forme, tabPieces[0]->couleur);
    InsererGauche(nouveauPlateau9, tmp);
    DisparaitrePiecesBis(nouveauPlateau9, &nouveauScore, 'G', nom, tabPieces, 1);
    tabCoups[8]++;
    tabScore[8] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau9);

    // Inserer a droite
    nouveauScore = *score;
    Plateau* nouveauPlateau10 = InitialiserPlateau();
    CreerCopiePlateau(plateau, nouveauPlateau10);
    Piece* tmp2 = InitialiserPiece(tabPieces[0]->forme, tabPieces[0]->couleur);
    InsererDroite(nouveauPlateau10, tmp2);
    DisparaitrePiecesBis(nouveauPlateau10, &nouveauScore, 'D', nom, tabPieces, 1);
    tabCoups[9]++;
    tabScore[9] = nouveauScore-*score;
    LibererMemoire2(nouveauPlateau10);


    int indMax = RechercherMax(tabScore, tabCoups);
    if (tabCoups[indMax]==15 || (indMax==8 && plateau->card == 15) || (indMax==9 && plateau->card == 15) || (indMax==8 && tabScore[indMax]==0) || (indMax==9 && tabScore[indMax]==0)){
        return -1;
    }
    return indMax;
}
