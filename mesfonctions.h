#ifndef MESFONCTIONS_H_INCLUDED
#define MESFONCTIONS_H_INCLUDED
typedef struct {
char pseudo[30]; //nom du joueur
int numero; // numero du joueur
int ligne; //ligne du damier
int colonne; //colonne du damier
float score_obtenu;

}Joueur;


typedef struct {
int n;
int **damier;
int *place_bombe;
int *point_obs_exp;
}arg_explosion;

typedef struct {
int *n;
int **damier;
int *place_bombe;
Joueur *j;
}arg_exp_j;


void afficher(int **damier);
void placer_obstacles(int **damier);
Joueur placer_joueur(int **damier, Joueur j);
Joueur deplacement(int **damier,Joueur j, int touche);

void *thread_explosion( void *arg);
Joueur play(int **damier, Joueur j, int *n);
float score(int nbr_bombe, int obt_expl, int n);
void sauvegarde_score(Joueur j);
void initialiser_tableau_scores(void);

#endif // MESFONCTIONS_H_INCLUDED
