/*
 * interrupt_vector.h
 *
 * Created: 9/10/2024 5:03:30 PM
 *  Author: AMIT
 */ 


#ifndef INTERRUPT_VECTOR_H_
#define INTERRUPT_VECTOR_H_


#define  ISR(__vector_NUM)   void __vector_NUM( void ) __attribute__ ((signal));\
                             void __vector_NUM (void)



#define   INT0_      __vector_1 
#define   INT1_      __vector_2
#define   INT2_      __vector_3
#define  TIM0_OVF    __vector_11
#define  TIMER0_COMP    __vector_10
#define  TIMER1_OVF   __vector_9
#define  TIMER1_COMP_A   __vector_7









#endif /* INTERRUPT_VECTOR_H_ */