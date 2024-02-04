/* GESTION DE L'AFFICHAGE */

#include "../hdr/affichage.h"
#include "../hdr/piece.h"
#include "../hdr/plateau.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <MLV/MLV_all.h>

#define LARGEUR_FENETRE 1000.0
#define HAUTEUR_FENETRE 500.0
#define TAILLE_PIECE 50.0
#define CENTRE_PIECE_SUR_PLATEAU HAUTEUR_FENETRE -35
#define ECART_CERCLE TAILLE_PIECE / 2.0 + 5.0



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


void Logo(void){
    printf("        ________ _______ ________ ________  __  _______ ________ _______\n");
    printf("       |\033[48;5;24m__    __\033[0m|\033[48;5;226m   ____\033[0m|\033[48;5;40m__    __\033[0m|\033[48;5;196m   __   \033[0m||\033[48;5;24m__\033[0m||\033[48;5;226m  _____\033[0m|\033[48;5;40m__    __\033[0m|\033[48;5;196m   ____\033[0m|\n");
    printf("          |\033[48;5;24m  \033[0m|  |\033[48;5;226m  \033[0m|__     |\033[48;5;40m  \033[0m|  |\033[48;5;196m  \033[0m|__|\033[48;5;196m  \033[0m| __ |\033[48;5;226m  \033[0m|____   |\033[48;5;40m  \033[0m|  |\033[48;5;196m  \033[0m|__\n");
    printf("          |\033[48;5;24m  \033[0m|  |\033[48;5;226m   __\033[0m|    |\033[48;5;40m  \033[0m|  |\033[48;5;196m     ___\033[0m||\033[48;5;24m  \033[0m||\033[48;5;226m____   \033[0m|  |\033[48;5;40m  \033[0m|  |\033[48;5;196m   __\033[0m|\n");
    printf("          |\033[48;5;24m  \033[0m|  |\033[48;5;226m  \033[0m|____   |\033[48;5;40m  \033[0m|  |\033[48;5;196m   __  \033[0m| |\033[48;5;24m  \033[0m| ____|\033[48;5;226m  \033[0m|  |\033[48;5;40m  \033[0m|  |\033[48;5;196m  \033[0m|____\n");
    printf("          |\033[48;5;24m__\033[0m|  |\033[48;5;226m_______\033[0m|  |\033[48;5;40m__\033[0m|  |\033[48;5;196m__\033[0m| |\033[48;5;196m___\033[0m||\033[48;5;24m__\033[0m||\033[48;5;226m_______\033[0m|  |\033[48;5;40m__\033[0m|  |\033[48;5;196m_______\033[0m|\n\n\n");
    printf("\033[0m");
}

int DeroulementJeu(char nom[], int* score, Plateau* plateau, char* res, Piece* tabPieces[]){
	MLV_Keyboard_button touche;
	Piece* pieceActuel;
	RecupPlateau(plateau);
	
	//on va recuperer la touche sur laquelle va appuyer l'utilisateur, et on lance l'action correspondante
	

   do{
   	
   		MLV_actualise_window();
   		MLV_wait_keyboard( &touche, NULL, NULL );
   		
   		if (plateau->tailleMax == plateau->card){
   			touche=MLV_KEYBOARD_s;
   		}
   			
   	 			pieceActuel = tabPieces[0];
   	 			
   	 			if (touche== MLV_KEYBOARD_g || touche== MLV_KEYBOARD_d || touche== MLV_KEYBOARD_s){
            
           
                Piece* pieceDerniereTab = GenererPieceAleatoire();
                tabPieces[0] = tabPieces[1];
                tabPieces[1] = tabPieces[2];
                tabPieces[2] = tabPieces[3];
                tabPieces[3] = tabPieces[4];
                tabPieces[4] = pieceDerniereTab;
               }
      
           

            // Differents cas


			//cas d'insertion a gauche
            if(touche== MLV_KEYBOARD_g){
            
            	
                InsererGauche(plateau, pieceActuel);
                DisparaitrePieces(plateau, score, 'G',nom,tabPieces,1);
                RecupPlateau(plateau);
                AfficherScore(score);
				RecupSuiv(tabPieces);
                
            }
            //cas d'insertion a droite
            else if (touche== MLV_KEYBOARD_d){
                
                InsererDroite(plateau, pieceActuel);
                DisparaitrePieces(plateau, score, 'G',nom,tabPieces,1);
                RecupPlateau(plateau);
                AfficherScore(score);
                RecupSuiv(tabPieces);
            }
            
            //cas de decalage
            else if (touche== MLV_KEYBOARD_l){
                do{
                    BoiteDeTexte1("                       Forme (F) - Couleur (C) : ");
                    
                    
					MLV_wait_keyboard( &touche, NULL, NULL );
					
					//cas de decalage de forme
                    if (touche == MLV_KEYBOARD_f ){
                        do {
                        	
                        	RecupPlateau(plateau);
                        	AfficherScore(score);
                            RecupSuiv(tabPieces);
                            BoiteDeTexte1(" Carre (C) - Losange (L) - Rond (R) - Triangle (T) :  ");
                            
                            MLV_wait_keyboard( &touche, NULL, NULL );
                            
                           
                            if (touche == MLV_KEYBOARD_c){
                                DecalageForme(plateau,'C');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                RecupPlateau(plateau);
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                            
                            else if (touche == MLV_KEYBOARD_l){
                                DecalageForme(plateau,'L');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1); 
                                RecupPlateau(plateau); 
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                            else if (touche == MLV_KEYBOARD_r){
                                DecalageForme(plateau,'R');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                RecupPlateau(plateau);
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                            else if (touche == MLV_KEYBOARD_t){
                                DecalageForme(plateau,'T');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                RecupPlateau(plateau);
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                        }while(touche != MLV_KEYBOARD_c && touche != MLV_KEYBOARD_l && touche != MLV_KEYBOARD_r && touche != MLV_KEYBOARD_t);
                        break;
                    }
                    //cas de decalage de couleur
                    else if (touche == MLV_KEYBOARD_c){
                        do{
                        	RecupPlateau(plateau);
                        	AfficherScore(score);
                            RecupSuiv(tabPieces);
                            BoiteDeTexte1("        Rouge (R) - Jaune (J) - Bleu (B) - Vert (V) : ");
                            
                            MLV_wait_keyboard( &touche, NULL, NULL );
                            
                            if (touche == MLV_KEYBOARD_r){
                                DecalageCouleur(plateau,'R');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                RecupPlateau(plateau);
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                            else if (touche == MLV_KEYBOARD_j){
                                DecalageCouleur(plateau,'J');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                RecupPlateau(plateau);
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                            else if (touche == MLV_KEYBOARD_b){
                                DecalageCouleur(plateau,'B');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                RecupPlateau(plateau);
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                            else if (touche == MLV_KEYBOARD_v){
                                DecalageCouleur(plateau,'V');
                                DisparaitrePieces(plateau, score, 'L', nom, tabPieces, 1);
                                RecupPlateau(plateau);
                                AfficherScore(score);
                                RecupSuiv(tabPieces);
                                break;
                            }
                        }while(touche != MLV_KEYBOARD_r && touche != MLV_KEYBOARD_j && touche != MLV_KEYBOARD_b && touche != MLV_KEYBOARD_v);
                        break;
                    }
                }while (touche != MLV_KEYBOARD_c && touche != MLV_KEYBOARD_f);
               }           
                
        //Sauvegarde a la fin du jeu    
        else if(touche == MLV_KEYBOARD_s){   
       	MLV_actualise_window();

	
	//si l'utilisateur a ete contraint d'arreter la partie car il n'y a plus de place sur le plateau : ecran de "game over"
	if(plateau->tailleMax == plateau->card){
       	
       	

       	gameOver();
       	
       	MLV_Sound* son;
       	MLV_stop_music();
       	
       	//son de game over
       	son = MLV_load_sound( "gameover.wav" );
       	MLV_actualise_window();
  
       
        
        MLV_play_sound( son, 1.0 );
        MLV_wait_seconds(5);
        
        // Arrête toutes les sons.
        
        MLV_stop_all_sounds();
        
        // Ferme les morceaux de musiques qui ont été ouverts.
        
        MLV_free_sound( son );
	}

       	
       	//on arrete la musique du jeu et on lance l'ecran de sauvegarde
       	MLV_stop_music();
       	MLV_actualise_window();
       	MLV_clear_window(MLV_COLOR_BLACK);
		sauvegarde();

       	
       
       	MLV_wait_seconds(3);
       
       			// Met a jour le classement
                EcrireClassement(nom, *score);

                // Effectue la sauvegarde de la partie
                FILE* sauvegarde = fopen("txt/sauvegarde.txt", "w");
                fprintf(sauvegarde, "%s\n", nom);
                fprintf(sauvegarde, "%d\n", plateau->card);
                fprintf(sauvegarde, "%d\n", *score);

                // Libere l'allocation faite pour la piece qui a ete change de la liste tabPieces
                free(pieceActuel);

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

                if (plateau->card == 0){
                    fprintf(sauvegarde, "\n");
                    fprintf(sauvegarde, "\n");
                    free(plateau);
                    fclose(sauvegarde);
                    MLV_free_image( image );
                    MLV_free_window();
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

            //on libere l'image qui sert de fond a la fenetre, ainsi que la fenetre 
            MLV_free_image( image );
            MLV_free_window();
            
   			}
     
     
    } while (!(touche== MLV_KEYBOARD_s));
     //le jeu s'arrete quand l'utilisateur a choisi de sauvegarder (on le force a sauvegarder si le nombre maximum de piece est atteint)
    
    quitter=1;
    
    
    return 0;
    
}
