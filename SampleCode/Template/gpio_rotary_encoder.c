/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "NuMicro.h"

#include "gpio_rotary_encoder.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

#define ENC_A                               (PA4)
#define ENC_B                               (PA3)

enum 
{
    GPIO_LOW = 0 ,
    GPIO_HIGH , 
};

enum 
{
    DIR_LEFT = 0 ,
    DIR_RIGHT , 
};

unsigned char DIRECTION = 0;

ROTARY_ENCODER_T PINA;
ROTARY_ENCODER_T PINB;

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

/*
    https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/

*/

/*
    PA4 : A
    PA3 : B

*/

void set_Encoder_direction(unsigned char dir)
{
    DIRECTION = dir;
}

unsigned char get_Encoder_direction(void)
{
    return DIRECTION;
}

void Rotary_Encoder_polling(void)
{
    if (PINA.flag)
    {
        PINA.flag = 0 ;
        printf("LEFT (%d:%4d)\r\n" , get_Encoder_direction() ,PINA.count);
    }
    if (PINB.flag)
    {
        PINB.flag = 0 ;
        printf("RIGHT (%d:%4d)\r\n" , get_Encoder_direction() ,PINB.count);
    }
}

void Rotary_Encoder_pinBcalculate(void)
{ 
    PINB.val = ENC_B;        
    PINB.seq <<= 1;
    PINB.seq |= PINB.val;
    PINB.seq &= 0x0F;
}

void Rotary_Encoder_pinAcalculate(void)
{
    PINA.val = ENC_A;
    PINA.seq <<= 1;
    PINA.seq |= PINA.val;    
    PINA.seq &= 0x0F;
}

void Rotary_Encoder_IRQSensing(void)
{
    //0b00001001 : 0x09
    //0b00000011 : 0x03
    if (PINA.seq == 0x09 && PINB.seq == 0x03) 
    {
        PINA.count++;
        set_Encoder_direction(DIR_LEFT);
        PINA.flag = 1;
    }

    //0b00000011 : 0x03
    //0b00001001 : 0x09
    if (PINA.seq == (0x03) && PINB.seq == 0x09) 
    {
        PINB.count++;
        set_Encoder_direction(DIR_RIGHT);
        PINB.flag = 1;
    }
}

void GPA_IRQHandler(void)
{
    if(GPIO_GET_INT_FLAG(PA, BIT4))
    {
        GPIO_CLR_INT_FLAG(PA, BIT4);
    }
    if(GPIO_GET_INT_FLAG(PA, BIT3))
    {
        GPIO_CLR_INT_FLAG(PA, BIT3);
    }

    Rotary_Encoder_pinAcalculate();
    Rotary_Encoder_pinBcalculate();
    Rotary_Encoder_IRQSensing();
}

void GPIO_Rotary_Encoder_Init(void)
{
	SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA4MFP_Msk)) | (SYS_GPA_MFPL_PA4MFP_GPIO);
	SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA3MFP_Msk)) | (SYS_GPA_MFPL_PA3MFP_GPIO);

	GPIO_SetMode(PA,BIT4,GPIO_MODE_INPUT);
	GPIO_SetMode(PA,BIT3,GPIO_MODE_INPUT);

    GPIO_EnableInt(PA, 4, GPIO_INT_BOTH_EDGE);
    GPIO_EnableInt(PA, 3, GPIO_INT_BOTH_EDGE);
    NVIC_EnableIRQ(GPA_IRQn);

    /* Enable interrupt de-bounce function and select de-bounce sampling cycle time is 1024 clocks of LIRC clock */
    GPIO_SET_DEBOUNCE_TIME(GPIO_DBCTL_DBCLKSRC_HCLK, GPIO_DBCTL_DBCLKSEL_1024);
    GPIO_ENABLE_DEBOUNCE(PA, BIT4 | BIT3);

}

