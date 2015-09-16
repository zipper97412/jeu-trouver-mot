/* Valeurs destinees aux registres de configuration des ports */
#ifndef PORTS
#define PORTS
// Port B pour pilotage des afficheurs
#define PORT_B_DIRECTION 0xFF  // 8 bits en sortie
#define PORT_B_TECHNO_LIGNES 0xFF // 8 sorties en push pull

// Port C pour les 4 boutons-poussoirs et SPI
#define PORT_C_DIRECTION 0x00  //  8 bits en entrée
#define PORT_C_TECHNO_LIGNES 0x00 // 8 lignes en floating input     

// Port D pour UART2, SWIM, led verte, TLI, channels/timers et /BL HDLX
#define PORT_D_DIRECTION 0x19  // lignes 0 et 3 en sortie
#define PORT_D_TECHNO_LIGNES 0x90  //  ligne 0 en open drain ligne 3 en PushPull

// Port E pourI2C, entrées analogiques et /WR HDLX													 // bit 4 push pull

#define PORT_E_DIRECTION 0x28 // lignes 3 et 5 en sortie
#define PORT_E_TECHNO_LIGNES 0x28  // lignes 3 et 5 en PP

// Port G pour A0 et A1 HDLX  et verrouillage dans 74HC165
#define PORT_G_DIRECTION 0x03 // 2 lignes en sortie
#define PORT_G_TECHNO_LIGNES 0x03  // 2 lignes en PP


/* Masques destines aux 2 modules d'affichage HDLX */

#define HDLX_NBL 0x08 // Blanking
#define HDLX_NWR1 0x08 // Impulsion /WR1
#define HDLX_NWR2 0x20 // Impulsion /WR2
#define HDLX_A0 GPIO_PIN_0 //  entree adresse A0
#define HDLX_A1 GPIO_PIN_1 //  entree adresse A1

void init_ports(void);
void Init_Timer2(void);
void Init_Timer4(void);

#endif