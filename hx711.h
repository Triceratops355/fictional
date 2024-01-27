/*
 *******************************************************************************
 * File:	hx711.h
 * Brief:	HX711 Library for weight measurement
 *******************************************************************************
 * Created on: Jan 26, 2024
 * Author: Edward
 *******************************************************************************
 * This library provides functions to interface with the HX711 ADC for weight
 *******************************************************************************
 */

#ifndef INC_HX711_H_
#define INC_HX711_H_



#endif /* INC_HX711_H_ */

#include "main.h"

typedef struct hx711{
	GPIO_TypeDef *Data_GPIO; //set GPIOA
	GPIO_TypeDef *SCK_GPIO; //set GPIOA
	uint16_t dataPin;
	uint16_t sckPin;
	uint8_t gain; // channel A: 1 or 3, channel B: 2
}HX711;

//Call this function when you want to switch HX711
void init(HX711 *data, GPIO_TypeDef *Data_GPIO, uint8_t dataPin, GPIO_TypeDef *SCK_GPIO, uint8_t sckPin);
//Set gain for choice channel(A, B) HX711
int32_t hx711_value(HX711 *data, uint8_t gain);
