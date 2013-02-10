/*
 * Morse.h
 *
 *  Created on: 10 feb. 2013
 *      Author: Administrator
 */

#ifndef MORSE_H_
#define MORSE_H_

#define LED_RED_PIN		GPIO_PIN_1
#define LED_GREEN_PIN	GPIO_PIN_3
#define LED_BLUE_PIN	GPIO_PIN_2

#define HIGH			1
#define MIDDLE			0.5
#define	OFF				0

#define OUTLINE 4
#define LOW  0x00
#define DOTLENGTH 2000000

void send(char letter);
void delay(long int Length);
void digitalWrite (int iPin, float iValue);

#endif /* MORSE_H_ */
