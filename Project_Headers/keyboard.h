 /****************************************************************************
 Compañia: Universidad Catolica de Oriente
 Diseñado por: Luis Felipe Echeverri 
 Fecha: 05/10/2012
 Descripcion: En este archivo se crean las macros para una implementacion
              versatil en el uso de los pines para un teclado matricial
              
 Dependencias: DataType.h, Events.h"

 *****************************************************************************
 *
 *                C1    C2    C3   C4
 *
 *       _____________________________________
 *      /                                     \
 *     |   __________________________________  |
 *     |  |                                 |  |
 *     |  |                                 |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F1|  |     | 1 | | 2 | | 3 | | A |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F2|  |     | 4 | | 5 | | 6 | | B |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F3|  |     | 7 | | 8 | | 9 | | C |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |      ___   ___   ___   ___      |  |
 *     |  |     |   | |   | |   | |   |     |  |
 *   F4|  |     | * | | 0 | | # | | D |     |  |
 *     |  |     |___| |___| |___| |___|     |  |
 *     |  |                                 |  |
 *     |  |                                 |  |
 *     |  |_________________________________|  |
 *     |            _______________            |
 *     |           | | | | | | | | |           |
 *     |           |*|*|*|*|*|*|*|*|           |
 *     |           |_|_|_|_|_|_|_|_|           |
 *      \_________/_________________\_________/
 *              /                     \
 *             |  |  |  |  |  |  |  |  |    
 *             |C1|C2|C3|C4|F1|F2|F3|F4|
 *             |__|__|__|__|__|__|__|__|
 * 
 * PTD4/ADP11: C1
 * PTD5: C2
 * PTD6: C3
 * PTD7: C4                 
 * PTG0/KBI0:  F1
 * PTG1/KBI1:  F2
 * PTG2/KBI6:  F3 
 * PTG3/KBI7:  F4
 * PTD4/ADP11: C1
 * PTD5: C2
 * PTD6: C3
 * PTD7: C4
 ***********************************************/
#ifndef _KBI
#define _KBI
#include "DataType.h"
#include "Events.h"
/***********************************************
KEYBOARD Settings
***********************************************/
//#define  WITH_RTC  // descomentar esta linea si se desea trabajar con el RTC
                     // para generar el tiempo de espera del rebote mecanico
                     // si no se elige esta opcion se utilizara un retardo basado
                     // en un --for-- el cual libera al modulo RTC pero bloquea la
                     // CPU mientras transcurre el tiempo del rebote, recuerde que 
                     // se puede variar el tiempo for de acuerdo a la velocidad 
					 // del Busclk
//DATA
#define ROW1D              PTGD_PTGD0
#define ROW2D              PTGD_PTGD1
#define ROW3D              PTGD_PTGD2
#define ROW4D              PTGD_PTGD3

#define COL1D              PTDD_PTDD4
#define COL2D              PTDD_PTDD5
#define COL3D              PTDD_PTDD6
#define COL4D              PTDD_PTDD7

//DATA DIRECTION
#define ROW1DD            PTGDD_PTGDD0
#define ROW2DD            PTGDD_PTGDD1
#define ROW3DD            PTGDD_PTGDD2
#define ROW4DD            PTGDD_PTGDD3

#define COL1DD            PTDDD_PTDDD4
#define COL2DD            PTDDD_PTDDD5
#define COL3DD            PTDDD_PTDDD6
#define COL4DD            PTDDD_PTDDD7

//PULL UP RESISTOR
#define ROW1PE            PTGPE_PTGPE0
#define ROW2PE            PTGPE_PTGPE1
#define ROW3PE            PTGPE_PTGPE2
#define ROW4PE            PTGPE_PTGPE3

#define COL1PE            PTDPE_PTDPE4
#define COL2PE            PTDPE_PTDPE5
#define COL3PE            PTDPE_PTDPE6
#define COL4PE            PTDPE_PTDPE7
 
//KBIPIN

#define ROW1KBIPE         KBIPE_KBIPE0
#define ROW2KBIPE         KBIPE_KBIPE1
#define ROW3KBIPE         KBIPE_KBIPE6
#define ROW4KBIPE         KBIPE_KBIPE7

//KBIEDG
#define ROW1HBIEDG        KBIES_KBEDG0
#define ROW2HBIEDG        KBIES_KBEDG1
#define ROW3HBIEDG        KBIES_KBEDG6
#define ROW4HBIEDG        KBIES_KBEDG7



#define COLOUT()           COL1DD=1; COL2DD=1; COL3DD=1; COL4DD=1
#define COLCERO()          COL1D=0; COL1D=0; COL1D=0; COL1D=0
#define COLIN()            COL1DD=0; COL2DD=0; COL3DD=0; COL4DD=0
#define COLPE()            COL1PE=1; COL2PE=1; COL3PE=1; COL4PE=1

#define ROWOUT()           ROW1DD=1; ROW2DD=1, ROW3DD=1; ROW4DD=1
#define ROWCERO()          ROW1D=0; ROW1D=0; ROW1D=0; ROW1D=0
#define ROWIN()            ROW1DD=0; ROW2DD=0, ROW3DD=0; ROW4DD=0
#define ROWPE()            ROW1PE=1; ROW2PE=1; ROW3PE=1; ROW4PE=1
#define ROWKBIEN()         ROW1KBIPE=1; ROW2KBIPE=1;ROW3KBIPE=1;ROW4KBIPE=1
#define ROWKBIDIS()        ROW1KBIPE=0; ROW2KBIPE=0;ROW3KBIPE=0;ROW4KBIPE=0
#define ROWKBIEDG()        ROW1HBIEDG=0; ROW2HBIEDG=0;ROW3HBIEDG=0;ROW4HBIEDG=0;

void Keyboard_Init(void);
UINT8 keydecoder(void);
#endif
