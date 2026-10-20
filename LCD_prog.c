/*
 * LCD_prog.c
 *
 * Created: 8/27/2024 3:25:38 PM
 *  Author: AMIT
 */ 
#include "BIT_MATH.h" 
#include "STD_TYPE.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"

#define  F_CPU  16000000UL 
#include <util/delay.h> 



                          
static void LCD_voidSHD( u8 copy_u8data){
	
	/* u8 Loc_arr[4]={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN} ; 
	 u8 loc_in=0 ; 
	 
	 for (loc_in=0 ; loc_in<4;loc_in++)
	 {
		 DIO_voidSetPinVal(LCD_DPORT,Loc_arr[loc_in],GET_BIT(copy_u8data,loc_in)) ; 
	 }*/
	
	DIO_voidSetPinVal(LCD_DPORT,LCD_D4_PIN,GET_BIT(copy_u8data,0));
	DIO_voidSetPinVal(LCD_DPORT,LCD_D5_PIN,GET_BIT(copy_u8data,1));
	DIO_voidSetPinVal(LCD_DPORT,LCD_D6_PIN,GET_BIT(copy_u8data,2));
	DIO_voidSetPinVal(LCD_DPORT,LCD_D7_PIN,GET_BIT(copy_u8data,3));
	
	
}

void LCD_voidSendEnablePulse(void){
		
		/* send enabal pulse */
		DIO_voidSetPinVal(LCD_CPORT,LCD_EN_PIN,HIGH) ;
		_delay_ms(1) ;
		DIO_voidSetPinVal(LCD_CPORT,LCD_EN_PIN,LOW) ;
		
}

void LCD_voidInit(void) {
	
	/*set RS , R/W and enable pin  as output pin*/
		DIO_voidSetPinDir(LCD_CPORT,LCD_RS_PIN,OUTPUT);
		DIO_voidSetPinDir(LCD_CPORT,LCD_RW_PIN,OUTPUT);
		DIO_voidSetPinDir(LCD_CPORT,LCD_EN_PIN,OUTPUT);
		
	/*set data pin as output pin*/
		DIO_voidSetPinDir(LCD_DPORT ,LCD_D4_PIN,OUTPUT);
		DIO_voidSetPinDir(LCD_DPORT ,LCD_D5_PIN,OUTPUT);
		DIO_voidSetPinDir(LCD_DPORT ,LCD_D6_PIN,OUTPUT);
		DIO_voidSetPinDir(LCD_DPORT ,LCD_D7_PIN,OUTPUT);
		
		
		
	         _delay_ms(40) ; 
		/*#if LCD_MODE ==_8_MODE
	  
	    LCD_voidSendCommand(0b00111000) ; 
		#elif LCD_MODE == _4_MODE */
		
		/* set RS as HIGH to send Command */
		DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,LOW) ;

		/*set R/W pin as low to write */
		DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW) ;
		 LCD_voidSHD(0b0010) ; 
		 LCD_voidSendEnablePulse() ; 
		 LCD_voidSHD(0b0010) ;
		 LCD_voidSendEnablePulse() ;
		 LCD_voidSHD(0b1000) ;
		 LCD_voidSendEnablePulse() ;
		
			 _delay_us(45); 
		 /* 2- send display on/off command*/
		 LCD_voidSendCommand(0b00001111) ; 
			 _delay_us(45);
		 /*3- send clr lcd command */	
		 LCD_voidSendCommand(0b00000001) ; 	
			_delay_ms(2);
		/*entry mode set*/
		LCD_voidSendCommand(0b00000110);

}

void LCD_voidSendCommand( u8 copy_u8command) {
	
	     /* set RS pin as low to send command */
		 DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,LOW) ; 
		 /*set R/W pin as low to write */
	    DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW) ; 
		/*#if LCD_MODE ==_8_MODE
			
	    DIO_voidSetPortVal(LCD_DPORT,copy_u8command) ; // 1100 1100 
        LCD_voidSendEnablePulse() ; 
		#elif LCD_MODE==_4_MODE */
		    LCD_voidSHD(copy_u8command >> 4) ; 
            LCD_voidSendEnablePulse() ;
            LCD_voidSHD(copy_u8command) ;
            LCD_voidSendEnablePulse() ;
		
	
}

void LCD_voidSendData   ( u8 copy_u8data) {
	
	
	   /* set RS as HIGH to send DATA */
	   DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,HIGH) ;

	   /*set R/W pin as low to write */
	   DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW) ;

	  /*	#if LCD_MODE ==_8_MODE
	  	
	  	DIO_voidSetPortVal(LCD_DPORT,copy_u8data) ; // 1100 1100
	  	LCD_voidSendEnablePulse() ;
	  	 LCD_MODE==_4_MODE*/
	  	LCD_voidSHD(copy_u8data >> 4) ;
	  	LCD_voidSendEnablePulse() ;
	  	LCD_voidSHD(copy_u8data) ;
	  	LCD_voidSendEnablePulse() ;
	  	
	
}


void LCD_voidSendString(char*str) {
	u8 i= 0; 
	while(str[i] != '\0'){

		LCD_voidSendData(str[i]) ; 
		i++ ; 
	}	
}



void LCD_voidGotoxy(u8 copy_u8x, u8 copy_u8y){
	
	  /* 1- cal address ( ddram) */
	
	  u8  DDRAM_address= copy_u8x+ copy_u8y*0x40 ; 
	  
	  /*SET DDRAM  */
	  
	  SET_BIT(DDRAM_address,7) ; 
	  LCD_voidSendCommand(DDRAM_address) ; 

}

void LCD_voidDrawData(u8 copy_pattern , u8 *copy_u8data ,u8 copy_u8x, u8 copy_u8y) {
	
	    /* 1- cal  CGRAM address */
	
	    u8 CGRAM_address= copy_pattern*8 ; 
		
	   /* SET CGRAM */	
	     CLR_BIT(CGRAM_address,7) ; 
		 SET_BIT(CGRAM_address,6) ; 
		 LCD_voidSendCommand(CGRAM_address) ; 
		
		/* DRAW data */
		
		for (u8 i=0 ; i<8;i++)
		{
			LCD_voidSendData(copy_u8data[i]) ; 
		}
		 
		/* display */
		
		LCD_voidGotoxy(copy_u8x,copy_u8y) ; 
		
		LCD_voidSendData(copy_pattern) ;  
	
}

void LCD_voidSendNumber(u32 number){
	
	s8 i=0;
	u8 array[10] ;
	
	if(number==0){
		
		LCD_voidSendData('0') ;
		return ;
	}
	for(i=0; number!=0 ;i++){
		
		array[i]= number % 10 + 48 ;
		number /= 10 ;
	}
	i-- ;
	while(i >= 0){
		
		LCD_voidSendData(array[i]) ;
		i-- ;
	}
}




void LCD_voidClearData(void){
	
	LCD_voidGotoxy(0,0);
	LCD_voidSendString("                              ");
	LCD_voidGotoxy(0,1);
	LCD_voidSendString("                              ");
	
	LCD_voidGotoxy(0,0);

}
