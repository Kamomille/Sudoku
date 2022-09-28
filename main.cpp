
// include de base
#include <stdio.h>
#include <stdlib.h>

// include pour la partie graphique
#include <SDL2/SDL.h>
#include <cstdlib>
#include "graphic.h"

// include pour la partie grille sudoku
#include <string.h>
#include <time.h>



// Déclaration ----------------------------------------------------------------------------------

extern int Grille_sudoku_abscisse[90];
extern int Grille_sudoku_ordonne[90];

extern int GrilleNombre [9][9]; // grille avec tous les nombres
extern int GrilleSudo [9][9]; // grille à trou
extern int GrilleUtilisateur [9][9]; // grille sudoku que va remplir l'utilisateur
extern int score;
extern int my_timer_id;

int etatLigne =1, etatColonne =1, etatCase =1;
int colonne, ligne;
int var;

int creation_fenetre ();
void image_general(char* Tableau_couleur,int chiffre,int taille_abscisse_rectangle,int taille_ordonne_rectangle,int position_abscisse_image,int position_ordonne_image);
void carre_blanc(int x, int y);

// Fonctions de recherche -----------------------------------------------------------------------------

int recherche_par_ligne (int Tableau[9][9], int nb, int numLigne){
    int etat = 0;
    for (int i=0; i<9; i++){
        if(Tableau[numLigne][i]==nb){
            etat = 1;
            break;
        }
    }
    return etat; // etat = 0 si nb n'est pas dans le tableau[nb ligne][9]
}

int recherche_par_colonne (int Tableau[9][9], int nb, int numColonne){
    int etat = 0;
    for (int i=0; i<9; i++){
        if(Tableau[i][numColonne]==nb){
            etat = 1;
            break;
        }
    }
    return etat;
}

int recherche_par_case (int Tableau[9][9], int nb, int numLigne, int numColonne){
    int etat = 0;
    for (int i=0; i<3; i++){ //parcourt la case
        for (int j=0; j<3; j++){
            if (Tableau[i+(numLigne*3)][j+(numColonne*3)] == nb){
                etat = 1;
                break;
            }
        }
    }
    return etat;
}

void affichage_GrilleNombre (int GrilleNombre[9][9]){
    printf("\n---Grille Nombre---\n\n");
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            printf("%d ",GrilleNombre[i][j]);
            if (j%3 ==2){
                printf(" ");
            }
        }
        printf("\n");
        if (i%3 ==2){
            printf("\n");
        }
    }
}


// Fonctions grille ----------------------------------------------------------------------------------

void ajoute_chiffre (int position_grille, int ancienne_position_curseur){
    // Affiche les chiffes en blanc ou en rouge dès que l'utilisateur entre un nouveau chiffre

    colonne = position_grille%9;
    ligne = position_grille/9;

    etatColonne = recherche_par_colonne (GrilleUtilisateur, ancienne_position_curseur, colonne);
    etatLigne = recherche_par_ligne (GrilleUtilisateur, ancienne_position_curseur,ligne);
    etatCase = recherche_par_case (GrilleUtilisateur, ancienne_position_curseur, ligne/3, colonne/3);

    if (GrilleUtilisateur[ligne][colonne]== ancienne_position_curseur){ // enleve le chiffre
        carre_blanc(Grille_sudoku_abscisse[position_grille], Grille_sudoku_ordonne[position_grille]);
        GrilleUtilisateur[ligne][colonne] = 0;

    }
    else {
        GrilleUtilisateur[ligne][colonne] = ancienne_position_curseur;

        if ((etatLigne ==0) && (etatColonne ==0) && (etatCase ==0)) {
            image_general((char *)"Tableau_blanc",ancienne_position_curseur,35,35,Grille_sudoku_abscisse[position_grille],Grille_sudoku_ordonne[position_grille]);
        }
        else{
             score=score -10;
            image_general((char *)"Tableau_rouge",ancienne_position_curseur,35,35,Grille_sudoku_abscisse[position_grille],Grille_sudoku_ordonne[position_grille]);
        }
    }

    int ii=0;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if ((GrilleUtilisateur[i][j] != 0) && (GrilleSudo[i][j] == 0)){

                var = GrilleUtilisateur[i][j];
                GrilleUtilisateur[i][j] = 0;
                etatColonne = recherche_par_colonne (GrilleUtilisateur, var, j);
                etatLigne = recherche_par_ligne (GrilleUtilisateur, var,i);
                etatCase = recherche_par_case (GrilleUtilisateur, var, i/3, j/3);
                GrilleUtilisateur[i][j] = var;

                if ((etatLigne ==0) && (etatColonne ==0) && (etatCase ==0)) {
                    image_general((char *)"Tableau_blanc",GrilleUtilisateur[i][j],35,35,Grille_sudoku_abscisse[ii],Grille_sudoku_ordonne[ii]);
                }
                else{
                    image_general((char *)"Tableau_rouge",GrilleUtilisateur[i][j],35,35,Grille_sudoku_abscisse[ii],Grille_sudoku_ordonne[ii]);

                }
            }
            ii += 1;
        }
    }

}

void creation_GrilleNombre(){

// Génération grille --------------------------------------------------------------------------------------------------------


    int nombreAleatoire;
    int possible = 1;
    int fin = 0;
    int tentative = 0;

    memset(GrilleNombre, 0, 9*9*sizeof(int)); // permet d'initialiser toutes les valeurs du tableau à 0
    srand(time(NULL)); //permet de faire fonctionner rand

    while (fin == 0){ // cherche des grilles jusqu'a en trouver une qui marche
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                possible = 0;
                for (int nombre = 1; nombre < 10; nombre++) { // regarde s'il y a une possibilité
                    etatColonne = recherche_par_colonne (GrilleNombre, nombre, i);
                    etatLigne = recherche_par_ligne (GrilleNombre, nombre,j);
                    etatCase = recherche_par_case (GrilleNombre, nombre, j/3, i/3);
                    if ((etatLigne ==0) && (etatColonne ==0) && (etatCase ==0)){
                        possible = 1;
                    }
                }
                etatLigne = 1;
                etatColonne = 1;
                etatCase = 1;
                if (possible == 1){ // s'il y a une possibilité alors on remplit la case avec un chiffre aléatoire possible
                    while((etatLigne ==1) || (etatColonne ==1) || (etatCase ==1)) {
                        nombreAleatoire = (rand() % 9)+1; // -> nombre aléatoire en [1,9]
                        etatColonne = recherche_par_colonne (GrilleNombre, nombreAleatoire, i);
                        etatLigne = recherche_par_ligne (GrilleNombre, nombreAleatoire,j);
                        etatCase = recherche_par_case (GrilleNombre, nombreAleatoire, j/3, i/3);
                    }
                    GrilleNombre[j][i] = nombreAleatoire;
                    etatLigne = 1;
                    etatColonne = 1;
                    etatCase = 1;
                }
                if (GrilleNombre[8][8] != 0){ // grille rempli
                    fin = 1;
                    printf("%d",tentative);
                    printf(" TROUVER !!!!!");
                }
                if(possible == 0) { // on est bloqué, faut génerer une autre grille
                    i = 9;
                    j = 9;
                    tentative += 1;
                    memset(GrilleNombre, 0, 9*9*sizeof(int));
                }
            }
        }
    }
    affichage_GrilleNombre (GrilleNombre);
}

void creation_GrilleSudo(int GrilleNombre[9][9], int nbTrou){

// Enlève les chiffres pour faire une grille à trou ----------------------------------------------------------------------------

    int ligne_aleatoire = 0;
    int colonne_aleatoire = 0;

    memmove (GrilleSudo, GrilleNombre, 9*9*sizeof(int)); // copie grilleNombre dans GrilleSudo
    for (int i = 0; i < nbTrou; i++) {
        while (GrilleSudo[ligne_aleatoire] [colonne_aleatoire] == 0){
            ligne_aleatoire = (rand() % 9)+1;
            colonne_aleatoire = (rand() % 9)+1;
        }
        GrilleSudo[ligne_aleatoire] [colonne_aleatoire] = 0;
    }
    affichage_GrilleNombre (GrilleSudo);

    memmove (GrilleUtilisateur, GrilleSudo, 9*9*sizeof(int)); // copie GrilleSudo dans GrilleUtilisateur
}

int verifie_si_fin_du_jeu(){
    int fin = 1; // verifie que toutes les cases sont remplies
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if ((GrilleUtilisateur[i][j] == 0)){
                fin = 0;
                break;

            }
        }
    }
    int victoire = 0;
    if (fin == 1){
        victoire = 1;
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                var = GrilleUtilisateur[i][j];
                GrilleUtilisateur[i][j] = 0;
                etatColonne = recherche_par_colonne (GrilleUtilisateur, var, j);
                etatLigne = recherche_par_ligne (GrilleUtilisateur, var,i);
                etatCase = recherche_par_case (GrilleUtilisateur, var, i/3, j/3);
                GrilleUtilisateur[i][j] = var;

                if ((etatLigne ==0) && (etatColonne ==0) && (etatCase ==0)) {

                }
                else{
                    victoire = 0;
                    break;
                }
            }
        }
    }

    return victoire;
}


// MAIN ----------------------------------------------------------------------------------

int main(int argc, char* argv[]) {

    //my_timer_id = SDL_AddTimer(1000, my_callbackfunc, nullptr);

    creation_GrilleNombre();

    creation_fenetre ();

    return 0;
}



