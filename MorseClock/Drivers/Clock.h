/*
 * Clock.h
 *
 *  Created on: 10 feb. 2013
 *      Author: Administrator
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <time.h>



void init_clock(void);
void settime(int hr, int min, int s);
void printtime(void);
void runtime(void);
void RTC_Handler(void);


#endif /* CLOCK_H_ */
