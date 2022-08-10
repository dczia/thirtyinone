/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define PA00 GPIO(GPIO_PORTA, 0)
#define PA01 GPIO(GPIO_PORTA, 1)
#define PA02 GPIO(GPIO_PORTA, 2)
#define PWM0 GPIO(GPIO_PORTA, 4)
#define PWM1 GPIO(GPIO_PORTA, 5)
#define PA08 GPIO(GPIO_PORTA, 8)
#define PA09 GPIO(GPIO_PORTA, 9)
#define PWM2 GPIO(GPIO_PORTA, 10)
#define BOOTLOAD GPIO(GPIO_PORTA, 15)
#define GPIO0 GPIO(GPIO_PORTA, 18)
#define GPIO1 GPIO(GPIO_PORTA, 19)
#define GPIO2 GPIO(GPIO_PORTA, 20)
#define GPIO3 GPIO(GPIO_PORTA, 21)
#define PB08 GPIO(GPIO_PORTB, 8)
#define PB09 GPIO(GPIO_PORTB, 9)

#endif // ATMEL_START_PINS_H_INCLUDED
