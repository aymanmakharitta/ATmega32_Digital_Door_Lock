/*
 * LCD_interface.h
 *
 * Created: 8/27/2024 3:25:10 PM
 *  Author: AMIT
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/* LCD MODE
* YOU can select your lcd mode 
* 1- 4 bit mode 
* 2-8 bit mode 
 */

#define   _4_MODE      0 
#define   _8_MODE      1 

#define  LCD_MODE   _4_MODE





void LCD_voidInit(void) ; 

void LCD_voidSendCommand( u8 copy_u8command) ; 
void LCD_voidSendData   ( u8 copy_u8data) ;

void LCD_voidClearData(void);

void LCD_voidSendString(char*str) ; 

void LCD_voidGotoxy(u8 copy_u8x, u8 copy_u8y) ; 


void LCD_voidDrawData(u8 copy_pattern , u8 *copy_u8data ,u8 copy_u8x, u8 copy_u8y) ; 

void LCD_voidSendNumber(u32 number) ; 
#endif /* LCD_INTERFACE_H_ */