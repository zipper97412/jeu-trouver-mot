#ifndef CORELOOP
#define CORELOOP
#include "datastruct.h"


void decodeur(PLAYER* players, THEME* themes, char* chaine, int vitesse);
extern void parseur(char* chaine, char** words);
extern void roundLoop(PLAYER* players, THEME* themes, const char phrases[MAXPH][PHLEN], int vitesse);
void jouer(PLAYER pJoueur);


#endif
