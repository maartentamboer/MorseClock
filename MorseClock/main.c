#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "utils/ustdlib.h"
#include <stdio.h>
int PinData=2;

#define LED_RED_PIN		GPIO_PIN_1
#define LED_GREEN_PIN	GPIO_PIN_3
#define LED_BLUE_PIN	GPIO_PIN_2

#define RED 			LED_RED_PIN
#define GREEN 			LED_GREEN_PIN
#define BLUE			LED_BLUE_PIN
#define YELLOW			LED_RED_PIN + LED_GREEN_PIN
#define PURPLE			LED_RED_PIN + LED_BLUE_PIN
#define LIGHTBLUE		LED_GREEN_PIN + LED_BLUE_PIN
#define WHITE			LED_RED_PIN + LED_GREEN_PIN + LED_BLUE_PIN
#define	OFF				0

#define OUTLINE 4
#define HIGH BLUE
#define LOW  0x00
#define DOTLENGTH 2000000

char message[] = "1 2 3 4 5 6 7 8 9 0 .";
char message2[] = "Maarten en Sjoerd .";
void digitalWrite (int iPin, int iValue)
{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, iValue);
}

void delay(long int Length)
{
	SysCtlDelay(Length);
}



void dot() {
    // Make a dot signal
    digitalWrite(OUTLINE, RED);
    delay(DOTLENGTH);
    digitalWrite(OUTLINE, LOW);
    delay(DOTLENGTH);
}

void dash() {
    // Make a dash signal
    digitalWrite(OUTLINE, BLUE);
    delay(3*DOTLENGTH);
    digitalWrite(OUTLINE, LOW);
    delay(DOTLENGTH);
}

void letterBreak() {
    // The break between letters is 3x(dot length).
    // One dot length comes automatically at the end of
    // the previous dot or dash, so 2 more are needed.
    delay(2*DOTLENGTH);
}

void wordBreak() {
    // The break between words is 4x(dot length).
    // Three come for free since a letter just ended,
    // so 4 more are needed.
    delay(4*DOTLENGTH);
}

void send(char letter) {
    // Sends the given letter to the output
    switch (letter) {
        case 'A':
        case 'a': dot(); dash(); break;
        case 'B':
        case 'b': dash(); dot(); dot(); dot(); break;
        case 'C':
        case 'c': dash(); dot(); dash(); dot(); break;
        case 'D':
        case 'd': dash(); dot(); dot(); break;
        case 'E':
        case 'e': dot(); break;
        case 'F':
        case 'f': dot(); dot(); dash(); dot(); break;
        case 'G':
        case 'g': dash(); dash(); dot(); break;
        case 'H':
        case 'h': dot(); dot(); dot(); dot(); break;
        case 'I':
        case 'i': dot(); dot(); break;
        case 'J':
        case 'j': dot(); dash(); dash(); dash(); break;
        case 'K':
        case 'k': dash(); dot(); dash(); break;
        case 'L':
        case 'l': dot(); dash(); dot(); dot(); break;
        case 'M':
        case 'm': dash(); dash(); break;
        case 'N':
        case 'n': dash(); dot(); break;
        case 'O':
        case 'o': dash(); dash(); dash(); break;
        case 'P':
        case 'p': dot(); dash(); dash(); dot(); break;
        case 'Q':
        case 'q': dash(); dash(); dot(); dash(); break;
        case 'R':
        case 'r': dot(); dash(); dot(); break;
        case 'S':
        case 's': dot(); dot(); dot(); break;
        case 'T':
        case 't': dash(); break;
        case 'U':
        case 'u': dot(); dot(); dash(); break;
        case 'V':
        case 'v': dot(); dot(); dot(); dash(); break;
        case 'W':
        case 'w': dot(); dash(); dash(); break;
        case 'X':
        case 'x': dash(); dot(); dot(); dash(); break;
        case 'Y':
        case 'y': dash(); dot(); dash(); dash(); break;
        case 'Z':
        case 'z': dash(); dash(); dot(); dot(); break;
        case '0': dash(); dash(); dash(); dash(); dash(); break;
        case '1': dot(); dash(); dash(); dash(); dash(); break;
        case '2': dot(); dot(); dash(); dash(); dash(); break;
        case '3': dot(); dot(); dot(); dash(); dash(); break;
        case '4': dot(); dot(); dot(); dot(); dash(); break;
        case '5': dot(); dot(); dot(); dot(); dot(); break;
        case '6': dash(); dot(); dot(); dot(); dot(); break;
        case '7': dash(); dash(); dot(); dot(); dot(); break;
        case '8': dash(); dash(); dash(); dot(); dot(); break;
        case '9': dash(); dash(); dash(); dash(); dot(); break;
        case ',': dash(); dash(); dot(); dot(); dash(); dash(); break;
        case '.': dot(); dash(); dot(); dash(); dot(); dash(); break;
        case '?': dot(); dot(); dash(); dash(); dot(); dot(); break;
        case ';': dash(); dot(); dash(); dot(); dash(); dot(); break;
        case '\'': dash(); dash(); dash(); dot(); dot(); dot(); break;
        case '-': dash(); dot(); dot(); dot(); dot(); dash(); break;
        case '/': dash(); dot(); dot(); dash(); dot(); break;
        case '(':
        case ')': dash(); dot(); dash(); dash(); dot(); dash(); break;
        case '_': dot(); dot(); dash(); dash(); dot(); dash(); break;
        case ' ': wordBreak(); break;
    }
    letterBreak();
}



int main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	int j = 0;
	while(1)
	{

		delay(DOTLENGTH * 10);
		 for (j=0; j<sizeof(message); j++) {
		        send(message[j]); // Send each character in the message.
		    }
		 delay(DOTLENGTH * 10);
		 for (j=0; j<sizeof(message2); j++) {
				send(message2[j]); // Send each character in the message.
			}
	}
}
