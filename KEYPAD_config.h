/*
 * KEYPAD_config.h
 *
 * Created: 9/1/2024 3:40:26 PM
 *  Author: AMIT
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


/* col port */
#define  KEYPAD_COL_PORT   DIO_PORTC 

#define KEYPAD_COL0_PIN    DIO_PIN0
#define KEYPAD_COL1_PIN    DIO_PIN1
#define KEYPAD_COL2_PIN    DIO_PIN2
//#define KEYPAD_COL3_PIN    DIO_PIN3

/* row port */

#define  KEYPAD_ROW_PORT   DIO_PORTC  

#define KEYPAD_ROW0_PIN    DIO_PIN4
#define KEYPAD_ROW1_PIN    DIO_PIN5
#define KEYPAD_ROW2_PIN    DIO_PIN6
#define KEYPAD_ROW3_PIN    DIO_PIN7


#endif /* KEYPAD_CONFIG_H_ */