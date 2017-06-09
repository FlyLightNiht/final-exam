#include "LPC11xx.h"
#include "UART.h"

volatile uint8_t UART_Flag;
uint8_t UART_Data_Buff[10];
uint32_t UART_Data_Num;

void UART_IRQ_Init (uint32_t UART_BPS)
{
	uint16_t DD;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_IOCON->PIO1_6 &=~0x07;
	LPC_IOCON->PIO1_6 |= (1<<0);//R
	LPC_IOCON->PIO1_7 &=~0x07;
	LPC_IOCON->PIO1_7 |= (1<<0);//T
	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
	LPC_SYSCON->UARTCLKDIV = 0x01;
	LPC_UART->LCR = 0x83;
	DD = SystemCoreClock / LPC_SYSCON->UARTCLKDIV / 16 / UART_BPS;
	LPC_UART->DLM = DD / 256;
	LPC_UART->DLL = DD % 256;
	LPC_UART->LCR = 0x03;
	LPC_UART->FCR = 0x87;
	NVIC_EnableIRQ(UART_IRQn);
	NVIC_SetPriority(UART_IRQn , 1);
	LPC_UART->IER = 0x01;
}


void UART_Init(uint32_t UART_BPS)
{
	uint16_t usFdiv;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
  LPC_IOCON->PIO1_6 |= 0x01;
	LPC_IOCON->PIO1_7 |= 0x01;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);
	LPC_SYSCON->UARTCLKDIV = 0x01;
	LPC_UART->LCR = 0x83;
	usFdiv = (SystemCoreClock/LPC_SYSCON->UARTCLKDIV/16)/UART_BPS;
	LPC_UART->DLM = usFdiv / 256;
	LPC_UART->DLL = usFdiv % 256;
	LPC_UART->LCR = 0x03;
	LPC_UART->FCR = 0x07;	
}


void UART_SendByte (uint8_t TData)
{
	LPC_UART->THR = TData;
	while((LPC_UART->LSR & 0x40) == 0);
}



uint8_t UART_GetByte (void)
{
	uint8_t Data;
	while((LPC_UART->LSR&0x01) == 0);
	Data = LPC_UART->RBR;
	return Data;
}



void UART_SendStr (char *puc)
{
	while(1)
	{
		if(*puc == '\0') break;
		UART_SendByte(*puc++);
	}
}
