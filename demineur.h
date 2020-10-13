#include "argv.h"
#include "stdio.h"
#include <stdlib.h>
#include <stdio.h>
#include "monconio.h"
#include "ansi.h"
#include <time.h>

#define HAUT 65
#define BAS 66
#define DROITE 67
#define GAUCHE 68
#define m 109
#define SPACE 32
#define ECHAP 27
#define MODEFLECHE '['

// Structure CASE utilisée pour le tableau de jeu //

typedef struct
    {
        char visible;
        char val;
    } CASE ;

////////////////////////////////////////////////////

///////////// Prototype des fonctions //////////////
int tailleX(void);
int tailleY(void);
int nbBombe(int,int);
void initJeu(void);
int showAround(CASE*,int, int);
int initTerrain(CASE*, int, int, int);
void rdyCheck(void);
void showTerrain(CASE*, int, int);
char pression(CASE*, int, int, int);
int caseSpace(CASE*, int, int, int, int, int);
int casem (CASE* , int);
void showCursor (int, int);
int winCondition(CASE*, int, int, int);
int again (void);
int clearTerrain(CASE*, int, int);
int looseCondition(CASE*, int);
int boucleJeu(CASE* , int, int, int, int, int);
////////////////////////////////////////////////////


