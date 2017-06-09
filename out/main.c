#include "LPC11xx.h"                    // Device header
#include "keypress.h"
#include "ADC.h"
#include "LED.h"
#include "UART.h"
#include <stdio.h>
#include <string.h>
extern volatile uint8_t UART_Flag;
extern uint8_t chance;
char AD_Data_Buff[20];

int main()
{ uint32_t i;
	extern uint8_t judge;
	float temp;
	UART_IRQ_Init(9600);
	ADC_Init ();
	KeyInit();
  LED_Init ();
	while(1)
	{
  temp=mf52(ADC_Get());
		
	if(judge==0) 
	for(i=0;i<1000;i++)
	 Display( Fahrenheit(temp));
	if(judge==1)
  for(i=0;i<1000;i++)
   	Display((int)temp);
}
	if(UART_Flag==1){
		if(chance==1)
			sprintf (AD_Data_Buff,"TEMP:%4.2f  ÉãÊÏ¶È\r\n",temp);
		else 
			sprintf (AD_Data_Buff,"TEMP:%4.2f  »ªÊÏ¶È\r\n",temp);
		UART_SendStr(AD_Data_Buff);
		UART_Flag=0;
	}

	}