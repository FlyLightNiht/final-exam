#include "LPC11xx.h"                    // Device header
#include "ADC.h"
	uint32_t t;
	float k;
	uint32_t res_value;
void ADC_Init (void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO1_11 &=~0xbf;
	LPC_IOCON->PIO1_11 |= 0x01;
	LPC_SYSCON->PDRUNCFG &=~(0x01<<4);           
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);	  
	LPC_ADC->CR = (0x01<<7)|((SystemCoreClock/1000000-1)<<8)|(0<<16)|(0<<17)|(0<<24)|(0<<27);	
}
uint32_t ADC_Get(void)
{
	uint32_t i;
	uint32_t ulADCData;
	uint32_t ulADCBuf;
	ulADCData=0;
    for(i=0;i<10;i++)
     {
			 LPC_ADC->CR |=(1<<24);
			 while((LPC_ADC ->DR[7]&0x80000000)==0);
			 LPC_ADC->CR |=(1<<24);
			 while((LPC_ADC ->DR[7]&0x80000000)==0);
			 ulADCBuf =LPC_ADC->DR[7];
			 ulADCBuf =(ulADCBuf >>6)&0x3ff;
			 ulADCData+=ulADCBuf ;
		 }	
    ulADCData=ulADCData/10;
    ulADCData=(ulADCData*3300)/1024;
		res_value = ((ulADCData*10000)/(3300-ulADCData));
		return res_value;
	 }
  float  mf52(uint32_t ad)
	{
	if((res_value<33970)&&(res_value>18148))  //0-12
	{
			k = 1366;
		  t = (33970-res_value)/k;
	}		
	else if ((res_value<18148)&&(res_value>11490)) //12-22
	{
			k = 774;
		  t = (218148-res_value)/k+10;
	}
	else if ((res_value<11490)&&(res_value>7578)) //22-32
	{
			k = 453.7;
		  t = ((11490-res_value)/k)+20;
	}
	else if ((res_value<7578)&&(res_value>5298))  //32-40
	{
			k = 273.7;
		  t = ((7578-res_value)/k)+30;
	}
	else if ((res_value<5298)&&(res_value>3586))  //40-50
	{
			k = 171.7;
		  t = ((5298-res_value)/k)+40;
	}
	else if ((res_value<3586)&&(res_value>2484))  //50-60
	{   k = 110.2;
		  t = ((3586-res_value)/k)+50;
	}
	return t;
}
float Fahrenheit(uint32_t temp)
{temp=temp*1.8+32;
	return temp;
}