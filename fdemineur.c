#include "demineur.h"

// Initialisation Basique des données de jeu + restriction des valeurs possibles //
int tailleX()
{
    int X;
    printf("\n\rDéfinissez la taille du terrain\n\r");
    printf("Inserez la largeur désirée :\n\r");
    scanf("%d", &X);
    while (X > 100 || X < 5)
    {
        printf("\n\rLargeur désirée non valable, veuillez insérer une largeur comprise entre 5 et 100\n\r");
        scanf("%d", &X);
    }
    return (X);
}

int tailleY()
{
    int Y;
    printf("Inserez la hauteur désirée :\n\r");
    scanf("%d", &Y);
    while (Y > 100 || Y < 5)
    {
        printf("\n\rHauteur désirée non valable, veuillez insérer une hauteur comprise entre 5 et 100\n\r");
        scanf("%d", &Y);
    }
    return (Y);
}

int nbBombe(int X,int Y)
{
    int b;
    printf("\n\rInserez un nombre de bombe\n\r");
    scanf("%d", &b);
    while(b > X*Y || b < 1)
    {
        printf("\n\rNombre de bombe désirée non valable, veuillez insérer un nombre de bombe compris entre 1 et %d\n\r",X*Y);
        scanf("%d", &b);
    }
    return (b);
}

//////////////////////////////////////////////////////////////////////////////////////

///////////////////////////// Initialisation du terrain //////////////////////////////
int initTerrain(CASE* jeu, int sizeX, int sizeY, int bombe)
{
    int at;
    for(int i = 0; i<sizeX*sizeY; i++) // Initialisation basique des cases en mode non visible et valeur 0 //
        {
            jeu[i].visible=0;
            jeu[i].val='0';
        }    
    for(int i = 0 ; i<bombe ; i++) // Installation des bombes la ou il n'y en a pas déjà une //
    {
        at = rand() % (sizeX*sizeY);
        if(jeu[at].val!='*')
            {
               jeu[at].val='*';
            }
            else i--;
        }
    int id = 0;
    for (int i = 0 ; i < sizeX*sizeY ; i++) // Comptage du nombre de bombe autour de la case (Equivaleur de votre GetPosAdj) //
    {
        if (jeu[id].val == '0') // Comprendre : si pas une bombe //
        {                    
            if ((id) % sizeX != sizeX-1) // Comprendre : si pas de dépacement a droite du tableau //
            {
                if (jeu[id+1].val=='*') jeu[id].val += 1;
                if (jeu[id-sizeX+1].val=='*') jeu[id].val += 1;
                if (jeu[id+sizeX+1].val=='*') jeu[id].val += 1;
            }
            if (id % sizeX != 0) // Comprendre : si pas de dépacement a gauche du tableau //
            {
                if (jeu[id-sizeX-1].val=='*') jeu[id].val += 1;
                if (jeu[id-1].val=='*') jeu[id].val += 1;
                if (jeu[id+sizeX-1].val=='*') jeu[id].val += 1;                    
            }
            if (jeu[id-sizeX].val=='*') jeu[id].val += 1; // Les bombes en dessous et au dessus de la case seront forcément //
            if (jeu[id+sizeX].val=='*') jeu[id].val += 1; // prises en compte si elles existent car pas de dépacement possibles //
        }
        if (jeu[id].val == '0') // Transformation des 0 restants en '.' pour une meilleur lisibilité //
        {
            jeu[id].val = '.';
        }
        id++;
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////

////// Affichage des instructions de jeu, attente de réponse de l'utilisateur ////////
void rdyCheck(void)
{
    ttyraw(0);
    unsigned char ch[4];
    int go = 0;
    printf("Valeurs acceptées, lancement imminent\n\rDéplacez vous avec les FLECHE\n\rDécouvrez les cases avec SPACE\n\rMarquez les cases avec m\n\rAppuyez sur SPACE pour commencer\n\r");
    while (go != 1)
    {
        read(STDIN_FILENO,ch,sizeof(ch));
        if (ch[0] == 32)
        {
            go = 1;
        }  
    }
    ttyreset(0);
}

//////////////////////////////////////////////////////////////////////////////////////

//////// Boucle de jeu comprenant beaucoup de fonctions expliquées plus bas //////////
int boucleJeu(CASE* jeu,int sizeX,int sizeY,int bombe,int posx,int posy)
{
    int alive = 0;
    ttyraw(0);
    while(!alive)
        {        

                    system("clear"); // J'utilise un system("clear") et pas un CLRSCR car le rendu est plus propre à mon gout //
                    showTerrain(jeu, sizeX, sizeY); //Expliquer plus bas //
                    showCursor(posx,posy); // Expliquer plus bas //
                    int absPos = ((sizeX)*(posy/3-1)+posx/5-1);// Calcul de la position absolue du curseur par rapport au tableau (calcul un peu bizar du a la facon dont j'affiche mon tableau) //
                    char which = pression(jeu, absPos, sizeX, sizeY); // La fonction pression() est bloquante, on attends une action de l'utilisateur //
                    if (which == 'S') // Grand if a remplacer par un switch() je viens de m'en apercevoir oups //
                    {
                        caseSpace(jeu, absPos, sizeX, sizeY, posx, posy); // Fonction expliquer plus bas
                        if (winCondition(jeu, sizeX, sizeY, bombe))
                        {
                            alive = winCondition(jeu, sizeX, sizeY, bombe); // Verification des conditions de victoire
                        }
                        if (looseCondition(jeu, absPos))
                        {
                            alive = looseCondition(jeu, absPos); // Verification des conditions de défaites
                        }
                    }
                    else if (which == 'H') // Si flêche du haut appuyé le curseur monte  //
                    {
                        if(posy > 4)
                        {            
                            posy -=3;
                        }
                    }
                    else if (which == 'B') // Flêche du bas //
                    {
                        if(posy < sizeY*3)
                        {
                            posy +=3;
                        }
                    }
                    else if (which == 'G') // Flêche de gauche //
                    {
                        if(posx > 5)
                        {
                            posx -=5;
                        }
                    }
                    else if (which == 'D') // Flêche de droite //
                    {
                        if(posx < sizeX*5)
                        {                
                            posx +=5;
                        }
                    }
                    else if (which == 'm') // En cas d'appuie sur la lettre m //
                    {
                        casem(jeu, absPos); // Marquage de la case sous quelques conditions expliquées plus bas //
                    }                
        }
    if(ttyreset(0))printf("TTYRESET FAILED\n\r"); // Verification de bon fonctionnement du ttyreset() parceque si il marche pas ça m'énerve //
    return alive;
}

//////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////// Affichage du terrain /////////////////////////////////
void showTerrain(CASE* jeu, int sizeX, int sizeY)
{
    printf("\r\n\n\n");
    int ind = 0;
    for(int i = 0; i<sizeY ; i++) // for() gérant les ligne //
    {
        for(int j = 0; j<sizeX ; j++) // for() gérant les colonnes //
        {
            printf("    ");
            if (jeu[ind].visible==1) // Si le caractère est visible on affiche sa valeur avec une couleur adéquate //
            {
                if(jeu[ind].val != '.' && jeu[ind].val != '*')
                {
                    if (jeu[ind].val <= '2')
                    {
                        FGCOLOR(GREEN);
                    }
                    else if (jeu[ind].val <='4')
                    {
                        FGCOLOR(CYAN);
                    }
                    else if (jeu[ind].val <='6')
                    {
                       FGCOLOR(YELLOW);
                    }
                    else FGCOLOR(RED);
                }
                else if (jeu[ind].val == '*') // Pas très utile sauf en fin de partie quand on affiche tout le tableau //
                {
                    FGCOLOR(RED);
                }
            printf("%c",jeu[ind].val);
            RESET;
            }
            else if (jeu[ind].visible==2) // Si le caractère est marqué on affiche un F //
            {
                FGCOLOR(BLUE);
                printf("F");
                RESET;
            }
            else printf("#"); // sinon (si pas visible) on affiche un simple # //
            ind ++; // Caractère suivant //
        }
        printf("           ");
        UNDERLINE;
        printf("|%d|\n\r\n\n",i+1); // Affichage du numéro de ligne a droite //
        RESET;
    }
}

//////////////////////////////////////////////////////////////////////////////////////

///////////////// Fonction de pression appelé a chaque boucle ////////////////////////
char pression(CASE* jeu, int absPos, int sizeX, int sizeY)
{
    unsigned char ch[4];
    int nblu = 0;
    nblu = read(STDIN_FILENO,ch,sizeof(ch)); // read() est bloquant, le programme attends impérativement une réponse de l'utilisateur //
    if (ch[0] == SPACE) // Les SPACE, HAUT, BAS (...) sont référencés dans demineur.h
	{
		return('S');
	}
    if(ch[0] == m)
    {
        return('m');   
    }        
    if(nblu >= 3) // Si nblu est plus grand ou égal a 3 alors on est en mode echaptement (Flèche directionnel et quelques autres) //
    {
        switch (ch[2]) 
        {
            case HAUT:
                return ('H');
                break;
            case BAS:
                return ('B');
                break;
            case DROITE:
                return ('D');
                break;
            case GAUCHE:
                return ('G');
                break;
            default:
                break;
        }
    }
    return ('R'); // Si une autre touche on return un caractère basique //
    
}

//////////////////////////////////////////////////////////////////////////////////////

//////////// Fonction qui réagie a l'appui de la touche espace ///////////////////////
int caseSpace(CASE* jeu, int absPos, int sizeX,int sizeY, int posx, int posy)
{
 	jeu[absPos].visible=1; // Affichage de la case sur lequel est le curseur //
    showAround(jeu, sizeX, absPos); // Dévoilage des cases autour (explication plus bas) // 
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////

///////////// Fonction qui réagie a l'appuie de la touche M //////////////////////////
int casem(CASE* jeu, int absPos)
{
    if (jeu[absPos].visible == 2) // Si le caractère était déja marquer on le démarque //
    {
        jeu[absPos].visible=0;
    }
    else if (jeu[absPos].visible==0)jeu[absPos].visible=2; // Si le caractère est bien invisible on le marque //
    else;

    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////

/////////////////////// Affichage du curseur à sa position ///////////////////////////
void showCursor (int posx, int posy)
{
    CUP(posx,posy);
    FGCOLOR(BLUE);
    printf("X\r\n");
    RESET;
}

///////////////////////////////////////////////////////////////////////////////////////

//Fonction récursive, volontairement assez complexe a première vue mais assez logique//
int showAround(CASE* jeu, int sizeX, int absPos)
{
    if (jeu[absPos].val=='.') // Si le caractère dévoilé est un '.'
            {
                if ((absPos) % sizeX != sizeX-1) // Comme pour la fonction qui compte le nombre bombe autour, ici on verifie le non-dépacement a droite //
                {
                    if (jeu[absPos+1].val != '*' && jeu[absPos+1].visible != 1) // On vérifie si le caractère adjacent n'est pas une bombe même si impossible si le caractère est un '.' //
                    {                                                           // Ce qui est intéressant c'est la véfication de l'état visible de la case, sans cette vérification la fonction récursive rentrerait dans une boucle infini //
                        jeu[absPos+1].visible = 1;                              // Le caractère adjacent est désormais visible et nous permets de ne pas rester bloquer dans la fonction //
                        if (jeu[absPos+1].val == '.')                           // Si le caractère découvert est lui aussi un '.' alors on rappel la fonction //
                        {
                            showAround(jeu, sizeX, absPos+1);                   // Appel de la fonction avec la nouvelle position de la case //
                        }
                    }
                    if (jeu[absPos-sizeX+1].val != '*' && jeu[absPos-sizeX+1].visible != 1) // Même méthode qu'au dessus avec la prochaine case adjacente cette fois-ci //
                    {
                        jeu[absPos-sizeX+1].visible = 1;
                        if (jeu[absPos-sizeX+1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos-sizeX+1);
                        }
                    }
                    if (jeu[absPos+sizeX+1].val != '*' && jeu[absPos+sizeX+1].visible != 1)
                    {
                        jeu[absPos+sizeX+1].visible = 1;
                        if (jeu[absPos+sizeX+1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos+sizeX+1);
                        }
                    }
                }
                if (absPos % sizeX != 0) // Comme pour le if() précédent on vérifie cette fois ci le non-dépacement a gauche //
                {
                    if (jeu[absPos-1].val != '*' && jeu[absPos-1].visible != 1)
                    {
                        jeu[absPos-1].visible = 1;
                        if (jeu[absPos-1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos-1);
                        }
                    }
                    if (jeu[absPos-sizeX-1].val != '*' && jeu[absPos-sizeX-1].visible != 1)
                    {
                        jeu[absPos-sizeX-1].visible = 1;
                        if (jeu[absPos-sizeX-1].val == '.')
                        {  
                            showAround(jeu, sizeX, absPos-sizeX-1);
                        }
                    }
                    if (jeu[absPos+sizeX-1].val != '*' && jeu[absPos+sizeX-1].visible != 1)
                    {
                        jeu[absPos+sizeX-1].visible = 1;
                        if (jeu[absPos+sizeX-1].val == '.')
                        {
                            showAround(jeu, sizeX, absPos+sizeX-1);
                        }
                    }
                }
                 
                if (jeu[absPos+sizeX].val != '*' && jeu[absPos+sizeX].visible != 1) // Comme pour la fonction qui compte le nombre autour, le AbsPos+sizeX et le AbsPos-sizeX sont indépendants des conditions de dépacement //
                {
                    jeu[absPos+sizeX].visible = 1;
                    if (jeu[absPos+sizeX].val == '.')
                    {
                    showAround(jeu, sizeX, absPos+sizeX);
                    }
                }
                if (jeu[absPos-sizeX].val != '*' && jeu[absPos-sizeX].visible != 1)
                {
                    jeu[absPos-sizeX].visible = 1;
                    if (jeu[absPos-sizeX].val == '.')
                    {
                    showAround(jeu, sizeX, absPos-sizeX);
                    }
                }
            }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////

/////////////// Simple vérification des conditions de victoires //////////////////////
int winCondition(CASE* jeu, int sizeX, int sizeY, int bombe)
{
    int check = 0;
    int i;
    for (i = 0 ; i <= sizeX*sizeY ; i++)
    {
        if (jeu[i].visible == 1)
        {
            check += 1; // Compteur du nombre de caractère visible dans le tableau //
        }
    }
    if (check >= sizeX*sizeY-bombe) // Si le nombre de caractère dans le tableau moins le nombre de bombe est = à notre compteur alors on a gagné //
    {
        return 1;
    }
    else return 0;
}

//////////////////////////////////////////////////////////////////////////////////////

//////// Simple vérification de présence, comme la fonction rdyCheck()////////////////
int again (void)
{
    ttyraw(0);
    unsigned char ch[4];
    while (ch[0] != SPACE || ch[0] != ECHAP) // On attends que l'utilisateur appuie soit sur espace soit sur echap //
    {
        read(STDIN_FILENO,ch,sizeof(ch));
        if (ch[0] == SPACE)
        {
            ttyreset(0);
            return 1;
        }
        if (ch[0] == ECHAP)
        {
            ttyreset(0);
            return 0;
        }
    }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////

////////////////// Simple vérification de condition de défaites //////////////////////
int looseCondition(CASE* jeu, int absPos)
{
    if(jeu[absPos].val == '*') // Si le dernier caractère sur lequel l'utilisateur à appuyé est une bombe alors on perd //
    {
        return 2;         
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////

/////////// Fonction qui rend visible tout les caractères en fin de partie ///////////
int clearTerrain(CASE* jeu, int sizeX, int sizeY)
{
    for (int i = 0 ; i <= sizeX*sizeY ; i++)
        {
            jeu[i].visible = 1;
        }
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////////

