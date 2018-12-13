#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <pthread.h>
#include "mesfonctions.h"

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;

void *poser_bombe( void *arg){
    pthread_mutex_lock(&mutex);


    arg_bombe* barg=(arg_bombe*)arg;
    int n= barg->n;


    Joueur j= barg->j;
    int obt_expl=barg->obt_expl;

    int ligne_bombe= j.ligne;
    int colonne_bombe=j.colonne;
    damier[ligne_bombe][colonne_bombe]=5;
    pthread_mutex_unlock(&mutex);
    for(int sec=0;sec<n;sec++){
        _sleep(1000);

    }
    pthread_mutex_lock(&mutex);
    obt_expl=0;

    int *a;

    for (int i=-n; i<=n; i++){


        switch (damier[ligne_bombe+i][colonne_bombe]){
            case 2:
                damier[ligne_bombe+i][colonne_bombe]=0;
                obt_expl++;
            case 3:
                damier[ligne_bombe+i][colonne_bombe]=0;
        }
        if (damier[ligne_bombe][colonne_bombe+i]==2){
            damier[ligne_bombe][colonne_bombe+i]=0;
            obt_expl++;
        }
        if (ligne_bombe==4 && (colonne_bombe==0 || colonne_bombe==1) ){
            if (damier[ligne_bombe][23-i+colonne_bombe]==2){
                damier[ligne_bombe][23-i+colonne_bombe]=0;
                obt_expl++;
            }
        }
        if (ligne_bombe==4 && (colonne_bombe==23 || colonne_bombe==22) ){
            if (damier[ligne_bombe][i-23+colonne_bombe]==2){
                damier[ligne_bombe][i-23+colonne_bombe]=0;
                obt_expl++;
            }
        }

    }
    pthread_mutex_unlock(&mutex);
    }



