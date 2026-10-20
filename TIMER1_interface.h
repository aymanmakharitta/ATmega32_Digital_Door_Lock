/*
 * TIMER1_interface.h
 *
 * Created: 9/29/2024 9:21:25 PM
 *  Author: AMIT
 */ 


#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_


#define  OV_MODE       0
#define  CTC_MODE      1

#define TIMER1_PRE_LOAD_VALUE 250
#define TIMER1_OVF_VALUE   40

#define TIMER1_CTC_PRELOAD_VALUE  62549
#define TIMER1_OUT_COMP_A      40


#define  TIMER1_NO_PRESCALER         1
#define  TIMER1_8_PRESCALER          2
#define  TIMER1_64_PRESCALER         3
#define  TIMER1_256_PRESCALER        4
#define  TIMER1_1024_PRESCALER       5

#define  TIMER1_PRESCALER    TIMER1_64_PRESCALER

void TIMER1_voidFastPWMICR1(u16 copy_u16Frequency,f32 copy_f32DutyCycle) ; 


void TIMER1_voidSetOcrVal( u16 copy_u16val) ; 


void TIMER1_voidNormalModeInit(u8 copy_u8ModeOfOperation) ; 
void TIMER1_voidStart(void);
void TIMER1_voidStop(void);
void TIMER1_void_voidSetCallBack(void(*ptr)(void),u8 copy_u8ModeOfOperation);


void TIMER1_voidRest(void) ; 

u16 TIMER1_u16ReadVal() ; 

 



#endif /* TIMER1_INTERFACE_H_ */