#include "stm8s.h"
#include "stm8s_conf.h"
#ifndef AFFICHEUR
#define AFFICHEUR

extern u8 aff_temp[8];
void clear(void);
void printtab(char tab[]);
void disp(void);
void push_char(u8 c);
void HDLX1(u8* chaine);
void HDLX2(u8* chaine);
#endif
