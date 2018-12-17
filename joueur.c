#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <pthread.h>
#include "mesfonctions.h"
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>

// déplacement des joueurs, poser une bombe et dégats
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER ;

Joueur deplacement(int **damier ,Joueur j, int touche){
    int fleche=0;
    fleche =getch();
    int i= j.ligne;
    int k=j.colonne;
    if (i==-1){
        return j;
    }
    switch(fleche){
        // Joueur 1:
        case 75: //gauche
            if(damier[i][k-1]==0){
            j.colonne--;
            }
            if(i==4 && k==0 && damier[4][23]==0){
                j.colonne=23;
            }
            break;
        case 72: //haut
            if(damier[i-1][k]==0){
            j.ligne--;
            }
            break;
        case 77:  //droite
            if(damier[i][k+1]==0){
            j.colonne++;
            }
            if(i==4 && k==23 && damier[4][0]==0){
                j.colonne=0;
            }
            break;
        case 80: // bas
            if(damier[i+1][k]==0){
            j.ligne++;
            }
            break;

    }
    if( damier[i][k]!=5){
        damier[i][k]=0;
    }

    damier[j.ligne][j.colonne]=2+j.numero;

    return j;
}


void *thread_explosion( void *arg)
{
    arg_explosion* arg_expl =(arg_explosion*)arg;
    int **damier= arg_expl -> damier;
    int n= arg_expl ->n;
    int *place_bombe= arg_expl -> place_bombe;

    Sleep(1000*n);

    int *p_obst_expl=arg_expl ->point_obs_exp;

    int ligne_bombe= place_bombe[0];
    int colonne_bombe= place_bombe[1];

    damier[ligne_bombe][colonne_bombe]=0;

    for (int i=-n; i<=n; i++){

        if(ligne_bombe+i>=0 && ligne_bombe+i < 9 && damier[ligne_bombe+i][colonne_bombe]==2){
            damier[ligne_bombe+i][colonne_bombe]=0;
            *p_obst_expl+=1;
            }
        if (colonne_bombe+i >= 0 && colonne_bombe+i<24 && damier[ligne_bombe][colonne_bombe+i]==2){
            damier[ligne_bombe][colonne_bombe+i]=0;
            *p_obst_expl+=1;
        }
        if (ligne_bombe==4 && (colonne_bombe==0 || colonne_bombe==1) ){
            if (damier[ligne_bombe][23-i+colonne_bombe]==2){
                damier[ligne_bombe][23-i+colonne_bombe]=0;
                *p_obst_expl+=1;
            }
        }
        if (ligne_bombe==4 && (colonne_bombe==23 || colonne_bombe==22) ){
            if (damier[ligne_bombe][i-23+colonne_bombe]==2){
                damier[ligne_bombe][i-23+colonne_bombe]=0;
                *p_obst_expl+=1;
            }
        }
    }
    printf("bombe a explose\n");
    pthread_cond_signal(&cond); //envoie signal au thread que verifie la place du bomberman

    }

void *thread_expl_j( void *arg){ // pour faire exploser bomberman



    arg_exp_j* argg =(arg_exp_j*)arg;
    int **damier= argg -> damier;
    int *n= argg ->n;

    int *place_bombe= argg -> place_bombe;
    int ligne_bombe= place_bombe[0];
    int colonne_bombe= place_bombe[1];
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    Joueur *j = argg ->j;

    if ( (((*j).colonne == colonne_bombe) && ((*j).ligne >= ligne_bombe-*n) && ((*j).ligne <= ligne_bombe+*n) ) ||
		(((*j).ligne == ligne_bombe) && ((*j).colonne >= colonne_bombe-*n) && ((*j).colonne <= colonne_bombe+*n)) ){

        printf("bomberman explose\n");
        damier[(*j).ligne][(*j).colonne]=0;
        *n=-1; // n >0 => on sort du while du play = FIN
    }
    pthread_mutex_unlock(&mutex);

}

Joueur play(int **damier, Joueur j, int *n){

    // Initialisation des paramètres //

    int memo_n = *n;
    int touche=0;
    int obstacle_expl=0;
    int nbr_bombe=0;
    int place_bomb[10][2]={{-1, -1}};

    pthread_t thread_id[10]; // initialisation thread exposion obstacle
    arg_explosion argex[10];

    pthread_t thread_id1[10]; // initialisation thread exposion bomberman
    arg_exp_j arg_2[10];

    for (int i=0; i<10; i++){
        argex[i].damier = damier;
        argex[i].n = *n;
        arg_2[i].damier = damier;
        arg_2[i].n = n;
    }

    // Démarrage du jeu //

    while(touche!=120 && *n>0){      // boucle s'arrete quand on appuie sur x ou quand n>0 (cad qd bomberbam touché)


        arg_2[nbr_bombe %10].j= &j;

        touche= getch();

        // déplacement //
        if (touche==224){ // touche fleche
            j =deplacement(damier,j, touche);
        }

        // explosion des obstacles //

        if (touche==32){ // touche espace
            nbr_bombe++;
            place_bomb [nbr_bombe %10][0]= j.ligne;
            place_bomb [nbr_bombe %10][1]= j.colonne;
            argex[nbr_bombe %10].place_bombe = place_bomb[nbr_bombe %10];
            arg_2[nbr_bombe %10].place_bombe = place_bomb[nbr_bombe %10];
            argex[nbr_bombe %10].point_obs_exp= &obstacle_expl;


            damier[place_bomb[nbr_bombe %10][0]][place_bomb[nbr_bombe %10][1]] = 5;

            pthread_create(&thread_id[nbr_bombe %10],NULL,thread_explosion,&argex[nbr_bombe %10]); // creation thread explose obstacle
            pthread_create(&thread_id1[nbr_bombe %10],NULL,thread_expl_j,&arg_2[nbr_bombe %10]); // mise en route thread verifiant la position bomberman par rapport à une bombe

        }

        // affichage du damier //
        afficher(damier);

    }
     // fermeture des threads //
    /*                              Mis en commentaire car fais beuguer le prog car on ferme des threads qui n'existe pas encore.
    for (int i=0; i<10; i++){
        pthread_join(thread_id[i],NULL);
        pthread_join(thread_id1[i],NULL);
    }
    */
    // calcul du score //
    j.score_obtenu= score(nbr_bombe,obstacle_expl,memo_n );


    return j;
}

float score(int nbr_bombe, int obt_expl, int n){

    float score_obtu = (float)obt_expl /(float)(nbr_bombe*n);
    printf("n= %d\n", n);
    printf("nbr de bombes utilisees = %d \n",nbr_bombe);
    printf("nbr d'obtacles detruits= %d \n", obt_expl);
    printf("score du joueur: %f\n ", score_obtu); //nbr obstacles explosés/(nbr bombes utilisées*n)

    return score_obtu;
}

void initialiser_tableau_scores(void){
    FILE *fichier;
    fichier= fopen("Meilleurs scores.txt","w");
    if (fichier !=0){
        fputs("---Meilleurs scores---\n",fichier);
        fclose(fichier);
        printf("fichier init\n");
    }
}

void sauvegarde_score(Joueur j){

    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant=*localtime(&secondes);
   // printf("%d/%d/%d ; %d:%d:%d\n", instant.tm_mday, instant.tm_mon+1,instant.tm_year+1900, instant.tm_hour, instant.tm_min, instant.tm_sec);

    FILE *fichier;
    fichier = fopen("Meilleurs scores.txt", "a");
    if (fichier !=0){

        fprintf(fichier, "pseudo:%s  \nscore: %f \ndate: %d/%d/%d \n\n",j.pseudo, j.score_obtenu,instant.tm_mday, instant.tm_mon+1,instant.tm_year+1900 );

        fclose(fichier);
    }


}


