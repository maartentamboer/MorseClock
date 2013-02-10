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

void send(char letter);
void delay(long int Length);
void digitalWrite (int iPin, int iValue);

#endif /* MORSE_H_ */
