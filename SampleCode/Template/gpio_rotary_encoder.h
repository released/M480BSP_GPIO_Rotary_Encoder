/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "NuMicro.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

#ifndef boolean
typedef unsigned char boolean;
#endif

typedef struct
{
    boolean val;
    unsigned char seq;
    unsigned int count;
    boolean flag;
} ROTARY_ENCODER_T;


/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/
void set_Encoder_direction(unsigned char dir);
unsigned char get_Encoder_direction(void);

void Rotary_Encoder_polling(void);
void GPIO_Rotary_Encoder_Init(void);

