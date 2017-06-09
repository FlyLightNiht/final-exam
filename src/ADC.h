#ifndef __ADC_H__
#define __ADC_H__
#include "LPC11xx.h"    
extern void ADC_Init (void);
extern uint32_t ADC_Get(void);	
extern  float mf52(uint32_t ad);
extern float Fahrenheit(uint32_t temp);
#endif