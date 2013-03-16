/*
 * adc.c
 *
 *  Created on: 16 mrt. 2013
 *      Author: Maarten Tamboer, Sjoerd Willemsen
 *      and https://github.com/sultanqasim/Stellarino
 */
#include "adc.h"
#include "pins.h"
const unsigned long pinMux[][4] = {
		{12, 0, 0, 12},		// PA0
		{12, 0, 0, 12},		// PA1
		{12, 0, 0, 12},		// PA2
		{12, 0, 0, 12},		// PA3
		{12, 0, 0, 12},		// PA4
		{12, 0, 0, 12},		// PA5
		{12, 0, 0, 12},		// PA6
		{12, 0, 0, 12},		// PA7
		{2, TIMER_A, GPIO_PB0_T2CCP0, 12},	// PB0
		{2, TIMER_B, GPIO_PB1_T2CCP1, 12},	// PB1
		{3, TIMER_A, GPIO_PB2_T3CCP0, 12},	// PB2
		{3, TIMER_B, GPIO_PB3_T3CCP1, 12},	// PB3
		{1, TIMER_A, GPIO_PB4_T1CCP0, ADC_CTL_CH10},	// PB4
		{1, TIMER_B, GPIO_PB5_T1CCP1, ADC_CTL_CH11},	// PB5
		{0, TIMER_A, GPIO_PB6_T0CCP0, 12},	// PB6
		{0, TIMER_B, GPIO_PB7_T0CCP1, 12},	// PB7
		{4, TIMER_A, GPIO_PC0_T4CCP0, 12},	// PC0
		{4, TIMER_B, GPIO_PC1_T4CCP1, 12},	// PC1
		{5, TIMER_A, GPIO_PC2_T5CCP0, 12},	// PC2
		{5, TIMER_B, GPIO_PC3_T5CCP1, 12},	// PC3
		{6, TIMER_A, GPIO_PC4_WT0CCP0, 12},	// PC4
		{6, TIMER_B, GPIO_PC5_WT0CCP1, 12},	// PC5
		{7, TIMER_A, GPIO_PC6_WT1CCP0, 12},	// PC6
		{7, TIMER_B, GPIO_PC7_WT1CCP1, 12},	// PC7
		{8, TIMER_A, GPIO_PD0_WT2CCP0, ADC_CTL_CH7},	// PD0
		{8, TIMER_B, GPIO_PD1_WT2CCP1, ADC_CTL_CH6},	// PD1
		{9, TIMER_A, GPIO_PD2_WT3CCP0, ADC_CTL_CH5},	// PD2
		{9, TIMER_B, GPIO_PD3_WT3CCP1, ADC_CTL_CH4},	// PD3
		{12, 0, 0, 12},		// PD4 (WTIMER4 is needed for elapsed time functions)
		{12, 0, 0, 12},		// PD5 (WTIMER4 is needed for elapsed time functions)
		{12, 0, 0, 12},		// PD6 (WTIMER5 A is needed for delay)
		{12, 0, 0, 12},		// PD7 (WTIMER5 B is needed for pulseIn)
		{12, 0, 0, ADC_CTL_CH3},		// PE0
		{12, 0, 0, ADC_CTL_CH2},		// PE1
		{12, 0, 0, ADC_CTL_CH1},		// PE2
		{12, 0, 0, ADC_CTL_CH0},		// PE3
		{12, 0, 0, ADC_CTL_CH9},		// PE4
		{12, 0, 0, ADC_CTL_CH8},		// PE5
		{12, 0, 0, 12},		// PE6
		{12, 0, 0, 12},		// PE7
		{0, TIMER_A, GPIO_PF0_T0CCP0, 12},	// PF0 (shared w/ PB6)
		{0, TIMER_B, GPIO_PF1_T0CCP1, 12},	// PF1 (shared w/ PB7)
		{1, TIMER_A, GPIO_PF2_T1CCP0, 12},	// PF2 (shared w/ PB4)
		{1, TIMER_B, GPIO_PF3_T1CCP1, 12},	// PF3 (shared w/ PB5)
		{2, TIMER_A, GPIO_PF4_T2CCP0, 12},	// PF4 (shared w/ PB0)
		{12, 0, 0, 12},		// PF5
		{12, 0, 0, 12},		// PF6
		{12, 0, 0, 12}		// PF7
};

const unsigned char bit8[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

const unsigned long GPIO[] = {GPIO_PORTA_BASE, GPIO_PORTB_BASE, GPIO_PORTC_BASE,
					  	  	  GPIO_PORTD_BASE, GPIO_PORTE_BASE, GPIO_PORTF_BASE};

const unsigned long SysCtlGPIOs[] = {
		SYSCTL_PERIPH_GPIOA, SYSCTL_PERIPH_GPIOB, SYSCTL_PERIPH_GPIOC,
		SYSCTL_PERIPH_GPIOD, SYSCTL_PERIPH_GPIOE, SYSCTL_PERIPH_GPIOF
};
void initadc(void)
{
	/*SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS);
	ADCSequenceDisable(ADC0_BASE, 1);

	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);*/

	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	pinModeADC(PE1);
	pinModeADC(PE2);
	pinModeADC(PE3);

}

void pinModeADC(unsigned char pin)
{
	if (pin >= PC0 && pin <= PC3) return;

	ROM_SysCtlPeripheralEnable(SysCtlGPIOs[pin/8]);
	ROM_SysCtlPeripheralSleepEnable(SysCtlGPIOs[pin/8]);

	ROM_GPIOPinTypeADC(GPIO[pin/8], bit8[pin%8]);
}

void getcolor(unsigned long *curcolor)
{
	curcolor[0] = analogRead(PE1)*10;
	curcolor[1] = analogRead(PE2)*10;
	curcolor[2] = analogRead(PE3)*10;
}

int gettemp(void)
{
	ADCSequenceDisable(ADC0_BASE, 0);
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_TS);
	ADCSequenceEnable(ADC0_BASE, 0);

	ADCIntClear(ADC0_BASE, 0);
	ADCProcessorTrigger(ADC0_BASE, 0);
	while(!ADCIntStatus(ADC0_BASE, 0, false));
	unsigned long value;
	ADCSequenceDataGet(ADC0_BASE, 0, &value);

	return ((1475 - ((2475 * value)) / 4096)/10-4);
}

int analogRead(unsigned char pin) {
	if (pinMux[pin][3] == 12) return 0;	// Non-ADC pin

	ADCSequenceDisable(ADC0_BASE, 0);
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | pinMux[pin][3]);
	ADCSequenceEnable(ADC0_BASE, 0);

	ADCIntClear(ADC0_BASE, 0);
	ADCProcessorTrigger(ADC0_BASE, 0);
	while(!ADCIntStatus(ADC0_BASE, 0, false));
	unsigned long value;
	ADCSequenceDataGet(ADC0_BASE, 0, &value);

	return value;	// From 0 to 4095
}
