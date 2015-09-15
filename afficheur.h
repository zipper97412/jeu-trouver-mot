#include "stm8s.h"
#include "stm8s_conf.h"
#ifndef AFFICHEUR
#define AFFICHEUR
void clear(void);
void printtab(char tab[]);
void disp(void);
void push_char(u8 c);
void HDLX1(u8* chaine);
void HDLX2(u8* chaine);
#endif
