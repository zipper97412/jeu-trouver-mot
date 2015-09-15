#ifndef CORELOOP
#define CORELOOP

#include "datastruct.h"

#define NB_THEME 4
#define MAXPH 42
#define PHLEN 100
#define MAXPL 4
#define MAXTH 4


void parseur(char phrase[MAXPH], char words[NB_THEME][20]);
void decodeur(PLAYER *players, THEME *themes char chaine[], int vitesse);
void roundLoop(PLAYER players[MAXPL], THEME themes[MAXTH], char phrases[MAXPH][PHLEN], int vitesse);



#endif
