/*
 *******************************************************************************
 * File:	hx711.с
 *******************************************************************************
 * Created on: Jan 26, 2024
 * Author: Edward
 *******************************************************************************
 */

#include "hx711.h"

void init(HX711 *data, GPIO_TypeDef *Data_GPIO, uint8_t dataPin, GPIO_TypeDef *SCK_GPIO, uint8_t sckPin)
{
	data->Data_GPIO = Data_GPIO;
	data->dataPin = dataPin;
	data->SCK_GPIO = SCK_GPIO;
	data->sckPin = sckPin;

	HAL_GPIO_WritePin(data->SCK_GPIO, data->sckPin, GPIO_PIN_RESET);
	HAL_Delay(50);
}

int32_t hx711_value(HX711 *data, uint8_t gain)
{
	data->gain = gain;
	int32_t count = 0;
	uint8_t dout;
	int32_t fill;

	while(HAL_GPIO_ReadPin(data->Data_GPIO, data->dataPin));

	HAL_GPIO_WritePin(data->SCK_GPIO, data->sckPin, GPIO_PIN_RESET);

	for(uint8_t i = 0; i < 24 ; i++){
		HAL_GPIO_WritePin(data->SCK_GPIO, data->sckPin, GPIO_PIN_SET);
		dout = HAL_GPIO_ReadPin(data->Data_GPIO, data->dataPin);
		count = count << 1;
		if(dout){
			count++;
		}
		HAL_GPIO_WritePin(data->SCK_GPIO, data->sckPin, GPIO_PIN_RESET);
	}

	for (uint8_t i = 0; i < data->gain; i++){
		HAL_GPIO_WritePin(data->SCK_GPIO, data->sckPin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(data->SCK_GPIO, data->sckPin, GPIO_PIN_RESET);
	}

	if (count & 0x800000){
	    fill = 0xff000000;
	}else{
	    fill = 0x00000000;
	}

	return fill + count;
}
