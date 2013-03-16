/*
 * Clock.c
 *
 *  Created on: 10 feb. 2013
 *      Author: Administrator
 */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/hibernate.h"
#include "utils/uartstdio.h"
#include "driverlib/pin_map.h"

#include <time.h>
#include <stdbool.h>

#include "Clock.h"
#include "Morse.h"
#include "rgb.h"
int i=0;
time_t tt;
bool bChangeEnable = false;
bool bRTCUpdated = false;
bool bTimeSet = false;
int selector = MINUTES;
int iChangeMin = 0;
int iChangeHour = 0;
void init_clock(void)
{
	settime(00,00,00);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);					//Enable the Hibernation module
	HibernateEnableExpClk(SysCtlClockGet());
	HibernateRTCEnable();
	HibernateRTCSet(0);
	HibernateRTCMatch0Set(HibernateRTCGet() + 10);
	HibernateIntEnable(HIBERNATE_INT_RTC_MATCH_0);
	HibernateIntClear(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
					  HIBERNATE_INT_RTC_MATCH_0 |
					  HIBERNATE_INT_RTC_MATCH_1);
	HibernateIntRegister(RTC_Handler);
}

void reinit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);					//Enable the Hibernation module
	HibernateEnableExpClk(SysCtlClockGet());
	HibernateRTCEnable();
	HibernateRTCSet(0);
	HibernateRTCMatch0Set(HibernateRTCGet() + 2);
	HibernateIntEnable(HIBERNATE_INT_RTC_MATCH_0);
	HibernateIntClear(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
					  HIBERNATE_INT_RTC_MATCH_0 |
					  HIBERNATE_INT_RTC_MATCH_1);
	HibernateIntRegister(RTC_Handler);
}

void settime(int hr, int min, int s)
{
	struct tm * timeinfo;
	timeinfo = localtime ( &tt );
	timeinfo->tm_hour = hr;
	timeinfo->tm_min = min;
	timeinfo->tm_sec = s;
	timeinfo->tm_year = 2013-1900;
	timeinfo->tm_mon = 2 - 1;
	timeinfo->tm_mday = 10;
	tt = mktime(timeinfo);
}

void morsetime()
{
	char data[5]={0};
	unsigned long ulWhite[]={0xFF00,0xFF00,0xFF00};
	unsigned long ulPurple[]={0xFF00,0x000,0xFF00};
	struct tm * timeinfo;
   int j =0;

	  timeinfo = localtime (&tt);
	  setcolor(ulWhite);
	  strftime (data,5,"%H",timeinfo);
	  for (j=0; j<sizeof(data); j++)
	  	{
	  		send(data[j]); // Send each character in the message.
	  	}
	  setcolor(ulPurple);
	  strftime (data,5, "%M",timeinfo);
	  for (j=0; j<sizeof(data); j++)
	  	{
	  		send(data[j]); // Send each character in the message.
	  	}
}

void printtime(void)
{
	char * c_time_string;
	c_time_string = ctime(&tt);
	UARTprintf("%s\n",c_time_string);
	SysCtlDelay(1);
}

void gettime(struct tm * timeinfo)
{
	timeinfo = localtime (&tt);
}
void runtime(void)
{
	while(1)
	{
		if(bRTCUpdated == true)
		{
			printtime();
			bRTCUpdated = false;
		}
	}
}

void Changetime(int mode)
{
	switch(mode)
	{
	case ENABLE:
		iChangeMin = 0;
		iChangeHour = 0;
		bChangeEnable = true;
		bTimeSet = false;
		selector = MINUTES;
		break;
	case NEXT:
		if (bChangeEnable == true)
		{
			if (selector == MINUTES)
				selector = HOURS;
			else if (selector == HOURS)
			{
				bChangeEnable = false;
				selector = MINUTES;
				settime(iChangeHour,iChangeMin,00);
				bTimeSet = true;
			}
		}
		break;
	case ADD:
		if (bChangeEnable == true)
		{
			if (selector == MINUTES)
				iChangeMin++;
			else if (selector == HOURS)
				iChangeHour++;
		}
		break;
	default:
		break;
	}
}

bool istimeset(void)
{
	return bTimeSet;
}

void RTC_Handler(void)
{
	unsigned long ulStatus;
	//
	// Get the interrupt status, and clear any pending interrupts.
	//
	ulStatus = HibernateIntStatus(1);
	HibernateIntClear(ulStatus);
	//
	// Process the RTC match 0 interrupt.
	//
	if(ulStatus & HIBERNATE_INT_RTC_MATCH_0)
	{
		unsigned long test = HibernateRTCGet();
		HibernateRTCMatch0Set(HibernateRTCGet() + 2);
		//GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, GREEN_LED);
		++tt;
		++tt;
		if (i==0)
		{
			//digitalWrite(0,RED);
			i++;
		}
		else
		{
			//digitalWrite(0,GREEN);
			i=0;
		}
		bRTCUpdated = true;
	}
}
