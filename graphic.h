#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

void ajoute_chiffre (int position_grille, int ancienne_position_curseur);
void affichage_GrilleNombre (int GrilleNombre[9][9]);
void demarrage(int valeur_de_j_pour_choix_niveau);
int verifie_si_fin_du_jeu();
Uint32 my_callbackfunc(Uint32 interval, void *param); //@ fonction pour gerer le temps (chronometre)

#endif // GRAPHIC_H_INCLUDED
