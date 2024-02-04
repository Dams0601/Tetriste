#include "../hdr/piece.h"
#include "../hdr/plateau.h"
#include "../hdr/chainage.h"
#include "../hdr/affichage.h"
#include "../hdr/classement.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <MLV/MLV_all.h>

#define LARGEUR_FENETRE 1290.0
#define HAUTEUR_FENETRE 740.0
#define TAILLE_PIECE 50.0
#define CENTRE_PIECE_SUR_PLATEAU HAUTEUR_FENETRE -200
#define ECART_CERCLE TAILLE_PIECE / 2.0 + 5.0


//fonctions qui servent a dessiner les pieces du jeu
void dessine_cercle(int x, MLV_Color color) {
    MLV_draw_filled_circle(x, CENTRE_PIECE_SUR_PLATEAU, TAILLE_PIECE / 2, color);
}

void dessine_carre(int x, MLV_Color color) {
    MLV_draw_filled_rectangle(x, CENTRE_PIECE_SUR_PLATEAU - TAILLE_PIECE / 2, TAILLE_PIECE, TAILLE_PIECE, color);
}

void dessine_triangle(int x, MLV_Color color) {
    int x_points[3] = {x, x + TAILLE_PIECE / 2, x + TAILLE_PIECE};
    int y_points[3] = {CENTRE_PIECE_SUR_PLATEAU + TAILLE_PIECE / 2, CENTRE_PIECE_SUR_PLATEAU - TAILLE_PIECE / 2, CENTRE_PIECE_SUR_PLATEAU + TAILLE_PIECE / 2};
    MLV_draw_filled_polygon(x_points, y_points, 3, color);
}

void dessine_losange(int x, MLV_Color color) {
    int x_points[4] = {x, x + TAILLE_PIECE / 2, x + TAILLE_PIECE, x + TAILLE_PIECE / 2};
    int y_points[4] = {CENTRE_PIECE_SUR_PLATEAU, (CENTRE_PIECE_SUR_PLATEAU - TAILLE_PIECE / 2), CENTRE_PIECE_SUR_PLATEAU, CENTRE_PIECE_SUR_PLATEAU + TAILLE_PIECE / 2};
    MLV_draw_filled_polygon(x_points, y_points, 4, color);
}


//Pour dessiner la liste des pieces suivantes
void dessine_cercle_coin(int x, MLV_Color color) {
    MLV_draw_filled_circle(x, CENTRE_PIECE_SUR_PLATEAU-300, TAILLE_PIECE / 2, color);
}

void dessine_carre_coin(int x, MLV_Color color) {
    MLV_draw_filled_rectangle(x, CENTRE_PIECE_SUR_PLATEAU-300 - TAILLE_PIECE / 2, TAILLE_PIECE, TAILLE_PIECE, color);
}

void dessine_triangle_coin(int x, MLV_Color color) {
    int x_points[3] = {x, x + TAILLE_PIECE / 2, x + TAILLE_PIECE};
    int y_points[3] = {CENTRE_PIECE_SUR_PLATEAU-300 + TAILLE_PIECE / 2, CENTRE_PIECE_SUR_PLATEAU-300 - TAILLE_PIECE / 2, CENTRE_PIECE_SUR_PLATEAU-300 + TAILLE_PIECE / 2};
    MLV_draw_filled_polygon(x_points, y_points, 3, color);
}

void dessine_losange_coin(int x, MLV_Color color) {
    int x_points[4] = {x, x + TAILLE_PIECE / 2, x + TAILLE_PIECE, x + TAILLE_PIECE / 2};
    int y_points[4] = {CENTRE_PIECE_SUR_PLATEAU-300, (CENTRE_PIECE_SUR_PLATEAU-300 - TAILLE_PIECE / 2), CENTRE_PIECE_SUR_PLATEAU-300, CENTRE_PIECE_SUR_PLATEAU-300 + TAILLE_PIECE / 2};
    MLV_draw_filled_polygon(x_points, y_points, 4, color);
}


void gameOver(void){

	MLV_Image* image;
    int image_width, image_height;
    
    //on charge l'ecran de game over
    image = MLV_load_image( "gameover.png" );
    
       
    // On redimensionne les images de sorte à ce que la taille soit la
    //plus grande comprise dans le cadre widthxheight
      
    MLV_resize_image_with_proportions( image, LARGEUR_FENETRE, HAUTEUR_FENETRE);
        
    // On récupère la nouvelle taille de l'image afin de l'utiliser pour
    // redimensionner la fenêtre.
    //
   	MLV_get_image_size( image, &image_width, &image_height );
    
   	// On redimensionne la fenêtre
        
    MLV_change_window_size( image_width, image_height );
       
    // On affiche l'image
    
	MLV_draw_image( image, 0, 0 );
    MLV_actualise_window();
}


//fonctionne de la meme maniere que la fonction gameover

void sauvegarde(void){

MLV_Image* image;
    int image_width, image_height;
    
     	image = MLV_load_image( "sauvegarde.png" );
        //
        // On redimensionne les images de sorte à ce que la taille soit la
        // plus grande comprise dans le cadre widthxheight
        //
        MLV_resize_image_with_proportions( image, LARGEUR_FENETRE, HAUTEUR_FENETRE);
        //
        // On récupère la nouvelle taille de l'image afin de l'utiliser pour
        // redimensionner la fenêtre.
        //
    	MLV_get_image_size( image, &image_width, &image_height );
        //
        // On redimensionne la fenêtre
        //
        MLV_change_window_size( image_width, image_height );
        //
        // On affiche l'image
    

		MLV_draw_image( image, 0, 0 );
    	MLV_actualise_window();
}

//fonction pour dessiner les pieces sur le plateau a partir d'un tableau de formes et de couleurs
void dessine_pieces_plateau(char formes[], char couleurs[], int taille) {
    //MLV_clear_window(MLV_COLOR_BLACK);
    MLV_Image* image;
    int image_width, image_height;
    
     image = MLV_load_image( "fond.png" );
        //
        // On redimensionne les images de sorte à ce que la taille soit la
        // plus grande comprise dans le cadre widthxheight
        //
        MLV_resize_image_with_proportions( image, LARGEUR_FENETRE, HAUTEUR_FENETRE);
        //
        // On récupère la nouvelle taille de l'image afin de l'utiliser pour
        // redimensionner la fenêtre.
        //
    	MLV_get_image_size( image, &image_width, &image_height );
        //
        // On redimensionne la fenêtre
        //
        MLV_change_window_size( image_width, image_height );
        //
        // On affiche l'image
    

	MLV_draw_image( image, 0, 0 );
    MLV_actualise_window();




    int x = 10;

    for (int i = 0; i < taille; i++) {
        MLV_Color couleurPiece;

        switch (couleurs[i]) {
            case 'R':
                couleurPiece = MLV_COLOR_RED;
                break;
            case 'B':
                couleurPiece = MLV_COLOR_BLUE;
                break;
            case 'J':
                couleurPiece = MLV_COLOR_YELLOW;
                break;
            case 'V':
                couleurPiece = MLV_COLOR_GREEN;
                break;
            default:
                couleurPiece = MLV_COLOR_BLACK; // Couleur par défaut pour les cas non traités
                break;
        }

        switch (formes[i]) {
            case 'R':
                dessine_cercle(x + ECART_CERCLE, couleurPiece);
                break;
            case 'C':
                dessine_carre(x, couleurPiece);
                break;
            case 'T':
                dessine_triangle(x, couleurPiece);
                break;
            case 'L':
                dessine_losange(x, couleurPiece);
                break;
            default:
                // Si forme inconnue
                break;
        }

        x += TAILLE_PIECE + 10; // Espace entre les formes sur le plateau
    }
    
    
    MLV_actualise_window();
}


//fonction pour afficher les 5 pieces suivantes
//fonctionne de la meme maniere que la fonciton précédente
void dessine_liste_coin(char shapes[], char colors[], int size) {

    int x = 600;

    for (int i = 0; i < size; i++) {
        MLV_Color color;

        switch (colors[i]) {
            case 'R':
                color = MLV_COLOR_RED;
                break;
            case 'B':
                color = MLV_COLOR_BLUE;
                break;
            case 'J':
                color = MLV_COLOR_YELLOW;
                break;
            case 'V':
                color = MLV_COLOR_GREEN;
                break;
            default:
                color = MLV_COLOR_BLACK; // Couleur par défaut pour les cas non traités
                break;
        }

        switch (shapes[i]) {
            case 'R':
                dessine_cercle_coin(x + ECART_CERCLE, color);
                break;
            case 'C':
                dessine_carre_coin(x, color);
                break;
            case 'T':
                dessine_triangle_coin(x, color);
                break;
            case 'L':
                dessine_losange_coin(x, color);
                break;
            default:
                // Forme inconnue, ne rien faire ou gérer le cas selon vos besoins.
                break;
        }

        x += TAILLE_PIECE + 10; // Espace entre les formes
    }
    
    
    MLV_actualise_window();
}



// Fonction affichant les côtes d'une boîte de texte. Les paramètres sont 
// la position du sommet Nord-Ouest ( paramètres x et y ) et la taille de la 
// boîte de texte ( paramètres width et height ).
//

void BoiteDeTexte(const char* text){


        // Taille de la future boite qui affichera le texte.
        int width_text, height_text; 
        //
        // Récupère la taile de la boite de texte qui affichera le texte
        // contenu dans la variable text.
        //
        MLV_get_size_of_text( text, &width_text, &height_text );
        int positionX = (width_text-310), positionY = 15;
        //
        // Affichage du texte
        //
        MLV_draw_text( positionX, positionY, text, MLV_COLOR_WHITE );
        
	MLV_actualise_window();

}

//affiche le score du joueur en haut de la fenetre
void AfficherScore(const int* score){

		char MonScore[30];
		sprintf(MonScore, "SCORE : %d", *score);
		int width_text, height_text; 
        //
        // Récupère la taile de la boite de texte qui affichera le texte
        // contenu dans la variable text.
        //
        MLV_get_size_of_text( MonScore, &width_text, &height_text );
        int positionX = (width_text), positionY = 150;
        //
        // Affichage du texte
        //
        MLV_draw_text( positionX, positionY,MonScore, MLV_COLOR_WHITE);


		MLV_actualise_window();

}

void BoiteDeTexte1(const char* texte){


        // Taille de la future boite qui affichera le texte.
        int width_text, height_text; 
        //
        // Récupère la taile de la boite de texte qui affichera le texte
        // contenu dans la variable text.
        //
        MLV_get_size_of_text( texte, &width_text, &height_text );
        int positionX = (width_text-310), positionY = 200;
        //
        // Affichage du texte
        //
        MLV_draw_text( positionX, positionY,texte, MLV_COLOR_WHITE);


	MLV_actualise_window();

}

void RecupPlateau(Plateau* plateau){
	if (plateau->card==0){
		return;
	}
	char formes[plateau->card];
  	char couleurs[plateau->card];
	Piece* sauvegarde = plateau->premier;
	formes[0] = sauvegarde->forme;
	couleurs[0] = sauvegarde->couleur;
	sauvegarde = sauvegarde->suiv;
	

	for (int j=1;j<plateau->card;j++){
		formes[j]=sauvegarde->forme;
		couleurs[j]=sauvegarde->couleur;
		sauvegarde=sauvegarde->suiv;
	}
	dessine_pieces_plateau(formes, couleurs,plateau->card);
}

void RecupSuiv(Piece* tabPieces[]){
	
	char formes[5];
  	char couleurs[5];
	

	for (int j=0;j<5;j++){
		formes[j]=tabPieces[j]->forme;
		couleurs[j]=tabPieces[j]->couleur;
		
	}
	dessine_liste_coin(formes, couleurs,5);
}

int quitter=0;
MLV_Image *image;

int main(void){
	
	


		
        int image_width, image_height;
        MLV_Music* music;

	
    			


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

            EffetChargement("Initialisation du plateau");
            
            
   		
        //
        // On créé et affiche la fenêtre
        //
        MLV_create_window( "Tetriste", "image", LARGEUR_FENETRE, HAUTEUR_FENETRE );
        MLV_enable_full_screen( );
        //
        // On charge en mémoire deux fichiers images.
        //
        image = MLV_load_image( "menu.png" );
        //
        // On redimensionne les images de sorte à ce que la taille soit la
        // plus grande comprise dans le cadre widthxheight
        //
        MLV_resize_image_with_proportions( image, LARGEUR_FENETRE, HAUTEUR_FENETRE);
        //
        // On récupère la nouvelle taille de l'image afin de l'utiliser pour
        // redimensionner la fenêtre.
        //
    	MLV_get_image_size( image, &image_width, &image_height );
        //
        // On redimensionne la fenêtre
        //
        MLV_change_window_size( image_width, image_height );
        
        //
        // On affiche l'image
        //
        MLV_draw_image( image, 0, 0 );
        
         MLV_init_audio( );
        //
        // Charge en mémoire un fichier contenant un morceau de musique.
        //
        music = MLV_load_music( "musique.ogg" );
        //
        // Joue la musique chargée en mémoire.
        //
        MLV_play_music( music, 1.0, -1 );
        //
        
       

            DeroulementJeu(nom, &score, plateau, &res, tabPieces);
            
        }
        // Reponse => Charger la derniere partie
        else if (res == 'C' || res == 'c'){
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
                
               
                
                 //
        // On créé et affiche la fenêtre
        //
        MLV_create_window( "Tetriste", "image", LARGEUR_FENETRE, HAUTEUR_FENETRE );
		MLV_enable_full_screen( );
        //
        // On charge en mémoire deux fichiers images.
        //
        image = MLV_load_image( "menu.png" );
        //
        // On redimensionne les images de sorte à ce que la taille soit la
        // plus grande comprise dans le cadre widthxheight
        //
        MLV_resize_image_with_proportions( image, LARGEUR_FENETRE, HAUTEUR_FENETRE);
        //
        // On récupère la nouvelle taille de l'image afin de l'utiliser pour
        // redimensionner la fenêtre.
        //
    	MLV_get_image_size( image, &image_width, &image_height );
        //
        // On redimensionne la fenêtre
        //
        MLV_change_window_size( image_width, image_height );
        //
        // On affiche l'image
        //
        MLV_draw_image( image, 0, 0 );
        
         MLV_init_audio( );
        //
        // Charge en mémoire un fichier contenant un morceau de musique.
        //
        music = MLV_load_music( "musique.ogg" );
        //
        // Joue la musique chargée en mémoire.
        //
        MLV_play_music( music, 1.0, -1 );
        AfficherScore(&score);
		RecupSuiv(tabPieces);
        //
        

                DeroulementJeu(nom, &score, plateau, &res, tabPieces);
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
                
   
                  
        // On créé et affiche la fenêtre
        //
        MLV_create_window( "Tetriste", "image", LARGEUR_FENETRE, HAUTEUR_FENETRE );
		MLV_enable_full_screen( );
        //
        // On charge en mémoire deux fichiers images.
        //
        image = MLV_load_image( "menu.png" );
        //
        // On redimensionne les images de sorte à ce que la taille soit la
        // plus grande comprise dans le cadre widthxheight
        //
        MLV_resize_image_with_proportions( image, LARGEUR_FENETRE, HAUTEUR_FENETRE);
        //
        // On récupère la nouvelle taille de l'image afin de l'utiliser pour
        // redimensionner la fenêtre.
        //
    	MLV_get_image_size( image, &image_width, &image_height );
        //
        // On redimensionne la fenêtre
        //
        MLV_change_window_size( image_width, image_height );
        //
        // On affiche l'image
        //
        MLV_draw_image( image, 0, 0 );
        
         MLV_init_audio( );
        //
        // Charge en mémoire un fichier contenant un morceau de musique.
        //
        music = MLV_load_music( "musique.ogg" );
        //
        // Joue la musique chargée en mémoire.
        //
        MLV_play_music( music, 1.0, -1 );
        //
        

       	// Debut du jeu reinitialiser
        DeroulementJeu(nom, &score, plateau, &res, tabPieces);         
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
    }while (quitter!= 1);
     MLV_stop_music();
        //
        // Ferme les morceaux de musiques qui ont été ouverts.
        //
        MLV_free_music( music );
        //
        // Arrête l'infrastructure son de la librairie MLV.
        //
        MLV_free_audio();
        
}
