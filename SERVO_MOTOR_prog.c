/*
 * SERVO_MOTOR_prog.c
 *
 * Created: 10/19/2026 2:41:34 AM
 *  Author: East-Sound
 */ 

#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "DIO_interface.h"
#include "TIMER1_interface.h"
#include "TIMER1_reg.h"


#include "SERVO_MOTOR_config.h"
#include "SERVO_MOTOR_interface.h"





void SERVOMOTOR_voidInit(void)
{
	DIO_voidSetPinDir(SERVO_MOTOR_PORT,SERVO_MOTOR_PIN,OUTPUT);
}




void SERVOMOTOR_voidSetAngleWithFreq(u16 copy_u16Frequency, s16 copy_s16Angle , u16 copy_u16MinControlPulseMicroSec, u16 copy_u16MaxControlPulseMicroSec)
{
		
		/* select mode fast pwm ICR */
			CLR_BIT(TCCR1A_REG,0) ; 
			SET_BIT(TCCR1A_REG,1) ;
			SET_BIT(TCCR1B_REG,3) ; 
			SET_BIT(TCCR1B_REG,4) ;
		/* NON inverting FAST PWM  : OC1A */
			CLR_BIT(TCCR1A_REG,6) ; 
			SET_BIT(TCCR1A_REG,7) ; 
		
		 /*select prescaler 64*/
			 SET_BIT(TCCR1B_REG,0);
			 SET_BIT(TCCR1B_REG,1);
			 CLR_BIT(TCCR1B_REG,2);
		 
		 /* set top value : frequency*/
		 /*
		 F_timer=F_CPU/prescaler=16000000/64=250000HZ
		 t_tick=1/F_timer=1/250000=4 micro_second
		 I Want F=50HZ         THEN   T=20 ms
		 top_value=number_of _tick=20ms/4Ms=5000
		 ICR1_REG=5000-1=4999
		 */		
		 /*At this function, I give it the F in HZ */
			ICR1_REG=((1000000UL / copy_u16Frequency) / 4 ) - 1 ;
			
		/*set OCR value: ANGLE*/
		/*
		 F_timer=F_CPU/prescaler=16000000/64=250000HZ
		 t_tick=1/F_timer=1/250000=4 micro_second
		 I can divide the total angle to step (depending on the range of time between the min and max control pulse) like:
		  if the range is from -90 to 90 
		  and the min control pulse =1ms max control pulse =2ms
		  then the one step eqal= (max_control_pulse - min_control_pulse)/180
		  then if i want to get any angle =angle *one step =( (angle+90)*(max_control_pulse - min_control_pulse)/180 )+ min_control_pulse
		  
		  then now i have the time of my angle then i want the ocr1 value 
		  OCR1_REG= (the_result/4(tick_time))-1
		*/
		
		OCR1A_REG=((copy_u16MinControlPulseMicroSec+((f32)(copy_s16Angle+90)/180)*(copy_u16MaxControlPulseMicroSec-copy_u16MinControlPulseMicroSec))/4)-1;
	
}
