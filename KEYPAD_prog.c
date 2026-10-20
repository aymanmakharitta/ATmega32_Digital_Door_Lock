/*
 * KEYPAD_prog.c
 *
 * Created: 9/1/2024 3:40:40 PM
 *  Author: AMIT
 */ 

#include "BIT_MATH.h"
#include "STD_TYPE.h" 
#include "DIO_interface.h"
#include "KEYPAD_config.h"
/*
u8  KEYPAD_DATA[4][4]={{'1','2','3','+'},
	                   {'4','5','6','-'},
					   {'7','8','9','*'},
					   {'c','0','=','/'}} ; 
	*/					   
						   
						   
u8  KEYPAD_DATA[4][3]={{'1','2','3'},
	                   {'4','5','6'},
					   {'7','8','9'},
					   {'*','0','#'}} ; 						   
					     


void KEYPAD_voidInit(){
	
	 u8 COL_ARR[3]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN} ; 
	 u8 ROW_ARR[4]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN} ;
	 u8 loc_in=0 ; 
	 u8 loc_col=0;
	 
	 for (loc_in=0 ;loc_in<4;loc_in++)
	 {
		  /* make row pins as input high to active internal pull up */
		  DIO_voidSetPinDir(KEYPAD_ROW_PORT,ROW_ARR[loc_in],INPUT) ; 
		  DIO_voidSetPinVal(KEYPAD_ROW_PORT,ROW_ARR[loc_in],HIGH)  ; 
	 
	 }
	 for (loc_col=0 ;loc_col<3 ;loc_col++)
	 {
		 
				/* make col pin as output high  */
		 	  DIO_voidSetPinDir(KEYPAD_COL_PORT,COL_ARR[loc_col],OUTPUT) ;
		 	  DIO_voidSetPinVal(KEYPAD_COL_PORT,COL_ARR[loc_col],HIGH)  ;
	 }
		 
	 	 
}

u8  KEYPAD_u8GetKey(){
	
	u8 COL_ARR[3]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN} ;
	u8 ROW_ARR[4]={KEYPAD_ROW0_PIN,KEYPAD_ROW1_PIN,KEYPAD_ROW2_PIN,KEYPAD_ROW3_PIN} ;
	u8 lOC_row_in=0 ;
	u8 lOC_col_in=0 ;
	u8 loc_val=0xff ; 
	for (lOC_col_in=0 ; lOC_col_in<3;lOC_col_in++)
	{
		  /* set current col as low */
		  DIO_voidSetPinVal(KEYPAD_COL_PORT,COL_ARR[lOC_col_in],LOW)  ; 
		  
		  for(lOC_row_in=0 ;lOC_row_in<4;lOC_row_in++){
			  
			  if (DIO_u8ReadPinVal(KEYPAD_ROW_PORT,ROW_ARR[lOC_row_in])==0)
			  {
				  
				  loc_val=KEYPAD_DATA[lOC_row_in][lOC_col_in] ; 
				 
				 while(DIO_u8ReadPinVal(KEYPAD_ROW_PORT,ROW_ARR[lOC_row_in])==0) ; 
					 
					 return loc_val ; 
				  
				  
			  }
			  
			  
			  
		  }
		 /* set current col as low */
		 DIO_voidSetPinVal(KEYPAD_COL_PORT,COL_ARR[lOC_col_in],HIGH)  ;
		
		
		
	}
	
	
	
	
	return loc_val ; 
}