#ifndef TIMER4
#define TIMER4
/**
\brief cette fonction permet d'initialiser le timer 4
*/
void t4_init(void);


/**
\brief cette fonction permet de modifier les registres ARR
\param arr la nouvelle valeur à mettre dans les registres
*/
void t4_setARR(u8 arr);


/**
\brief cette fonction permet de modifier la valeur dans le registre du prescalaire
\param pscr la nouvelle valeur a mettre dans le registre
*/
void t4_setPSCR(u8 pscr);


/**
\brief cette fonction permet de lancer le comptage
*/
void t4_start(void);


/**
\brief cette fonction permet d'arreter le comptage et de mettre en condition pour repartir
*/
void t4_reset(void);

/**
\brief cette fonction permet de connaitre le temps écoulé d'un timer en secondes.
\return le temps écoulé en secondes
*/
u8 t4_elapsedTime(void);


/**
\brief cette fonction permet de connaitre le contenu actuel des registres arr
\return la valeur des registres
*/
u8 t4_getTime(void);

/**
\brief cette fonction permet de regarder la valeur de UIF
\return la valeur de UIF
*/
int t4_end(void);

#endif