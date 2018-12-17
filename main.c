#include <stdio.h>
#include <stdlib.h>
#include "mesfonctions.h"
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <pthread.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define LIGNES 9
#define COLONNES 24

int main(int argc, char* argv[]){

    // Initialisation du damier (murs) //

    int **damier = (int **)malloc(LIGNES*sizeof(int)); //initialisation damier
	for (int i=0; i < LIGNES; i++) {
		damier[i] = (int *)malloc(COLONNES*sizeof(int));
	}
	for (int k=0; k<COLONNES; k++){ //construction murs
        damier[0][k]= 1;
        damier[LIGNES -1][k]= 1;
        for (int j=1;j<8;j++){
            damier[j][k]=0;
        }
	}
	{
	damier[1][0]= 1;
	damier[1][23]=1;
	damier[2][0]= 1;
	damier[2][2]= 1;
	damier[2][3]= 1;
	damier[2][5]= 1;
	damier[2][8]= 1;
	damier[2][10]= 1;
	damier[2][11]= 1;
	damier[2][12]= 1;
	damier[2][14]= 1;
	damier[2][15]= 1;
	damier[2][17]= 1;
	damier[2][21]= 1;
	damier[2][23]= 1;
	damier[3][0]= 1;
	damier[3][2]= 1;
	damier[3][5]= 1;
	damier[3][6]= 1;
	damier[3][8]= 1;
	damier[3][10]= 1;
	damier[3][14]= 1;
	damier[3][17]= 1;
	damier[3][18]= 1;
	damier[3][20]= 1;
	damier[3][21]= 1;
	damier[3][23]= 1;
	damier[4][2]= 1;
	damier[4][3]= 1;
	damier[4][5]= 1;
	damier[4][7]= 1;
	damier[4][8]= 1;
	damier[4][10]= 1;
	damier[4][11]= 1;
	damier[4][12]= 1;
	damier[4][14]= 1;
	damier[4][15]= 1;
	damier[4][17]= 1;
	damier[4][19]= 1;
	damier[4][21]= 1;
	damier[5][0]= 1;
	damier[5][2]= 1;
	damier[5][5]= 1;
	damier[5][8]= 1;
	damier[5][12]= 1;
	damier[5][14]= 1;
	damier[5][17]= 1;
	damier[5][21]= 1;
	damier[5][23]= 1;
	damier[6][0]= 1;
	damier[6][2]= 1;
	damier[6][3]= 1;
    damier[6][5]= 1;
	damier[6][8]= 1;
	damier[6][10]= 1;
	damier[6][11]= 1;
	damier[6][12]= 1;
	damier[6][14]= 1;
	damier[6][15]= 1;
	damier[6][17]= 1;
	damier[6][21]= 1;
	damier[6][23]= 1;
	damier[7][0]= 1;
	damier[7][23]= 1;
	}

    Joueur joueur1;

    // Tableau des scores //
/*
    int initialiser;
    printf("initialiser tableau des scores? oui:1\n");
    scanf("%d",&initialiser);
    if(initialiser==1){
        initialiser_tableau_scores();
    }
    printf("quel est ton pseudo?\n");
    scanf("%s", &joueur1.pseudo);
    printf("pseudo: %s\n", joueur1.pseudo);
    */
    joueur1.numero=1;
    // n //
    printf("combien de cases voisines vont exploser les bombes ?\n ");
    int n;
    scanf("%d", &n );
    printf("n= %d\n", n);

    // placement joueur et obstacle dans le damier //
    joueur1 = placer_joueur(damier, joueur1);
    placer_obstacles(damier);
    afficher(damier);

    // démarrage jeu //
    joueur1 = play( damier, joueur1, &n);
    if (n<0){
        printf("perdu");
    }

    // sauvegarde dans le fichier des scores //
    sauvegarde_score(joueur1);


    //Problèmes:
    // no problem <3333


    return 0;
}

