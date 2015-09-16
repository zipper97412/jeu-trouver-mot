#ifndef DATASTRUCT
#define DATASTRUCT


#define MAXPH 14
#define PHLEN 120
#define MAXPL 3
#define MAXTH 4

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
	char score;
  char penality;
	char idJoueur;
  char foundWords[MAXPH][20];

} PLAYER;


typedef struct {
  char actif;
  char idPlayer;

} THEME;

extern PLAYER tabJoueur[MAXPL];
extern THEME tabTheme[MAXTH];
extern char words[MAXTH][20];

#endif
