#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "utils/ustdlib.h"
#include "utils/uartstdio.h"

#include "Drivers/Morse.h"
#include "Drivers/Clock.h"
#include "Drivers/rgb.h"
#include "Drivers/buttons.h"
#include "Drivers/adc.h"
#include "Drivers/pins.h"
int PinData=2;



char message[] = "SOS.";


int main(void)
{
	unsigned char ucDelta = 0;
	unsigned char ucState = 0;
	int countuntilprint=0;
	int j = 0;
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(0x00000001);
	GPIOPinConfigure(0x00000401);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioInit(0);
	UARTprintf("\nMorseClock \n");
	UARTprintf("Sjoerd Willemsen en Maarten Tamboer\n");
	UARTprintf("Version: %s, %s\n\n",__DATE__,__TIME__);
	ButtonsInit();
	RGBInit(0);
	initadc();
	unsigned long ulColors[]={0x1000,0xFF00,0xFF00};
	unsigned long ulRED[]={0xFF00,0x0000,0x0000};
	unsigned long ulGREEN[]={0x0000,0xFF00,0x0000};
	unsigned long ulBLUE[]={0x0000,0x0000,0xFF00};
	RGBSet(ulColors,0.1);
	RGBEnable();

	delay(DOTLENGTH * 10);

	RGBSet(ulColors,0.1);
	init_clock();
	RGBSet(ulRED,1);
	Changetime(ENABLE);
	while(1){
		ucState = ButtonsPoll(&ucDelta, 0);
		if(BUTTON_PRESSED(LEFT_BUTTON, ucState, ucDelta))
		{
			RGBSet(ulGREEN,1);
			SysCtlDelay(900000);
			Changetime(ADD);
			UARTprintf("LEFT_BUTTON pressed\n");
			printtime();
			if(istimeset())
				RGBSet(ulColors,1);
			else
				RGBSet(ulColors,0.1);
		}
		else if(BUTTON_PRESSED(RIGHT_BUTTON, ucState, ucDelta))
		{
			RGBSet(ulRED,1);
			SysCtlDelay(900000);
			Changetime(NEXT);
			UARTprintf("RIGHT_BUTTON pressed\n");
			if(istimeset())
			{
				getcolor(ulColors);
				RGBSet(ulColors,1);
			}
			else
			{
				RGBSet(ulColors,0.1);
			}
			printtime();
		}
		else if(BUTTON_PRESSED(ALL_BUTTONS, ucState, ucDelta))
		{
			RGBSet(ulBLUE,1);
			SysCtlDelay(900000);
			Changetime(ENABLE);
			UARTprintf("ALL_BUTTON pressed\n");
			printtime();
			if(istimeset())
				RGBSet(ulColors,1);
			else
				RGBSet(ulColors,0.1);
		}
		if ((bRTCUpdated == true) && istimeset())
		{
			printtime();
			bRTCUpdated = false;
			int tempvalue = gettemp();
			UARTprintf("Temperature: %d\n", tempvalue);
			if (countuntilprint>29)
			{
				countuntilprint = 0;
				morsetime();
				char data[10]={0};
				usprintf(data,"%d",tempvalue);
				UARTprintf("converted Temp:%s\n",data);
				setcolor(ulGREEN);
				for (j=0; j<sizeof(data); j++)
				{
					send(data[j]); // Send each character in the message.
				}
				RGBSet(ulColors,1);
			}
			else
			{
				countuntilprint++;
			}
		}
	} //End of while(1)
} //End of main
