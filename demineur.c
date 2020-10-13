#include "demineur.h"

int main ()
{
    srand(time(NULL));
    system("clear"); // Nettoyage de l'écran //
    int sizeX;
    int sizeY;
    int bombe;
    int newGame = 1; 
    while (newGame == 1) // Tant que l'utilisateur relance une partie //
    {
        int posy = 4;
        int posx = 5; 
        sizeX = tailleX(); // L'utilisateur choisi la taille X de la zone de jeu //
        sizeY = tailleY(); // L'utilisateur choisi la taille Y de la zone de jeu //
        bombe = nbBombe(sizeX,sizeY); // L'utilisateur choisi le nombre de bombe //
        CASE * jeu = (CASE*) malloc(sizeof(CASE)*sizeX*sizeY); // Déclaration du tableau en CASE* //
        initTerrain(jeu, sizeX, sizeY, bombe); // Initialisation du terrain //
        rdyCheck(); // On attends que l'utilisateur lance la partie //
        int alive = boucleJeu(jeu, sizeX, sizeY, bombe, posx, posy); // Boucle de jeu, si on en sort on a soit perdu soit gagner //
        system("clear"); // Nettoyage de l'écran //
        clearTerrain(jeu, sizeX, sizeY); // On rends tout les caractère du tableau visible pour ensuite l'afficher //
        showTerrain(jeu, sizeX, sizeY); // On affiche une dernière fois le terrain pour montrer a l'utilisateur qu'il a été mauvais et que l'erreur viens de lui //
        jeu = NULL;
        if (alive == 1) // Partie Gagnée ? //
        {
            printf("C'est gagné, félicitation, une autre partie ?\r\nSPACE pour relancer une partie.\r\nECHAP pour fermer le programme\r\n");
        }
        else if (alive == 2) // Partie Perdue ? //
        {
            printf("C'est perdu, dommage, une autre partie ?\n\rSPACE pour relancer une partie.\n\rECHAP pour fermer le programme\n\r");
        }
        newGame = again(); // Une nouvelle partie ? //
        free(jeu); // Libération du tableau de jeu //
    }
    
}
