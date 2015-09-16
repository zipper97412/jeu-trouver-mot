/* TIMER 3 */
#ifndef TIMER3_H
#define TIMER3_H

/**
\brief cette fonction permet d'initialiser le timer 3
*/
void t3_init(void);


/**
\brief cette fonction permet de modifier les registres ARR
\param arr la nouvelle valeur � mettre dans les registres
*/
void t3_setARR(u16 arr);


/**
\brief cette fonction permet de modifier la valeur dans le registre du prescalaire
\param pscr la nouvelle valeur a mettre dans le registre
*/
void t3_setPSCR(u8 pscr);


/**
\brief cette fonction permet de lancer le comptage
*/
void t3_start(void);


/**
\brief cette fonction permet d'arreter le comptage et de mettre en condition pour repartir
*/
void t3_reset(void);


/**
\brief cette fonction permet de connaitre le contenu actuel des registres arr
\return la valeur des registres
*/
u16 t3_getTime(void);


/**
\brief cette fonction permet de regarder la valeur de UIF
\return la valeur de UIF
*/
int t3_end(void);
#endif
