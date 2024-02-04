/* GESTION DU CHAINAGE */

#include "../hdr/chainage.h"
#include "../hdr/plateau.h"
#include "../hdr/piece.h"
#include "../hdr/classement.h"
#include "../hdr/affichage.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void SupprimerForme(Piece* piece){
    // Aucune forme est dans la liste chainee 'FORME'
    if (piece->suivForme == NULL){
        return;
    }
    // Une seule forme est dans la liste chainee 'FORME'
    else if (piece->suivForme == piece){
        piece->suivForme = NULL;
        piece->precForme = NULL;
    }
    // Plusieurs formes dans la liste chainee 'FORME'
    else {
        Piece* suivantForme = piece->suivForme;
        suivantForme->precForme = piece->precForme;
        piece->precForme->suivForme = suivantForme;
    }
}

void SupprimerCouleur(Piece* piece){
    // Aucune forme est dans la liste chainee 'COULEUR'
    if (piece->suivCouleur == NULL){
        return;
    }
    // Une seule forme dans la liste chainee 'COULEUR'
    else if (piece->suivCouleur == piece){
        piece->suivCouleur = NULL;
        piece->precCouleur = NULL;
    }
    // Plusieurs formes dans la liste chainee 'COULEUR'
    else {
        Piece* suivantCouleur = piece->suivCouleur;
        suivantCouleur->precCouleur = piece->precCouleur;
        piece->precCouleur->suivCouleur = suivantCouleur;
    }
}

void DisparaitrePieces(Plateau* plateau, int* score, char typeDeSuppression, char* nom, Piece* tabPieces[], int combo){
    // CAS : card < 3
    if (plateau->card<3){
        return;
    }
    // CAS : card = 3
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

            printf("\033[2J");
            printf("\033[0;0H");
            

            AfficherJeu(nom, score, tabPieces, plateau);
            // Affichage d'un combo
            if (combo>1){
                printf("           COMBO x%d\n", combo);
                usleep(1200000);
            }

            // Appel recursif pour gerer les suppressions en cascade
            DisparaitrePieces(plateau, score, typeDeSuppression, nom, tabPieces, combo+1);
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

                printf("\033[2J");
                printf("\033[0;0H");
                AfficherJeu(nom, score, tabPieces, plateau);
                if (combo>1){
                    printf("           COMBO x%d\n", combo);
                    usleep(1200000);
                }


                // Appel recursif pour gerer les suppressions en cascade
                DisparaitrePieces(plateau, score, typeDeSuppression, nom, tabPieces, combo+1);

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

                printf("\033[2J");
                printf("\033[0;0H");
                AfficherJeu(nom, score, tabPieces, plateau);
                if (combo>1){
                    printf("           COMBO x%d\n", combo);
                    usleep(1200000);
                }


                // Appel recursif pour gerer les suppressions en cascade
                DisparaitrePieces(plateau, score, typeDeSuppression, nom, tabPieces, combo+1);


                return;
            }
            tete = tete->suiv; // On passe au suivant
        }
    }    
}

void DecalageForme(Plateau* plateau, char forme){
	Piece* dernier = TrouverDernierForme(plateau, forme);
    // Aucune pièce du type [forme] sur le jeu
	if(dernier == NULL){
		return;
	}
	Piece * courant = dernier->precForme;
	while((courant) != dernier){
		char couleurtmp = dernier->couleur;
		dernier->couleur = courant->couleur;
		courant->couleur = couleurtmp;
		courant = courant->precForme;
	}
	char formes[plateau->card];
	char couleurs[plateau->card];
	
	int card = plateau->card;
	Piece* sauvegarde = plateau->premier;
	formes[0] = sauvegarde->forme;
	couleurs[0] = sauvegarde->couleur;
	sauvegarde = sauvegarde->suiv;
	

	for (int j=1;j<card;j++){
		formes[j]=sauvegarde->forme;
		couleurs[j]=sauvegarde->couleur;
		sauvegarde=sauvegarde->suiv;
	}
	
	Piece* temp = plateau->premier;
    Piece* suivant;

    // Liberation de la memoire des pieces
    do {
        suivant = temp->suiv;
        free(temp);
        temp = suivant;
    } while (temp != plateau->premier);
    plateau->card=0;

	for (int i=0; i<card; i++){
        Piece* piece = InitialiserPiece(formes[i], couleurs[i]);
        InsererDroite(plateau, piece);
    }
}	
	
void DecalageCouleur(Plateau* plateau,char couleur){
	Piece* dernier = TrouverDernierCouleur(plateau, couleur);
    // Aucune pièce du type [couleur] sur le jeu
	if(dernier == NULL){
		return;
	}
	Piece* courant=dernier->precCouleur;
	while((courant)!=dernier){
		char formetmp = dernier->forme;
		dernier->forme = courant->forme;
		courant->forme = formetmp;
		courant = courant->precCouleur;
	}
	char formes[plateau->card];
	char couleurs[plateau->card];
	
	
	int card = plateau->card;
	Piece* sauvegarde = plateau->premier;
	formes[0] = sauvegarde->forme;
	couleurs[0] = sauvegarde->couleur;
	sauvegarde = sauvegarde->suiv;
	

	for (int j=1;j<card;j++){
		formes[j] = sauvegarde->forme;
		couleurs[j] = sauvegarde->couleur;
		sauvegarde = sauvegarde->suiv;
	}
	
	Piece* temp = plateau->premier;
    Piece* suivant;

    // Liberation de la memoire des pieces
    do {
        suivant = temp->suiv;
        free(temp);
        temp = suivant;
    
    } while (temp != plateau->premier);
    plateau->card=0;

	for (int i=0; i<card; i++){
        Piece* piece = InitialiserPiece(formes[i], couleurs[i]);
        InsererDroite(plateau, piece);
    }
}	

void InsererDroite(Plateau* plateau, Piece* piece){
    // Double chaînage de la forme de la piece
    Piece* dernierForme = TrouverDernierForme(plateau, piece->forme);
    if (dernierForme == NULL){
        piece->suivForme = piece;
        piece->precForme = piece;
    } else {
        piece->suivForme = dernierForme->suivForme;
        piece->precForme = dernierForme;
        dernierForme->suivForme->precForme = piece;
        dernierForme->suivForme = piece;
    }

    // Double chaînage de la couleur de la piece
    Piece* dernierCouleur = TrouverDernierCouleur(plateau, piece->couleur);
    if (dernierCouleur == NULL){
        piece->suivCouleur = piece;
        piece->precCouleur = piece;
    } else {
        piece->suivCouleur = dernierCouleur->suivCouleur;
        piece->precCouleur = dernierCouleur;
        dernierCouleur->suivCouleur->precCouleur = piece;
        dernierCouleur->suivCouleur = piece;
    }

    // Ajout au plateau
    if (plateau->card == 0){
        plateau->premier = piece;
        piece->suiv = piece; // Le seul element pointe sur lui-même
    } else {
        Piece* fin = RechercherDernier(plateau);
        fin->suiv = piece;
        piece->suiv = plateau->premier;
    }
    plateau->card++;
}

void InsererGauche(Plateau* plateau, Piece* piece){

    // Double chaînage de la forme de la piece
    Piece* dernierForme = TrouverDernierForme(plateau, piece->forme);
    if (dernierForme == NULL){
        piece->suivForme = piece;
        piece->precForme = piece;
    } else {
        piece->suivForme = dernierForme->suivForme;
        piece->precForme = dernierForme;
        dernierForme->suivForme->precForme = piece;
        dernierForme->suivForme = piece;
    }

    // Double chaînage de la couleur de la piece
    Piece* dernierCouleur = TrouverDernierCouleur(plateau, piece->couleur);
    if (dernierCouleur == NULL){
        piece->suivCouleur = piece;
        piece->precCouleur = piece;
    } else {
        piece->suivCouleur = dernierCouleur->suivCouleur;
        piece->precCouleur = dernierCouleur;
        dernierCouleur->suivCouleur->precCouleur = piece;
        dernierCouleur->suivCouleur = piece;
    }

    // Ajout au plateau
    if (plateau->card == 0){
        plateau->premier = piece;
        piece->suiv = piece; // Le seul element pointe sur lui-même
    } else {
        piece->suiv = plateau->premier;
        Piece* fin = RechercherDernier(plateau);
        fin->suiv = piece;
        plateau->premier = piece;
    }
    plateau->card++;
}

void LibererMemoire(Plateau* plateau) {
    Piece* temp = plateau->premier;
    Piece* suivant;

    // Liberation de la memoire des pieces
    do {
        suivant = temp->suiv;
        free(temp);
        temp = suivant;
    } while (temp != plateau->premier);

    // Liberation de la memoire du plateau
    free(plateau);
}
