/*
 * main.c
 *
 *  Created on: Sep 28, 2020
 *      Author: yehia
 */

#include "STD_TYPES.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"
#include "LED_interface.h"
#include "BUZZ_interface.h"

#define DELAY_TIME		500

#define CRITICAL		37
#define MODERATE		34

void Notification(void);

void main()
{
	u16 Local_u16Temperature, Local_u16LM35;

	LED_t Local_LED_tGreenLed = {LED_PORTA, LED_PIN2, LED_u8ACTIVE_HIGH};
	LED_t Local_LED_tYellowLed = {LED_PORTA, LED_PIN3, LED_u8ACTIVE_HIGH};
	LED_t Local_LED_tRedLed = {LED_PORTA, LED_PIN4, LED_u8ACTIVE_HIGH};

	PORT_voidInit();
	ADC_voidInit();

	CLCD_voidInit();

	while(1)
	{
		ADC_u8StartConversionSynch(1, &Local_u16LM35);

		Local_u16Temperature = ((u32)Local_u16LM35 * 5000UL) / 256UL;
		Local_u16Temperature/=10;

		CLCD_voidGotoXY(0,0);
		CLCD_voidSendString("Temperature:");
		CLCD_voidSendNumber(Local_u16Temperature);

		if(Local_u16Temperature>CRITICAL)
		{
			LED_voidLedOff(&Local_LED_tGreenLed);
			LED_voidLedOff(&Local_LED_tYellowLed);
			LED_voidLedOn(&Local_LED_tRedLed);

			BUZZ_voidBuzzerOn();
			_delay_ms(DELAY_TIME);
			BUZZ_voidBuzzerOff();
			_delay_ms(DELAY_TIME);
		}

		else if(Local_u16Temperature>MODERATE)
		{
			LED_voidLedOff(&Local_LED_tGreenLed);
			LED_voidLedOn(&Local_LED_tYellowLed);
			LED_voidLedOff(&Local_LED_tRedLed);
		}

		else
		{
			LED_voidLedOn(&Local_LED_tGreenLed);
			LED_voidLedOff(&Local_LED_tYellowLed);
			LED_voidLedOff(&Local_LED_tRedLed);
		}

	}
}
void Notification(void)
{

}
