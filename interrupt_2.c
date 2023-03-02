/****************************************************************/
/*   Author             :    Mohamed Gamal				        */
/*	 Date 				:    25 January 2023     				*/
/*	 Version 			:    							    	*/
/*	 Description 		:   external interrupt     1            */
/*							                                	*/
/****************************************************************/


/****************************************************************/
/*********************** STD LIB DIRECTIVES *********************/
/****************************************************************/

#include "STD_Types.h"
#include "Bit_Math.h"


/****************************************************************/
/*********************** Component DIRECTIVES *******************/
/****************************************************************/

#include "interrupt_2.h"
#include "interrupt_2_confg .h"
#include "interrupt_2_private.h" 


/***********************************************************/
/**!comment   :  pointer to function for callback	       */
/***********************************************************/
 volatile pf x;
 
 /***********************************************************/
 /**!comment   :  NULL	                                    */
 /***********************************************************/
 
 #define NULL 0

/****************************************************************/
/*********************** Function Implementation  ***************/
/****************************************************************/


/****************************************************************/
/* Description    :  This function used to initialize EXT0      */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/



void EXT2_voidInit (void)
{
	
	/*  ( if / else if ) condition for Macros */
	#if EXT0_SENSE_MODE == IOC
	SET_BIT(MCUCR , 0);
	CLEAR_BIT(MCUCR , 1);
	
	#elif EXT0_SENSE_MODE == RISING
	SET_BIT(MCUCR , 0);
	SET_BIT(MCUCR , 1);
	
	#elif EXT0_SENSE_MODE == FALLING
	CLEAR_BIT(MCUCR , 0);
	SET_BIT(MCUCR , 1);
	
	#elif EXT0_SENSE_MODE == LOW_LEVEL
	CLEAR_BIT(MCUCR , 0);
	CLEAR_BIT(MCUCR , 1);
	
	#endif
	/* End ( if ) condition for Macros */

	
/** disable EXT2 in initialization function  **/
/** like : void EXT2_voidDisable(); 		  */
	CLEAR_BIT( GICR , 5 );
	SET_BIT(GIFR , 5 ) ;
	
	
}


/****************************************************************/
/* Description    : This function used to Enable EXT2			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT2_voidEnable()
{
	
	SET_BIT( GICR , 5 );
	
}


/****************************************************************/
/* Description    : This function used to Disable EXT2			*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT2_voidDisable()
{
	
	CLEAR_BIT( GICR , 5 );
	
}


/****************************************************************/
/* Description    : This function used to communicate with the	*/
/*					function in App Layer(The Callback function)*/ 
/*						[ Layer Architecture Problem Solved ]	*/
/*																*/
/*					Inputs : Pointer to function that points to	*/
/*							 the first line of the function(ISR)*/
/*					Return : void								*/
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/

void EXT2_voidCallBack(pf addresscpy)
{
	if(addresscpy !=NULL)
	{
		x = addresscpy;
	}
}

void SREG_VoidEnable (void)
{
	SET_BIT(SREG,5);
}
void SREG_VoidDisable (void)
{
	CLEAR_BIT(SREG,5);
}


/****************************************************************/
/* Description    : This function used to Set lach Interrupt	*/
/*									 happens.					*/ 
/*																*/
/*					Inputs : Sense Mode				  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/
void EXT2_voidSetSignalch(u8 SenseCpy)
{
	if (SenseCpy == IOC)
	{
		SET_BIT(MCUCR , 0);
		CLEAR_BIT(MCUCR , 1);
		
	}
	else if (SenseCpy == RISING)
	{
		SET_BIT(MCUCR , 0);
		SET_BIT(MCUCR , 1);
		
	}
	else if (SenseCpy == FALLING)
	{
		CLEAR_BIT(MCUCR , 0);
		SET_BIT(MCUCR , 1);
	}
	
	else if (SenseCpy == LOW_LEVEL)
	{
		CLEAR_BIT(MCUCR , 0);
		CLEAR_BIT(MCUCR , 1);
	}

	
	/** disable EXT0 in initialization function  **/
	/** like : void EXT0_voidDisable(); 		  */
	CLEAR_BIT( GICR , 5 );
	SET_BIT(GIFR , 5 ) ;

	
	
}

/****************************************************************/
/* Description    : This function used to Check if interrupt is */
/*					Executed or Not.							*/ 
/*																*/
/*					Inputs : void					  			*/
/*					Return : flag Status [ LBTY_OK , LBTY_NOK ]	*/
/****************************************************************/
/* Pre_condition  :  this function must be used after Interrupt */
/*     				 initialized 							    */
/****************************************************************/
/*
flagStatus EXT0_enuIsExecuted( void )
{
	flagStatus ErrorStatus ;
	
	if( (GET_BIT(GIFR, 6)) == 1 )
	{
		
		ErrorStatus = LBTY_NOK ;
	}
	else if ( (GET_BIT(GIFR, 6)) == 0 )
	{
		
		ErrorStatus = LBTY_OK ;
	}
	
	return ErrorStatus ;
}
*/

/****************************************************************/
/* Description    : This function for interrupt  */
/*												*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : void	*/
/****************************************************************/
/* Pre_condition  :   */
/*     				 							    */
/****************************************************************/

void __vector_3(void)
{
	x();
	
}

/***********************************************************************************************/
/************************************* END OF PROGRAM ******************************************/
/***********************************************************************************************/