#include <stdio.h>
#include <stdlib.h> //pour nbr aleatoires
#include <time.h>
#include "mesfonctions.h"

//void afficher(int damier[9][24]){
void afficher(int **damier){
    for(int i =0; i<9; i++){        // damier 9x24, rien= 0, mur=1, obstacle=2, bomberman=3 et 4 , bombe= 5
        for(int k=0; k <24; k++){
            switch(damier[i][k]){
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf("#"); // mur
                    break;
                case 2:
                    printf("x"); //obstacle
                    break;
                case 3:
                    printf("B"); // Bomberman 1
                    break;
                case 4:
                    printf("S"); // Bomberman 2
                    break;
                case 5:
                    printf("o"); // bombe
                    break;
            }
        }
        printf(" \n");
    }
}

void placer_obstacles(int **damier){ //obstacles = 2, affichage x

    srand(time(NULL));
    for (int i=1;i<7;i++){
        for(int j=1;j<22;j++){
            if(damier[i][j]==0 && damier[i-1][j]!= 3 && damier[i+1][j]!= 3 && damier[i][j-1]!= 3 && damier[i][j+1]!= 3){
                damier[i][j]= rand()%2 * 2;
            }
        }
    }

}

Joueur placer_joueur(int **damier, Joueur j){

    srand(time(NULL));
    int i=0;
    int k=0;
    while(damier[i][k]!=0 ){
        i= rand()%9+1;
        k= rand()%24+1;
    }
    damier[i][k]= 2+j.numero;
    printf("i=%d, k=%d\n", i,k);
    j.ligne=i;
    j.colonne=k;
    return j;
}





