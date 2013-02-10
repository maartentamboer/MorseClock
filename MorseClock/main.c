#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "utils/ustdlib.h"
#include "driverlib/hibernate.h"
#include <stdio.h>

#include "Drivers/Morse.h"

int PinData=2;



char message[] = "1 2 3 4 5 6 7 8 9 0 .";
char message2[] = "Maarten en Sjoerd .";




int main(void)
{
	unsigned long ulStatus = 0;
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);					//Enable the Hibernation module
	if(HibernateIsActive())
	{
		//
		// Read the status bits to see what caused the wake.
		//
		ulStatus = HibernateIntStatus(0);

		//
		// Wake was due to the push button.
		//
		if(ulStatus & HIBERNATE_INT_PIN_WAKE)
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x2); 				//Weíre going the use the red LED (2=red=pin1, 4=blue=pin2 and 8=green=pin3)
		}

		//
		// Wake was due to RTC match
		//
		if(ulStatus & HIBERNATE_INT_RTC_MATCH_0)
		{
			//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x2);
		}

	}

	//
	// Hibernation module was not active so this is a cold power-up/reset.
	//
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x4); 	//Weíre going the use the blue LED (2=red=pin1, 4=blue=pin2 and 8=green=pin3)
		HibernateEnableExpClk(SysCtlClockGet());								//Enables the Hibernation module for operation.
		HibernateGPIORetentionEnable();											//Enables GPIO retention after wake from hibernate.
		HibernateRTCSet(0);
		HibernateRTCEnable();
		HibernateWakeSet(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC);				//Configures the wake conditions for the Hibernation module
	}
	int j = 0;

		delay(DOTLENGTH * 10);
		 for (j=0; j<sizeof(message); j++) {
		        send(message[j]); // Send each character in the message.
		    }
		 digitalWrite(0,YELLOW);
		 HibernateRTCMatch0Set(HibernateRTCGet() + 2);
		 HibernateRequest();		//Requests hibernation mode. Clear Hibernation Raw Interrupt Status
		 while(1){}
}
