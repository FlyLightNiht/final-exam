#include "LPC11xx.h"                    // Device header
#include "LED.h"
uint8_t table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

void delay (void)
{
	uint32_t time=1000;
	while(time--);
}

void LED_Init (void)
{
	LPC_GPIO2->DIR = 0xfff;
}

void Display (uint32_t Num)
{
	if(Num<10)
	{
		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		delay();
		LPC_GPIO2->DATA = 0xfff;
	}
	else if(Num<100)
	{
		LPC_GPIO2->DATA = 0xb00 + table[Num%1000%100/10];
	  delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		delay();
		LPC_GPIO2->DATA = 0xfff;
	}
	else if(Num<1000)
	{
		LPC_GPIO2->DATA = 0xd00 + table[Num%1000/100];
	delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0xb00 + table[Num%1000%100/10];
		delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		delay();
		LPC_GPIO2->DATA = 0xfff;
	}
	else
	{
		LPC_GPIO2->DATA = 0xe00 + table[Num/1000];
		delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0xd00 + table[Num%1000/100];
		delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0xb00 + table[Num%1000%100/10];
		delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		delay();
		LPC_GPIO2->DATA = 0xfff;
	}

}