/*
 * Clock.h
 *
 *  Created on: 10 feb. 2013
 *      Author: Administrator
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <time.h>
#include <stdbool.h>

#define ENABLE 	1
#define NEXT   	2
#define ADD		3

extern time_t tt;

enum selectedit
{
	MINUTES = 0,
	HOURS = 1,
	DONE =2
};

extern bool bRTCUpdated;

void init_clock(void);
void settime(int hr, int min, int s);
void printtime(void);
void runtime(void);
void Changetime(int mode);
void RTC_Handler(void);


#endif /* CLOCK_H_ */
