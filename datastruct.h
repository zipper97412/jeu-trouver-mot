#ifndef DATASTRUCT
#define DATASTRUCT
#define NB_CHAR_NOM_THEME 30
#include "stm8s_type.h"

typedef struct {
  u8 actif;
  u8 idTheme;
  
} PLAYER;

typedef struct {
  u8 idPlayer;
  char nom[NB_CHAR_NOM_THEME];
  char aJoue;
  char etat_mot;
  
} THEME;


#endif
