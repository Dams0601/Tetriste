/* GESTION DE L'AFFICHAGE */

#include "../hdr/affichage.h"
#include "../hdr/piece.h"
#include "../hdr/plateau.h"
#include "../hdr/ia.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void AfficherCouleur(Piece* piece){
    // Si aucune pièce n'est présente sur le plateau
    if (piece==NULL){
        return;
    }
    // Convertir lettre en caractere unicode en passant par une varaible intermediaire
    char* formeUni;
    if (piece->forme == 'T'){
        formeUni = "\u25B2";
    }
    else if (piece->forme == 'C'){
        formeUni = "\u25A0";
    }
    else if (piece->forme == 'R'){
        formeUni = "\u25CF";
    }
    else if (piece->forme == 'L'){
        formeUni = "\u2BC1";
    }
    // Affichage selon la couleur
    if (piece->couleur == 'B'){
        printf("\033[34m%s\033[0m ", formeUni);
    }
    else if (piece->couleur == 'V'){
        printf("\033[32m%s\033[0m ", formeUni);
    }
    else if (piece->couleur == 'J'){
        printf("\033[93m%s\033[0m ", formeUni);
    }
    else if (piece->couleur == 'R'){
        printf("\033[31m%s\033[0m ", formeUni);
    }
}

void AfficherPlateau(Plateau* plateau) {
    printf("\n----------- PLATEAU ----------\n");
    Piece* temp = plateau->premier;
    if (plateau->card == 0){
        printf("\n------------------------------\n\n");
        return;
    }
    else if (plateau->card == 1){
        AfficherCouleur(temp);
        printf("\n------------------------------\n\n");
        return;
    }
    AfficherCouleur(temp);
    temp = temp->suiv;
    while (temp != plateau->premier) {
        AfficherCouleur(temp);
        temp = temp->suiv;
    }
    printf("\n------------------------------\n\n");
}

void AfficherJeu(char nom[], int* score, Piece* tabPieces[], Plateau* plateau){
    printf("| Nom : %s |\n", nom);
    printf("| SCORE : %5d |\n", *score);
    printf("\n       PROCHAINS : ");
    for (int i=0; i<5; i++){
        AfficherCouleur(tabPieces[i]);
    }
    printf("\n");

    AfficherPlateau(plateau);
}

void EffetChargement(char* texte){
    // Affiche circulairement [texte]. -> [texte].. -> [texte]...
    for (int i=0; i<4; i++){
        printf("\033[2J");
        printf("\033[0;0H");
        printf("%s.\n", texte);
        usleep(300000);
        printf("\033[2J");
        printf("\033[0;0H");
        printf("%s..\n", texte);
        usleep(300000);
        printf("\033[2J");
        printf("\033[0;0H");
        printf("%s...\n", texte);
        usleep(300000);
        printf("\033[2J");
        printf("\033[0;0H");
    }
}

char ChoixUtilisateur(char nom[], int* score, Piece* tabPieces[], Plateau* plateau, char res2){
    char res = 0;
    
    if (plateau->tailleMax == plateau->card){
        do {
            // Remmetre à 0 le terminal
            printf("\033[2J");
            printf("\033[0;0H");
            
            if (res2 == 'O' || res2 == 'o'){
                int tabScore[10] = {0};
                int tabCoups[10] = {0};
                int indMax = IntelligenceArtificielle(plateau, tabPieces, score, nom, tabCoups, tabScore);
                AfficherConseil(indMax, tabScore, tabCoups);
            }
            AfficherJeu(nom, score, tabPieces, plateau);


            printf("Decalage (L) - Stop (S) : ");
            scanf(" %c", &res);
            // Nettoyer le tampon d'entree apres la saisie du caractere pour eviter les entrees supplementaires non desirees
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
            }
        } while (res != 'S' && res != 's' && res != 'L' && res != 'l');
    }
    else {
        do {
            // Remettre à 0 le terminal
            printf("\033[2J");
            printf("\033[0;0H");

            

            if (plateau->card>=2 && (res2 == 'O' || res2 == 'o')){
                int tabScore[10] = {0};
                int tabCoups[10] = {0};
                int indMax = IntelligenceArtificielle(plateau, tabPieces, score, nom, tabCoups, tabScore);
                AfficherConseil(indMax, tabScore, tabCoups);
            }
            else if (plateau->card>=0 && (res2 == 'O' || res2 == 'o')){
                printf("Pas de coup 'strategique'...\n");
            }
            AfficherJeu(nom, score, tabPieces, plateau);
                    
            // Differents choix proposes
            printf("Droite (D) - Gauche (G) - Decalage (L) - Stop (S) : ");
            scanf(" %c", &res);
            // Nettoyer le tampon d'entree apres la saisie du caractere pour eviter les entrees supplementaires non desirees
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
            }
        } while (res != 'D' && res != 'd' && res != 'G' && res != 'g' && res != 'S' && res != 's' && res != 'L' && res != 'l');
    }
    return res;
}

void Logo(void){
    printf("      ====================================================================\n");
    printf("        ________ _______ ________ ________  __  _______ ________ _______\n");
    printf("       |\033[48;5;24m__    __\033[0m|\033[48;5;226m   ____\033[0m|\033[48;5;40m__    __\033[0m|\033[48;5;196m   __   \033[0m||\033[48;5;24m__\033[0m||\033[48;5;226m  _____\033[0m|\033[48;5;40m__    __\033[0m|\033[48;5;196m   ____\033[0m|\n");
    printf("          |\033[48;5;24m  \033[0m|  |\033[48;5;226m  \033[0m|__     |\033[48;5;40m  \033[0m|  |\033[48;5;196m  \033[0m|__|\033[48;5;196m  \033[0m| __ |\033[48;5;226m  \033[0m|____   |\033[48;5;40m  \033[0m|  |\033[48;5;196m  \033[0m|__\n");
    printf("          |\033[48;5;24m  \033[0m|  |\033[48;5;226m   __\033[0m|    |\033[48;5;40m  \033[0m|  |\033[48;5;196m     ___\033[0m||\033[48;5;24m  \033[0m||\033[48;5;226m____   \033[0m|  |\033[48;5;40m  \033[0m|  |\033[48;5;196m   __\033[0m|\n");
    printf("          |\033[48;5;24m  \033[0m|  |\033[48;5;226m  \033[0m|____   |\033[48;5;40m  \033[0m|  |\033[48;5;196m   __  \033[0m| |\033[48;5;24m  \033[0m| ____|\033[48;5;226m  \033[0m|  |\033[48;5;40m  \033[0m|  |\033[48;5;196m  \033[0m|____\n");
    printf("          |\033[48;5;24m__\033[0m|  |\033[48;5;226m_______\033[0m|  |\033[48;5;40m__\033[0m|  |\033[48;5;196m__\033[0m| |\033[48;5;196m___\033[0m||\033[48;5;24m__\033[0m||\033[48;5;226m_______\033[0m|  |\033[48;5;40m__\033[0m|  |\033[48;5;196m_______\033[0m|\n");
    printf("\033[0m");
    printf("\n      ====================================================================\n\n");
}

int DeroulementJeu(char nom[], int* score, Plateau* plateau, char* res, Piece* tabPieces[], char res2){
    while(*res!='s' || *res!='S'){
            // Recuperation de la premiere piece et generation d'une piece
            Piece* pieceActuel = tabPieces[0];
            
            // Choix de l'utilisateur
            *res = ChoixUtilisateur(nom, score, tabPieces, plateau, res2);

            // On "sort" le premier element pour pouvoir le placer sur le plateau de jeu
            if (*res != 'L' && *res != 'l'){
                Piece* pieceDerniereTab = GenererPieceAleatoire();
                tabPieces[0] = tabPieces[1];
                tabPieces[1] = tabPieces[2];
                tabPieces[2] = tabPieces[3];
                tabPieces[3] = tabPieces[4];
                tabPieces[4] = pieceDerniereTab;
            }

            // Differents cas
            if(*res == 'G' || *res == 'g'){
                InsererGauche(plateau, pieceActuel);
                DisparaitrePieces(plateau, score, 'G', nom, tabPieces, 1); // Supprime les triplets
            }
            else if (*res == 'D' || *res == 'd'){
                InsererDroite(plateau, pieceActuel);
                DisparaitrePieces(plateau, score, 'D', nom, tabPieces, 1); // Supprime les triplets
            }
            else if (*res == 'L' || *res == 'l'){
                do{
                    printf("Forme (F) - Couleur (C) : ");
                    scanf("%c", res);
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {
                    // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
                    }
                    if (*res == 'F' || *res == 'f'){
                        do {
                            printf("Carre (C) - Losange (L) - Rond (R) - Triangle (T) :  ");
                            scanf("%c", res);
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF) {
                                // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
                            }
                            if (*res == 'C'|| *res == 'c'){
                                DecalageForme(plateau,'C');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                break;
                            }
                            
                            else if (*res == 'L'|| *res == 'l'){
                                DecalageForme(plateau,'L');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);  
                                break;
                            }
                            else if (*res == 'R'|| *res == 'r'){
                                DecalageForme(plateau,'R');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                break;
                            }
                            else if (*res == 'T'|| *res == 't'){
                                DecalageForme(plateau,'T');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                break;
                            }
                        }while(*res != 'C' && *res != 'c' && *res != 'L' && *res != 'l' && *res != 'R' && *res != 'r' && *res != 'T' && *res != 't');
                        break;
                    }
                    else if (*res == 'C'|| *res == 'c'){
                        do{
                            printf("Rouge (R) - Jaune (J) - Bleu (B) - Vert (V) : ");
                            scanf("%c", res);
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF) {
                            // Lire et jeter les caracteres jusqu'à la fin de la ligne ou la fin du fichier
                            }
                            if (*res=='R' || *res == 'r'){
                                DecalageCouleur(plateau,'R');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                break;
                            }
                            else if (*res=='J'|| *res == 'j'){
                                DecalageCouleur(plateau,'J');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                break;
                            }
                            else if (*res=='B'|| *res == 'b'){
                                DecalageCouleur(plateau,'B');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                break;
                            }
                            else if (*res=='V'|| *res == 'v'){
                                DecalageCouleur(plateau,'V');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                break;
                            }
                        }while(*res != 'R' && *res != 'r' && *res != 'J' && *res != 'j' && *res != 'B' && *res != 'b' && *res != 'V' && *res != 'v');
                        break;
                    }
                } while (*res!='F' && *res!='f' && *res!='C' && *res!='c');
                *res = 'L';
            }
            else if (*res == 'S' || *res == 's'){
                // Met a jour le classement
                EcrireClassement(nom, *score);

                // Effectue la sauvegarde de la partie
                FILE* sauvegarde = fopen("txt/sauvegarde.txt", "w");
                fprintf(sauvegarde, "%s\n", nom);
                fprintf(sauvegarde, "%d\n", plateau->card);
                fprintf(sauvegarde, "%d\n", *score);

                // Libere l'allocation faite pour la piece qui a ete change de la liste tabPieces
                free(pieceActuel);

                if (plateau->card == 0){
                    fprintf(sauvegarde, "\n");
                    fprintf(sauvegarde, "\n");
                    free(plateau);
                    // Effet visuel
                    EffetChargement("Partie en cours de sauvegarde");
                    printf("Sauvegarde effectuee\n");
                    return -1;
                }
                // Gerer la plateau (cote FORME)
                Piece* piece = plateau->premier;
                fprintf(sauvegarde, "%c", piece->forme);
                piece = piece->suiv;
                while (piece != plateau->premier){
                    fprintf(sauvegarde, "%c", piece->forme);
                    piece = piece->suiv;
                }
                fprintf(sauvegarde, "\n");

                // Gerer la plateau (cote COULEUR)
                piece = plateau->premier;
                fprintf(sauvegarde, "%c", piece->couleur);
                piece = piece->suiv;
                while (piece != plateau->premier){
                    fprintf(sauvegarde, "%c", piece->couleur);
                    piece = piece->suiv;
                }
                fclose(sauvegarde);

                // Cote memoire
                // Plateau
                LibererMemoire(plateau);
                // Pieces generees
                int i=0;
                Piece* temp = tabPieces[i];
                Piece* suivant;

                // Liberation de la memoire des pieces
                do {
                    i++;
                    suivant = tabPieces[i];
                    free(temp);
                    temp = suivant;
                } while (i<5);

            // Effet visuel et affichage
            EffetChargement("Merci d'avoir joue.\nPartie en cours de sauvegarde");
            printf("Sauvegarde effectuee\n");
            return -1;
        } 
    }
    return 0;
}
