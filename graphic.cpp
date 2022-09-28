// include de base
#include <stdio.h>
#include <stdlib.h>

// include pour la partie graphique
#include <SDL2/SDL.h>
#include <cstdlib>

#include "graphic.h"

SDL_Window* pWindow{ nullptr };
SDL_Renderer* pRenderer{ nullptr };

SDL_Window* pfenetre{ nullptr };
SDL_Renderer* pRegle { nullptr };
int Tableau_position_case_abscisse[90];
int Tableau_position_case_ordonne[90];
int Grille_sudoku_abscisse[90];
int Grille_sudoku_ordonne[90];
int Case_grise_abscisse[90];
int Case_grise_ordonne[90];
int coordonnee_bouton[90];
int coordonne_regle[20];
int position_curseur;
int position_1 = 0;
int instance = 0;
int choix = 0;
int score=2000;
int millier;
int centaine;
int dizaine;
int unity;
int heure_dizaine;
int heure_unite;
int minute_dizaine;
int minute_unite;
int seconde_dizaine;
int seconde_unite;

int GrilleNombre [9][9];
int GrilleSudo [9][9]; // grille à trou
int GrilleUtilisateur [9][9]; // grille sudoku que va remplir l'utilisateur
int temps_debut;
int temps_fin;
int comptage_seconde;
int comptage_minute;
int comptage_heure;
int seconde_1;
static int temps_ecoule=0;

SDL_TimerID my_timer_id=-1;

void creation_GrilleSudo(int GrilleNombre[9][9], int nbTrou);
void regle ();
void victoire();
void bouton_general();
void creation_GrilleNombre();


void damier(){
    if (my_timer_id == -1)
        my_timer_id = SDL_AddTimer(1000, my_callbackfunc, nullptr);
    SDL_Rect colorBar;
    colorBar.x = 60; colorBar.y = 30; colorBar.w = 35; colorBar.h = 35;

    for ( int i = 0; i != 81; i += 1, colorBar.x += 40){
        SDL_SetRenderDrawColor( pRenderer, 255, 255, 255, 255 );
        if (i%3==0){
            colorBar.x += 20;
        }
        if (i%27==0){
            colorBar.y += 20;
        }
        if (i%9==0){
            colorBar.y += 40;
            colorBar.x = 60;
        }
        Grille_sudoku_abscisse[i]=colorBar.x;
        Grille_sudoku_ordonne[i]=colorBar.y;
        SDL_RenderFillRect( pRenderer, &colorBar );
        SDL_RenderPresent( pRenderer );
    }

}

void carre_blanc(int x, int y){
        SDL_Rect colorBar;
        colorBar.x = x; colorBar.y = y; colorBar.w = 35; colorBar.h = 35;
        SDL_SetRenderDrawColor( pRenderer, 255, 255, 255, 255 );

        SDL_RenderFillRect( pRenderer, &colorBar );
        SDL_RenderPresent( pRenderer );
}

void image_general(char* Tableau_couleur,int chiffre,int taille_abscisse_rectangle,int taille_ordonne_rectangle,int position_abscisse_image,int position_ordonne_image){
    const char* Chiffre_a_afficher;

    // ces 3 petites lignes permettent de définir unb tableau sans avoir à écrire les 50 lignes

    char Tableau_image_cup [168][21]; // [nombre d'image][nombre de caractère que contient son nom]
    for (int i = 0; i <= 84; i++){
        sprintf(Tableau_image_cup[i], "cup/%d.bmp", i);
    }


    if (strcmp(Tableau_couleur,"Tableau_cup") == 0){ // si ces 2 chaines de caractère sont égales
            Chiffre_a_afficher=Tableau_image_cup[chiffre];
    }

    const char* Tableau_image_blanc [10];

        Tableau_image_blanc[0]="chiffre/0_blanc.bmp";
        Tableau_image_blanc[1]="chiffre/1_blanc.bmp";
        Tableau_image_blanc[2]="chiffre/2_blanc.bmp";
        Tableau_image_blanc[3]="chiffre/3_blanc.bmp";
        Tableau_image_blanc[4]="chiffre/4_blanc.bmp";
        Tableau_image_blanc[5]="chiffre/5_blanc.bmp";
        Tableau_image_blanc[6]="chiffre/6_blanc.bmp";
        Tableau_image_blanc[7]="chiffre/7_blanc.bmp";
        Tableau_image_blanc[8]="chiffre/8_blanc.bmp";
        Tableau_image_blanc[9]="chiffre/9_blanc.bmp";


    if (strcmp(Tableau_couleur,"Tableau_blanc") == 0){
            Chiffre_a_afficher=Tableau_image_blanc[chiffre];
    }

    const char* Tableau_image_gris [9];
        Tableau_image_gris[1]="chiffre/1_gris.bmp";
        Tableau_image_gris[2]="chiffre/2_gris.bmp";
        Tableau_image_gris[3]="chiffre/3_gris.bmp";
        Tableau_image_gris[4]="chiffre/4_gris.bmp";
        Tableau_image_gris[5]="chiffre/5_gris.bmp";
        Tableau_image_gris[6]="chiffre/6_gris.bmp";
        Tableau_image_gris[7]="chiffre/7_gris.bmp";
        Tableau_image_gris[8]="chiffre/8_gris.bmp";
        Tableau_image_gris[9]="chiffre/9_gris.bmp";

    if (strcmp(Tableau_couleur,"Tableau_gris") == 0){
            Chiffre_a_afficher=Tableau_image_gris[chiffre];
    }

    const char* Tableau_image_rouge [9];
        Tableau_image_rouge[1]="chiffre/1_rouge.bmp";
        Tableau_image_rouge[2]="chiffre/2_rouge.bmp";
        Tableau_image_rouge[3]="chiffre/3_rouge.bmp";
        Tableau_image_rouge[4]="chiffre/4_rouge.bmp";
        Tableau_image_rouge[5]="chiffre/5_rouge.bmp";
        Tableau_image_rouge[6]="chiffre/6_rouge.bmp";
        Tableau_image_rouge[7]="chiffre/7_rouge.bmp";
        Tableau_image_rouge[8]="chiffre/8_rouge.bmp";
        Tableau_image_rouge[9]="chiffre/9_rouge.bmp";

    if (strcmp(Tableau_couleur,"Tableau_rouge") == 0){
            Chiffre_a_afficher =Tableau_image_rouge[chiffre];
    }

    const char* Tableau_image_bleu [20];
        Tableau_image_bleu[1]="chiffre/1_bleu.bmp";
        Tableau_image_bleu[2]="chiffre/2_bleu.bmp";
        Tableau_image_bleu[3]="chiffre/3_bleu.bmp";
        Tableau_image_bleu[4]="chiffre/4_bleu.bmp";
        Tableau_image_bleu[5]="chiffre/5_bleu.bmp";
        Tableau_image_bleu[6]="chiffre/6_bleu.bmp";
        Tableau_image_bleu[7]="chiffre/7_bleu.bmp";
        Tableau_image_bleu[8]="chiffre/8_bleu.bmp";
        Tableau_image_bleu[9]="chiffre/9_bleu.bmp";

        Tableau_image_bleu[10]="image/curseur.bmp";
        Tableau_image_bleu[11]="image/Bandeau_noir.bmp";
        Tableau_image_bleu[12]="image/Fond_noir.bmp";
        Tableau_image_bleu[13]="image/debut.bmp";
        Tableau_image_bleu[14]="image/niveau.bmp";
        Tableau_image_bleu[15]="image/exemple.bmp";
        Tableau_image_bleu[16]="image/regle.bmp";
        Tableau_image_bleu[17]="image/chrono.bmp";
        Tableau_image_bleu[18]="image/point.bmp";
        Tableau_image_bleu[19]="image/score.bmp";
        Tableau_image_bleu[20]="image/temps_score.bmp";

     if (strcmp(Tableau_couleur,"Tableau_bleu") == 0){
            Chiffre_a_afficher =Tableau_image_bleu[chiffre];
    }

    const char* Tableau_image_bleu_marine [9];
        Tableau_image_bleu_marine[1]="chiffre/1_bleu_marine.bmp";
        Tableau_image_bleu_marine[2]="chiffre/2_bleu_marine.bmp";
        Tableau_image_bleu_marine[3]="chiffre/3_bleu_marine.bmp";
        Tableau_image_bleu_marine[4]="chiffre/4_bleu_marine.bmp";
        Tableau_image_bleu_marine[5]="chiffre/5_bleu_marine.bmp";
        Tableau_image_bleu_marine[6]="chiffre/6_bleu_marine.bmp";
        Tableau_image_bleu_marine[7]="chiffre/7_bleu_marine.bmp";
        Tableau_image_bleu_marine[8]="chiffre/8_bleu_marine.bmp";
        Tableau_image_bleu_marine[9]="chiffre/9_bleu_marine.bmp";


    if (strcmp(Tableau_couleur,"Tableau_bleu_marine") == 0){
            Chiffre_a_afficher=Tableau_image_bleu_marine[chiffre];
    }

     const char* Tableau_image_chrono [12];
        Tableau_image_chrono[0]="chiffre/0_chrono.bmp";
        Tableau_image_chrono[1]="chiffre/1_chrono.bmp";
        Tableau_image_chrono[2]="chiffre/2_chrono.bmp";
        Tableau_image_chrono[3]="chiffre/3_chrono.bmp";
        Tableau_image_chrono[4]="chiffre/4_chrono.bmp";
        Tableau_image_chrono[5]="chiffre/5_chrono.bmp";
        Tableau_image_chrono[6]="chiffre/6_chrono.bmp";
        Tableau_image_chrono[7]="chiffre/7_chrono.bmp";
        Tableau_image_chrono[8]="chiffre/8_chrono.bmp";
        Tableau_image_chrono[9]="chiffre/9_chrono.bmp";
        Tableau_image_chrono[10]="chiffre/point.bmp";


    if (strcmp(Tableau_couleur,"Tableau_chrono") == 0){
            Chiffre_a_afficher=Tableau_image_chrono[chiffre];
    }

    SDL_Surface* image = SDL_LoadBMP(Chiffre_a_afficher);
    SDL_Texture* pTextureImage = SDL_CreateTextureFromSurface(pRenderer, image);
    SDL_FreeSurface(image);
    SDL_Rect src1{0, 0, 0, 200};
    SDL_QueryTexture(pTextureImage, nullptr, nullptr, &src1.w, &src1.h);
    SDL_Rect dst1{ position_abscisse_image,position_ordonne_image, taille_abscisse_rectangle, taille_ordonne_rectangle };
    SDL_RenderCopy(pRenderer, pTextureImage, &src1, &dst1);
    SDL_RenderPresent( pRenderer );
    SDL_DestroyTexture(pTextureImage);
}


Uint32 my_callbackfunc(Uint32 interval, void *param){ //@ fonction pour gerer le temps (chronometre)
    SDL_Event event;
    SDL_UserEvent userevent;

    temps_ecoule++;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}


void bouton (){
    SDL_Event event;
    int continuer = 1;
    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            // evenement click sur la croix ---------------------
            case SDL_QUIT:
                continuer = 0;
                SDL_DestroyWindow(pWindow);
                SDL_Quit();
                break;

            // evenement chronometre tous les secondes -----------
            case SDL_USEREVENT:
                {

                // JUJU ICI TU PEUX CREER UN FONTION POUR AFFICHER LE CHRONOMETRTE EN FONTION DU TEMPS : my_timer_id
                //printf("\n a : %d", temps_ecoule);

                    // Calcul temps

                int h = temps_ecoule / (60 * 60);//1 heure = 3600 secondes
                int m = temps_ecoule / 60; //1 minute = 60 secondes
                int s = temps_ecoule % 60;

                char heure_1[5];
                itoa(h, heure_1, 10);
                if (h>=10){
                    heure_dizaine=heure_1[0]-'0';
                    heure_unite=heure_1[1]-'0';
                }
                else {
                    heure_dizaine=0;
                    heure_unite=heure_1[0]-'0';
                }

                char minute_1[5];
                itoa(m, minute_1, 10);
                if (m>=10){
                     minute_dizaine=minute_1[0]-'0';
                     minute_unite=minute_1[1]-'0';
                }
                else {
                     minute_dizaine =0;
                     minute_unite=minute_1[0]-'0';
                }

                char seconde_1[5];
                itoa(s, seconde_1, 10);
                if (s >=10){
                  seconde_dizaine=seconde_1[0]-'0';
                  seconde_unite=seconde_1[1]-'0';
                }
                else {
                     seconde_dizaine=0;
                     seconde_unite=seconde_1[0]-'0';
                }

                // Affichage

                image_general((char *)"Tableau_chrono",heure_dizaine,35,35,100,35);
                image_general((char *)"Tableau_chrono",heure_unite,35,35,140,35);
                image_general((char *)"Tableau_chrono",10,35,35,180,35);
                image_general((char *)"Tableau_chrono",minute_dizaine,35,35,220,35);
                image_general((char *)"Tableau_chrono",minute_unite,35,35,260,35);
                image_general((char *)"Tableau_chrono",10,35,35,300,35);
                image_general((char *)"Tableau_chrono",seconde_dizaine,35,35,340,35);
                image_general((char *)"Tableau_chrono",seconde_unite,35,35,380,35);



                break;
                }

            // evenement click de la souris ---------------------
            case SDL_MOUSEBUTTONUP:
                int ancienne_position_curseur;
                if (instance==0){
                    instance+=1;
                    ancienne_position_curseur=1;
                }

                for (int position_curseur = 1; position_curseur != 19; position_curseur += 1){
                    if (   event.button.y > Tableau_position_case_ordonne[position_curseur]
                        && event.button.y <= Tableau_position_case_ordonne[position_curseur]+35
                        && event.button.x > Tableau_position_case_abscisse[position_curseur]
                        && event.button.x <= Tableau_position_case_abscisse[position_curseur]+35){
                          image_general((char *)"Tableau_bleu",1,35,35,70,525);
                          image_general((char *)"Tableau_bleu",11,40,20,64,505); // permet de mettre un bandeau noir au dessus du 1
                          image_general((char *)"Tableau_bleu",11,40,20,64+(ancienne_position_curseur-1)*42,505); // permet de mettre un bandeau noir sur l'ancienne position du curseur
                          image_general((char *)"Tableau_bleu",ancienne_position_curseur,35,35,70+(ancienne_position_curseur-1)*42,525); // permet de remettre l'ancienne case séléctiononer en bleu
                          image_general((char *)"Tableau_bleu_marine",position_curseur,35,35,70+(position_curseur-1)*42,525); // permet de mettre la nouvelle case séléctionné en rouge
                          image_general((char *)"Tableau_bleu",10,25,20,75+(position_curseur-1)*42,505); // permet de mettre le cursuer dans sa nouvelle position
                          ancienne_position_curseur=position_curseur;
                    }
                }
                int ajout =0;
                for (int case_grise=1; case_grise !=82; case_grise+=1){
                    if (   event.button.y > Case_grise_ordonne[case_grise]
                        && event.button.y <= Case_grise_ordonne[case_grise]+35
                        && event.button.x > Case_grise_abscisse[case_grise]
                        && event.button.x <= Case_grise_abscisse[case_grise]+35){
                        ajout=1;
                    }
                }

                 for (int position_grille =0; position_grille != 82; position_grille +=1){
                    if (   event.button.y > Grille_sudoku_ordonne[position_grille]
                        && event.button.y <= Grille_sudoku_ordonne[position_grille]+35
                        && event.button.x > Grille_sudoku_abscisse[position_grille]
                        && event.button.x <= Grille_sudoku_abscisse[position_grille]+35
                        && ajout==0){

                        ajoute_chiffre (position_grille, ancienne_position_curseur);

                        int valide_victoire = verifie_si_fin_du_jeu();

                        if (valide_victoire == 1){
                            victoire();
                        }
                    }
                }
            ajout=0;
            break;
        }
    }
}


void curseur(){
    for (int j = 1; j != 10; j += 1){
        image_general((char *)"Tableau_bleu",j,35,35,70+(j-1)*42,525);
        Tableau_position_case_abscisse[j]=70+(j-1)*42;
        Tableau_position_case_ordonne[j]=525;
    }
    image_general((char *)"Tableau_bleu",10,25,20,75,505);
    image_general((char *)"Tableau_bleu_marine",1,35,35,70,525);

    }


void calcul_grille(char* Tableau_couleur,int chiffre,int case_vertical_chiffre, int case_horizontal_chiffre,int emplacement_tableau){
    int verticale_bordure=90;
    int horizontale_bordure= 60;

    if (case_horizontal_chiffre>2){
        horizontale_bordure+=20;
    }
    if (case_horizontal_chiffre>5){
        horizontale_bordure+=20;
    }
    if (case_vertical_chiffre> 2){
        verticale_bordure+=20;
    }
    if (case_vertical_chiffre> 5){
        verticale_bordure+=20;
    }
    Case_grise_abscisse[emplacement_tableau] = case_horizontal_chiffre*40 + horizontale_bordure;
    Case_grise_ordonne[emplacement_tableau] = case_vertical_chiffre*40 + verticale_bordure;
    image_general(Tableau_couleur,chiffre,35,35,case_horizontal_chiffre*40 + horizontale_bordure,case_vertical_chiffre*40 + verticale_bordure);
}


void initialisation_grille(int GrilleSudo[9][9]){ // place les chiffres gris
    if (coordonnee_bouton[17]==5){ // niveau facile
        creation_GrilleSudo(GrilleNombre, 30);//30
    }
    if (coordonnee_bouton[17]==9){ // niveau moyen
        creation_GrilleSudo(GrilleNombre, 45);
    }
    if (coordonnee_bouton[17]==13 || coordonnee_bouton[17]==1){ // niveau difficile
        creation_GrilleSudo(GrilleNombre, 60);
    }

    int compt = 1;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (GrilleSudo[i][j] != 0){
                calcul_grille((char *)"Tableau_gris",GrilleSudo[i][j],i,j,compt);
                compt += 1;
            }
        }
    }

    temps_debut = SDL_GetTicks();
    printf("%d",temps_debut);

    temps_ecoule = 0;
    score=2000;


}


void bouton_general(){
    coordonnee_bouton[1]=154; //bouton play
    coordonnee_bouton[2]=334;
    coordonnee_bouton[3]=490;
    coordonnee_bouton[4]=540;
    coordonnee_bouton[5]=168;//2 bouton facile x sup
    coordonnee_bouton[6]=353;// x inf
    coordonnee_bouton[7]=225;// y sup
    coordonnee_bouton[8]=287;// y inf
    coordonnee_bouton[9]=168;//3 bouton moyen x sup
    coordonnee_bouton[10]=353; // x inf
    coordonnee_bouton[11]=340; // y sup
    coordonnee_bouton[12]=400;// y inf
    coordonnee_bouton[13]=195;//4 bouton difficile
    coordonnee_bouton[14]=365;
    coordonnee_bouton[15]=453;
    coordonnee_bouton[16]=515;
    coordonnee_bouton[17]=473;//5 bouton point d'exclamation
    coordonnee_bouton[18]=511;
    coordonnee_bouton[19]=10;
    coordonnee_bouton[20]=48;
    //image_general((char *)"Tableau_bleu",5,185,62,168,340);
    SDL_Event bouton;
    int continuer = 1;
    while (continuer){
        SDL_WaitEvent(&bouton);
        switch(bouton.type){
            case SDL_QUIT:
                continuer = 0;
                SDL_DestroyWindow(pWindow);
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONUP:
                for ( int j = 1; j != 20; j += 1){
                    if (   bouton.button.y > coordonnee_bouton[j+2]
                        && bouton.button.y <= coordonnee_bouton[j+3]
                        && bouton.button.x > coordonnee_bouton[j]
                        && bouton.button.x <= coordonnee_bouton[j+1]){
                        if (j==17){
                            regle();
                        }
                        coordonnee_bouton[17] = j;
                        if (j==1 && choix==0){
                            choix = choix + 1;
                            demarrage(j);
                        }
                        if (choix ==1 && (j==5 || j==9 || j==13)){
                            choix = choix + 1;
                           demarrage(2);
                        }
                          //demarrage(j);

                    }
                }
                break;
        }
    }
}

void victoire(){

    // Calcul temps
	int h = temps_ecoule / (60 * 60);//1 heure = 3600 secondes
	int m = temps_ecoule / 60; //1 minute = 60 secondes
	int s = temps_ecoule % 60;


    printf("\n h : %d ",h);
    printf("\n m : %d ",m);
    printf("\n s : %d ",s);

    if (m <20){
        score = score-s;
        score = score -(m*60);
    }
    if (score <10){
            char s[5];
            itoa(score, s, 10);
            millier = 0;
            centaine = 0;
            dizaine =0;
            unity=s[1]-'0';
    }

    if (100>score>10){
            char sm[5];
            itoa(score, sm, 10);
            millier = 0;
            centaine = 0;
            dizaine =sm[0]-'0';
            unity=sm[1]-'0';

    }

    if (1000>score>100){
        char sum[5];
        itoa(score, sum, 10);
        millier = 0;
        centaine = sum[0]-'0';
        dizaine =sum[1]-'0';
        unity=sum[2]-'0';
    }
    if (score >1000){

        char snum[5];
        itoa(score, snum, 10);
        millier = snum[0]-'0';
        centaine = snum[1]-'0';
        dizaine =snum[2]-'0';
        unity=snum[3]-'0';
    }

    // Affichage
      image_general((char *)"Tableau_bleu",12,520,600,0,0);
      image_general((char *)"Tableau_bleu",20,400,100,0,500);
    //image_general((char *)"Tableau_bleu",19,250,100 ,260,450);
    //image_general((char *)"Tableau_bleu",17,250,100 ,20,450);
    image_general((char *)"Tableau_chrono",heure_dizaine,30,30,90,505);
    image_general((char *)"Tableau_chrono",heure_unite,30,30,120,505);
    image_general((char *)"Tableau_chrono",10,30,30,160,505);
     image_general((char *)"Tableau_chrono",minute_dizaine,30,30,200,505);
    image_general((char *)"Tableau_chrono",minute_unite,30,30,250,505);
    image_general((char *)"Tableau_chrono",10,30,30,280,505);
    image_general((char *)"Tableau_chrono",seconde_dizaine,30,30,320,505);
    image_general((char *)"Tableau_chrono",seconde_unite,30,30,360,505);
    image_general((char *)"Tableau_chrono", millier,30,30,90,550);
    image_general((char *)"Tableau_chrono",centaine ,30,30,120,550);
    image_general((char *)"Tableau_chrono",dizaine,30,30,150,550);
    image_general((char *)"Tableau_chrono",unity,30,30,180,550);


    for ( int j = 1; j != 84; j += 1){
        image_general("Tableau_cup",j,850,420,-200,0);
        SDL_Delay(100);
    }

    SDL_Delay(4500);
    image_general((char *)"Tableau_bleu",13,520,600,0,0);
    choix=0;
    creation_GrilleNombre();
    bouton_general();
}

void regle (){
    image_general((char *)"Tableau_bleu",16,520,600,0,0);
    coordonne_regle[1]=60;
    coordonne_regle[2]=130;
    coordonne_regle[3]=445;
    coordonne_regle[4]=470;
    coordonne_regle[5]=475;
    coordonne_regle[6]=510;
    coordonne_regle[7]=10;
    coordonne_regle[8]=48;
    SDL_Event event;
    int continuer = 1;
    while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                SDL_DestroyWindow(pWindow);
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONUP:
                for ( int j = 1; j != 20; j += 1){
                    if (event.button.y > coordonne_regle[j+2]
                        && event.button.y <= coordonne_regle[j+3]
                        && event.button.x > coordonne_regle[j]
                        && event.button.x <= coordonne_regle[j+1]){
                        if(j==5){
                             image_general((char *)"Tableau_bleu",16,520,600,0,0);
                           }
                        if (j==1){
                             image_general((char *)"Tableau_bleu",13,520,600,0,0);
                             bouton_general();
                        }
                }
                break;
        }
        }
    }
}

void demarrage(int valeur_de_j_pour_choix_niveau){
    if (choix==1){
        image_general((char *)"Tableau_bleu",14,520,600,0,0);
        bouton_general();
    }
    if (choix==2){
        image_general((char *)"Tableau_bleu",12,520,600,0,0);

        damier();
        curseur();
        initialisation_grille(GrilleSudo);
        bouton();
    }
}



int creation_fenetre (){
// Création interface graphique --------------------------------------------------------------------------------------------

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(520, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer);
    image_general((char *)"Tableau_bleu",13,520,600,0,0);
    SDL_SetWindowTitle(pWindow, "Sudoku");
    seconde_1=1;
    comptage_seconde=0;
    bouton_general();

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}



