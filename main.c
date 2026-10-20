/*
 * Lock_System.c
 *
 * Created: 10/20/2026 5:12:19 AM
 * Author : AYMAN KHALED
 */ 



#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "interrupt_vector.h"

#include "DIO_interface.h"
#include "TIMER1_interface.h"

#include "SERVO_MOTOR_interface.h"
#include "KEYPAD_interface.h"
#include "LCD_interface.h"

#define  F_CPU 16000000UL
#include <util/delay.h>

#define GREEN_LED_PORT		DIO_PORTD
#define GREEN_LED_PIN		DIO_PIN0

#define RED_LED_PORT		DIO_PORTD
#define RED_LED_PIN			DIO_PIN1

#define BUZZER_PORT			DIO_PORTD
#define BUZZER_PIN			DIO_PIN2



int main(void)
{
	LCD_voidInit();
	KEYPAD_voidInit();
	SERVOMOTOR_voidInit();
	
	DIO_voidSetPinDir(GREEN_LED_PORT,GREEN_LED_PIN,OUTPUT);
	DIO_voidSetPinDir(RED_LED_PORT,RED_LED_PIN,OUTPUT);
	DIO_voidSetPinDir(BUZZER_PORT,BUZZER_PIN,OUTPUT);
	DIO_voidSetPinVal(BUZZER_PORT,BUZZER_PIN,HIGH);
	
	
	
	
	
	u8 PASSWORD_arr[4]={'1' , '2' , '3' , '4' };
	u8 entry_pass_arr[4];
	u8 check=2;
	
	u8 key;
	
	
	while (1)
	{
		
		for(u8 loop=0 ;loop<3 ;loop++)
		{
			
			if (check==0)
			{
				break;
			}
			
			
			for (u8 i=0 ;i<4 ; )
			{
				key=KEYPAD_u8GetKey();
				
				if (key != 0xff)
				{
					entry_pass_arr[i]=key;
					LCD_voidSendData('*');
					i++;
				}
				
			}
			
			for (u8 j=0 ;j<4 ;j++)
			{
				if (PASSWORD_arr[j]==entry_pass_arr[j])
				{
					check=0;
					continue;
				}
				else
				{
					if (loop==2)
					{
						check=1;
						continue;
					}
					
					LCD_voidClearData();
					LCD_voidGotoxy(0,0);
					LCD_voidSendString("wrong password");
					LCD_voidGotoxy(0,1);
					LCD_voidSendString("please try again");
					check=1;
					
					for(u8 STOP=0 ;STOP<3;STOP++)
					{
						DIO_voidSetPinVal(GREEN_LED_PORT,GREEN_LED_PIN,LOW);
						DIO_voidSetPinVal(RED_LED_PORT,RED_LED_PIN,HIGH);
						DIO_voidSetPinVal(BUZZER_PORT,BUZZER_PIN,LOW);
						_delay_ms(500);
						DIO_voidSetPinVal(RED_LED_PORT,RED_LED_PIN,LOW);
						DIO_voidSetPinVal(BUZZER_PORT,BUZZER_PIN,HIGH);
						_delay_ms(500);
						
					}
					
					LCD_voidClearData();
					break;
				}
			}
		}
		
		if (check==0)
		{
			LCD_voidClearData();
			LCD_voidGotoxy(5,0);
			LCD_voidSendString("OPENED");
			DIO_voidSetPinVal(GREEN_LED_PORT,GREEN_LED_PIN,HIGH);
			SERVOMOTOR_voidSetAngleWithFreq(50,90,1000,2000);
			
			
			while(KEYPAD_u8GetKey() != '#');               //as the door is lock again
			LCD_voidClearData();
			DIO_voidSetPinVal(GREEN_LED_PORT,GREEN_LED_PIN,LOW);
			SERVOMOTOR_voidSetAngleWithFreq(50,0,1000,2000);
			check=2;
			
		}
		else
		{
			LCD_voidClearData();
			LCD_voidSendString("system is locked");
			DIO_voidSetPinVal(DIO_PORTD,DIO_PIN0,LOW);
			DIO_voidSetPinVal(DIO_PORTD,DIO_PIN1,HIGH);
			DIO_voidSetPinVal(DIO_PORTD,DIO_PIN2,LOW);
			while(1);
		}
		
		
		
	}

	
}
