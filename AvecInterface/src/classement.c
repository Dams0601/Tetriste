#include "../hdr/classement.h"
#include "../hdr/piece.h"
#include "../hdr/plateau.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int PositionJoueur(char* nom, const char classementsNom[][MAX_NOM], int nbJoueurs){
    // Parcours le liste des noms
    for (int i=0; i<nbJoueurs; i++){
        if (!strcmp(classementsNom[i],nom)){
            return i;
        }
    }
    return -1;
}

void TriInsertion(char classementsNom[][MAX_NOM], int classementsScore[], int nbJoueurs) {
    int i, cleScore, j;
    char cleNom[MAX_NOM];
    // Parcours la liste des joueurs
    for (i = 1; i < nbJoueurs; i++) {
        cleScore = classementsScore[i];
        strcpy(cleNom, classementsNom[i]);
        j = i-1;
        while (j >= 0 && classementsScore[j] < cleScore) {
            classementsScore[j+1] = classementsScore[j];
            strcpy(classementsNom[j+1], classementsNom[j]);
            j = j-1;
        }
        classementsScore[j+1] = cleScore;
        strcpy(classementsNom[j+1], cleNom);
    }
}

void EcrireClassement(char* nom, int score){
    // Récupération des données du classement 
    FILE* classement = fopen("txt/classement.txt", "r");
    char ligne[MAX_NOM];
    char classementsNom[MAX_JOUEURS][MAX_NOM];
    int classementsScore[MAX_JOUEURS];
    int nbJoueurs = 0; // Pour déterminer si la ligne est paire ou impaire

    // Vérifier si le fichier est ouvert correctement
    if (classement == NULL) {
        FILE* f = fopen("txt/classement.txt", "w");
        if (f == NULL){
            perror("Erreur lors de l'ouverture du fichier");
            return;
        } 
        fclose(f);
    }
    fclose(classement);
    classement = fopen("txt/classement.txt", "r");

    // Lire chaque ligne du fichier et stocker dans les tableaux appropriés
    while (fgets(ligne, sizeof(ligne), classement) != NULL) {
        if (nbJoueurs % 2 == 0) {
            // Ligne paire, stocker dans le tableau des lignes paires
            ligne[strcspn(ligne, "\n")] = '\0';
            strcpy(classementsNom[nbJoueurs/2], ligne);
        } else {
            // Ligne impaire, stocker dans le tableau des lignes impaires
            classementsScore[(nbJoueurs-1)/2] = atoi(ligne);
        }
        nbJoueurs++;
    }
    nbJoueurs /= 2;
    printf("Nombre de joueurs : %d\n", nbJoueurs);

    // Fermer le fichier après avoir fini de le lire
    fclose(classement);

    // Si la liste est pleine mais que le nouveau joueur a un meilleur score que le dernier on le remplace
    int joueurExistant = PositionJoueur(nom, classementsNom, nbJoueurs);
    if (nbJoueurs == MAX_JOUEURS && score>classementsScore[MAX_JOUEURS-1]){
        if (joueurExistant == -1){
            strcpy(classementsNom[MAX_JOUEURS-1], nom);
            classementsScore[MAX_JOUEURS-1] = score;
        }
        else{
            strcpy(classementsNom[joueurExistant], nom);
            classementsScore[joueurExistant] = score;
        }

        TriInsertion(classementsNom, classementsScore, nbJoueurs);
    }
    else if(nbJoueurs<MAX_JOUEURS){
        if (joueurExistant == -1){
            strcpy(classementsNom[nbJoueurs], nom);
            classementsScore[nbJoueurs] = score;
            nbJoueurs++;
        }
        else{
            strcpy(classementsNom[joueurExistant], nom);
            classementsScore[joueurExistant] = score;
        }
        TriInsertion(classementsNom, classementsScore, nbJoueurs);
    }

    // Ecriture dans le fichier
    classement = fopen("txt/classement.txt", "w");
    for (int i=0; i<nbJoueurs; i++){
        fprintf(classement, "%s\n", classementsNom[i]);
        fprintf(classement, "%d\n", classementsScore[i]);
    }
    fclose(classement);
}

void AfficherClassement(void){
    char ligne[MAX_NOM];
    char classementsNom[MAX_JOUEURS][MAX_NOM];
    int classementsScore[MAX_JOUEURS];
    int nbJoueurs = 0; // Pour déterminer si la ligne est paire ou impaire

    // Vérifier si le fichier est ouvert correctement
    if (access("txt/classement.txt", F_OK) == -1){
        FILE* f = fopen("txt/classement.txt", "w");
        if (f == NULL){
            perror("Erreur lors de l'ouverture du fichier");
            return;
        }
        fclose(f);
    }
    FILE* classement = fopen("txt/classement.txt", "r");
    if (classement == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    // Lire chaque ligne du fichier et stocker dans les tableaux appropriés
    while (fgets(ligne, sizeof(ligne), classement) != NULL) {
        if (nbJoueurs % 2 == 0) {
            // Ligne paire, stocker dans le tableau des lignes paires
            ligne[strcspn(ligne, "\n")] = '\0';
            strcpy(classementsNom[nbJoueurs/2], ligne);
        } else {
            // Ligne impaire, stocker dans le tableau des lignes impaires
            classementsScore[(nbJoueurs-1)/2] = atoi(ligne);
        }
        nbJoueurs++;
    }
    nbJoueurs /= 2;

    // Fermer le fichier après avoir fini de le lire
    fclose(classement);

    if (nbJoueurs == 0){
        printf("On attend ton score dans le classement...\nC'est un petit peu vide sans toi...\n");
    }
    else{
        printf("----------------------------- CLASSEMENT ----------------------------\n");
        printf("[%5s] %50s |  SCORE |\n", "RANG", "NOM");
        printf("---------------------------------------------------------------------\n");
        for (int i=0; i<nbJoueurs; i++){
            if (i==0){
                printf("[\033[48;5;226m%5d\033[0m] %50s | %6d |\n", i+1, classementsNom[i], classementsScore[i]);
            }
            else if (i==1){
                printf("[\033[48;5;8m%5d\033[0m] %50s | %6d |\n", i+1, classementsNom[i], classementsScore[i]);
            }
            else if (i==2){
                printf("[\033[48;5;130m%5d\033[0m] %50s | %6d |\n", i+1, classementsNom[i], classementsScore[i]);
            }
            else{
                printf("[%5d] %50s | %6d |\n", i+1, classementsNom[i], classementsScore[i]);
            }
        }
    } 
}

void AjouterPoint(int* score, char typeDeSuppression, int combo){
    if (typeDeSuppression=='G' || typeDeSuppression=='g' || typeDeSuppression=='D' || typeDeSuppression=='d'){
        *score=*score+combo*POINT_AJOUT;
    }
    else { // typeDeSuppression=='L' || typeDeSuppression=='l'
        *score=*score+combo*POINT_DECALAGE;
    }
}
