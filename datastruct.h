#ifndef DATASTRUCT
#define DATASTRUCT
#define NB_CHAR_NOM_THEME 30
#include "stm8s_type.h"

typedef struct {
  char actif;
  char idPlayer;
  char nom[NB_CHAR_NOM_THEME];
  
} THEME;


#define WORD_NOTHERE 0
#define WORD_ENTERING 1
#define WORD_LEAVING 2

#define TRY_LOST 2
#define TRY_WON 1
#define TRY_NOPE 0
typedef struct {
  char idTheme;
  char actif;
  char aJoue;
  char aTrouve;
  char etatMot;
  
} PLAYER;


#endif
