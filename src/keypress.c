#include "LPC11xx.h"                    // Device header
#include "keypress.h"  
#include "LED.h"
uint8_t judge=0;
void PIOINT3_IRQHandler(void)
{    delay();
	if(((LPC_GPIO3 ->MIS)&(1<<1)) == (1<<1))     
	{   
		 if(judge==0)
		 {
			 judge=1;    
		 }
		 else 
			 judge=0;  
  LPC_GPIO3 ->IC =(1<<1);            
	} 

}
void KeyInit(void)
{
	LPC_GPIO3 ->DIR &=~(1<<1);        
	LPC_GPIO3 ->IE |=(1<<1);            
	LPC_GPIO3 ->IS &=~(1<<1);           
	LPC_GPIO3 ->IEV &=~(1<<1);          
	NVIC_EnableIRQ (EINT3_IRQn );        
}