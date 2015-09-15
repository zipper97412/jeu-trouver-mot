#ifndef DATASTRUCT
#define DATASTRUCT


typedef struct {
  char actif;
  char idPlayer;
  
} THEME;


#define WORD_NOTHERE 0
#define WORD_ENTERING 1
#define WORD_LEAVING 2

#define TRY_LOST 2
#define TRY_WON 1
#define TRY_NOPE 0

#define FOUND_NOT 0
#define FOUND_YES 1

typedef struct {
  char idTheme;
  char actif;
  char aJoue;
  char aTrouve;
  char etatMot;
  
} PLAYER;


#endif
