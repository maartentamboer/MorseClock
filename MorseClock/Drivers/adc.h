/*
 * adc.h
 *
 *  Created on: 16 mrt. 2013
 *      Author: Maarten Tamboer, Sjoerd Willemsen
 *      and https://github.com/sultanqasim/Stellarino
 */
#ifndef ADC_H_
#define ADC_H_

#define PART_LM4F120H5QR
#define TARGET_IS_BLIZZARD_RA1
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

void initadc(void);
void pinModeADC(unsigned char pin);
int analogRead(unsigned char pin);
void getcolor(unsigned long *curcolor);
int gettemp(void);

#endif /* ADC_H_ */
