/*
 * ADC_ass4.c
 *
 *  Created on: Jan 6, 2024
 *      Author: Abir Omara
 */


/* Lib layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#define F_CPU   8000000UL

/* MCAL */
#include "DIO_interface.h"
#include "ADC_interface.h"


/* HAL */
#include "lcd_interface.h"


int main ()
{
	u16 Local_u16DigitalValue,Local_u16AnalogValue,Local_OldValue;;

	DIO_voidInit();
	ADC_voidInit();
	LCD_voidInt();

	u8 Hamosha1M[8]=
	{
			0b00001110,
			0b00001110,
			0b00000100,
			0b00000100,
			0b00001110,
			0b00010101,
			0b00000100,
			0b00000100
	};
	u8 Hamosha2M[8]=
	{
			0b00000100,
			0b00000100,
			0b00001010,
			0b00001010,
			0b00001010,
			0b00001010,
			0b00001010,
			0b00000000
	};

	u8 Hamosha1E[8]=
	{
			0b00000000,
			0b00000000,
			0b00010000,
			0b00001011,
			0b11111111,
			0b00001011,
			0b00010000,
			0b00000000
	};
	u8 Hamosha2E[8]=
	{
			0b00000000,
			0b00000000,
			0b00000000,
			0b00011100,
			0b00000011,
			0b00011100,
			0b00000000,
			0b00000000
	};
	while (1){
		ADC_u8GetDigitalValueSynchNonBlocking(ADC_u8_CHANNEL_0,&Local_u16DigitalValue);

		Local_u16AnalogValue=(u16) ((Local_u16DigitalValue*5000UL)/1024);
		if (Local_OldValue != Local_u16AnalogValue)
		{
			LCD_voidClearDisplay();

		}

		if (Local_u16AnalogValue <= 3000)
		{
			//turn off led 1 means light
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("Good");
			LCD_voidWriteSpecialChar(1,&Hamosha1E,1,15);
			LCD_voidWriteSpecialChar(2,&Hamosha2E,1,14);
			LCD_u8GoToXY(2,0);
			LCD_voidWriteString("Evening");
			_delay_ms(1000);

		}
		else if (Local_u16AnalogValue > 3000)
		{
			//turn on led 1 means dark
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("Good");
			LCD_voidWriteSpecialChar(1,&Hamosha1M,1,9);
			LCD_voidWriteSpecialChar(2,&Hamosha2M,2,9);
			LCD_u8GoToXY(2,0);
			LCD_voidWriteString("Morning");
			_delay_ms(1000);
		}
		Local_OldValue= Local_u16AnalogValue;
	}
	return 0;
}
