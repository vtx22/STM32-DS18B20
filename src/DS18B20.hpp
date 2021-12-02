#pragma once
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include "Timing.hpp"

class DS18B20
{
public:
	DS18B20(TIMER *tim);
	float readTemperature();

private:
	//PIN CONFIG AND SETTING
	void setDataPin(bool on);
	void toggleDataPin();

	void setPinOUTPUT();
	void setPinINPUT();

	//INTERFACING FUNCTIONS
	void startSensor();

	void writeData(uint8_t data);
	uint8_t readData();

	TIMER *_tim;
};
