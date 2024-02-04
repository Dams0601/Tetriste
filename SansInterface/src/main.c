#include "../hdr/piece.h"
#include "../hdr/plateau.h"
#include "../hdr/chainage.h"
#include "../hdr/affichage.h"
#include "../hdr/classement.h"
#include "../hdr/ia.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void){
    // Initialisation du plateau, du score, du nom, et des pieces generees aleatoirement
    Plateau* plateau = InitialiserPlateau();
    int score = 0;
    Piece* piece1 = GenererPieceAleatoire();
    Piece* piece2 = GenererPieceAleatoire();
    Piece* piece3 = GenererPieceAleatoire();
    Piece* piece4 = GenererPieceAleatoire();
    Piece* piece5 = GenererPieceAleatoire();
    Piece* tabPieces[5] = {piece1, piece2, piece3, piece4, piece5};
    char nom[MAX_NOM];
    srand(time(NULL));
    char res = 0;
    char res2 = 0;

    do {
        // Choix de recuperer une partie precedente ou une nouvelle partie
        do {
            printf("\033[2J");
            printf("\033[0;0H");

            // Affiche le Logo
            Logo();
            
            // Consignes
            printf("Objectif : Vous devez creer des motifs de forme ou couleur repetes afin de marquer un maximum de points.\n\n");
            printf("Demarrer une nouvelle partie (D) - Charger la derniere partie en cours (C) - Voir le classement (V): ");
            scanf(" %c", &res);
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
            }
        } while (res != 'D' && res != 'd' && res != 'C' && res != 'c' && res != 'V' && res != 'v');
        
        // Reponse => Demarrer une nouvelle partie
        if (res == 'D' || res == 'd'){
            printf("Nom d'utilisateur (max 50 car.) : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';
            do{
                printf("Avec aide (O=oui et N=non) : ");
                scanf(" %c", &res);
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                    // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
                }
                res2 = res;
                res = 'D';
            } while (res2 != 'O' && res2 != 'o' && res2 != 'N' && res2 != 'n');

            EffetChargement("Initialisation du plateau");

            DeroulementJeu(nom, &score, plateau, &res, tabPieces, res2);
        }
        // Reponse => Charger la derniere partie
        else if (res == 'C' || res == 'c'){

            do{
                printf("Avec aide (O=oui et N=non) : ");
                scanf(" %c", &res);
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                    // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
                }
                res2 = res;
                res = 'C';
            } while (res2 != 'O' && res2 != 'o' && res2 != 'N' && res2 != 'n');

            // Ouverture du fichier 'sauvegarde.txt'
            if (access("txt/sauvegarde.txt", F_OK) == -1){
                FILE* f = fopen("txt/sauvegarde.txt", "w");
                if (f == NULL){
                    perror("Erreur lors de l'ouverture du fichier");
                    return 1;
                } 
                fclose(f);
            }
            FILE* sauvegarde = fopen("txt/sauvegarde.txt", "r");
            if (sauvegarde == NULL) {
                perror("Erreur lors de l'ouverture du fichier");
                return 1;
            }
            // Se deplacer à la fin du fichier pour obtenir la taille
            fseek(sauvegarde, 0, SEEK_END);
            char taille = ftell(sauvegarde);
            // Remettre le curseur au debut du fichier
            fseek(sauvegarde, 0, SEEK_SET);
            if (taille == 0) {
                printf("\033[2J");
                printf("\033[0;0H");
                printf("Aucune partie sauvegardee...\nUne nouvelle partie ete demarree.\n");
                
                printf("Nom d'utilisateur (max 50 car.) : ");
                fgets(nom, sizeof(nom), stdin);
                nom[strcspn(nom, "\n")] = '\0';

                EffetChargement("Initialisation du plateau");

                DeroulementJeu(nom, &score, plateau, &res, tabPieces, res2);
            }
            else{
                char ligne[100];
                // Lire chaque ligne du fichier
                char nom[MAX_NOM];
                fgets(nom, MAX_NOM, sauvegarde);
                nom[strcspn(nom, "\n")] = '\0';

                int nbrElem = atoi(fgets(ligne, 100, sauvegarde));
                score = atoi(fgets(ligne, 100, sauvegarde));
                if (nbrElem != 0){
                    char formes[100];
                    fgets(formes, 100, sauvegarde);
                
                    char couleurs[100];
                    fgets(couleurs, 100, sauvegarde);

                    for (int i=0; i<strlen(formes)-1; i++){
                        Piece* piece = InitialiserPiece(formes[i], couleurs[i]);
                        InsererDroite(plateau, piece);
                    }

                    // Effet visuel
                    EffetChargement("Chargement de la partie en cours");
                }

                // Fermer le fichier
                fclose(sauvegarde);

                // Debut du jeu reinitialiser
                DeroulementJeu(nom, &score, plateau, &res, tabPieces, res2);         
            }
        }
        else if (res == 'V' || res == 'v'){
            do {
                printf("\033[2J");
                printf("\033[0;0H");
                AfficherClassement();
                res = 0;
                printf("Pour revenir en arriere (R) : ");
                scanf(" %c", &res);
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("\033[2J");
                printf("\033[0;0H");
            } while(res != 'R' && res != 'r');
        } 
    }while (res!='S' && res!='s');
}
