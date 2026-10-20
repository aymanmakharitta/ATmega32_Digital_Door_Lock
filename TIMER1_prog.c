/*
 * TIMER1_prog.c
 *
 * Created: 9/29/2024 9:21:58 PM
 *  Author: AMIT
 */ 
#include "BIT_MATH.h" 
#include "STD_TYPE.h"
#include "TIMER1_interface.h"
#include "TIMER1_reg.h"


static void(*PRV_pFunctionCallBackOVF)(void) = NULL;
static void(*PRV_pFunctionCallBackCTCA)(void) = NULL;

void TIMER1_voidFastPWMICR1(u16 copy_u16Frequency,f32 copy_f32DutyCycle) 
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
		
	/*set OCR value: duty cycle*/
	/*
	This is the width of the high part
	the compare value :
	 F_timer=F_CPU/prescaler=16000000/64=250000HZ
	 t_tick=1/F_timer=1/250000=4 micro_second
	 if i want the high part =1ms then:number of count =1ms/4MS=250
	 then 
	 OCR1_REG =250-1=249
	*/
	
	/*At this function, I give it the duty cycle as 00% like 50, 70 or 20 etc */
		OCR1A_REG=((copy_f32DutyCycle * (ICR1_REG + 1 ))/100.00) - 1;	 
		
	
}

/*
void TIMER1_voidSetOcrVal( u16 copy_u16val){
	
	OCR1B_REG=copy_u16val ; 
}
*/


void TIMER1_voidNormalModeInit(u8 copy_u8ModeOfOperation) {
	
	switch(copy_u8ModeOfOperation)
	{
		case OV_MODE:
		 /* select mode : normal mode */
		 CLR_BIT(TCCR1A_REG,0) ;
		 CLR_BIT(TCCR1A_REG,1) ;
		 CLR_BIT(TCCR1B_REG,3) ;
		 CLR_BIT(TCCR1B_REG,4) ;
		 
		 /*init the timer with pre load value*/
		 TCNT1_REG = TIMER1_PRE_LOAD_VALUE ;
		 
		 /* enable  overflow interrupt */
		 SET_BIT(TIMSK_REG,2);
		 
		break;
		
		/*›Ì «· OV MODE «‰« »Õÿ ›Ì TCNT1_REG  «·ﬁ”„Â «··Ì «‰« Â»œ√ ⁄œ „‰Â« ·Õœ „ «Ê’· · «· OVER FLOW */
		/*›Ì «· CTC MODE «‰« »Õÿ ›Ì «· OCR1A «·ﬁÌ„Â «··Ì Â‰ÂÌÌÌ ⁄‰œÂ«« «·⁄œ*/
		
		
		case CTC_MODE:
		 /* select mode : ctc mode */
		 CLR_BIT(TCCR1A_REG,0) ;
		 CLR_BIT(TCCR1A_REG,1) ;
		 SET_BIT(TCCR1B_REG,3) ;
		 CLR_BIT(TCCR1B_REG,4) ;
		 
		 /*init the timer with pre load value*/
		 OCR1A_REG=TIMER1_CTC_PRELOAD_VALUE;
		 
		 /* enable  overflow interrupt */
		 SET_BIT(TIMSK_REG,4);
		 
		 break;
	}
	

}

void TIMER1_voidStart(void)
{
	/*select prescaler 64*/
	SET_BIT(TCCR1B_REG,0);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,2);
	
}
void TIMER1_voidStop(void)
{
	CLR_BIT(TCCR1B_REG,0);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,2);
	
}
/*
void TIMER1_voidRest(void){
	
	
	TCNT1_REG=0x0000 ; 
	
}

u16 TIMER1_u16ReadVal(){
	
	
	return TCNT1_REG ; 
}
*/

void TIMER1_void_voidSetCallBack(void(*ptr)(void),u8 copy_u8ModeOfOperation)
{
	switch(copy_u8ModeOfOperation)
	{
		case OV_MODE:
		PRV_pFunctionCallBackOVF=ptr;
		break;
		
		case CTC_MODE:
		PRV_pFunctionCallBackCTCA=ptr;
		break;
	}
}



/*ISR TIMER1 OVF*/
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	static u16 local_u16counter =0;
	local_u16counter++;
	if (local_u16counter==TIMER1_OVF_VALUE)
	{
		local_u16counter=0;
		if(PRV_pFunctionCallBackOVF != NULL)
		{
			PRV_pFunctionCallBackOVF();
		}
	}
}


/*ISR TIMER1 OUTPUT_COMPARE_A*/
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	static u16 local_u16counter =0;
	local_u16counter++;
	if (TIMER1_OUT_COMP_A == local_u16counter)
	{
		if(PRV_pFunctionCallBackCTCA != NULL)
		{
			PRV_pFunctionCallBackCTCA();
		}
	}
}