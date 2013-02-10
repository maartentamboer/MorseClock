#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "utils/ustdlib.h"
#include "utils/uartstdio.h"

#include "Drivers/Morse.h"
#include "Drivers/Clock.h"

int PinData=2;



char message[] = "1234567890.";
char message2[] = "Maarten en Sjoerd .";




int main(void)
{
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
	int j = 0;

	delay(DOTLENGTH * 10);
	for (j=0; j<sizeof(message); j++)
	{
		send(message[j]); // Send each character in the message.
	}
	digitalWrite(0,YELLOW);
	delay(DOTLENGTH * 10);
	init_clock();

	while(1){
		 SysCtlDelay(2000000);
		 //gettime();
		 runtime();
	}
}
