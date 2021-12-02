#include "DS18B20.hpp"

DS18B20::DS18B20(TIMER *tim)
{
	_tim = tim;
}

void DS18B20::setDataPin(bool on)
{
	if (on)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

void DS18B20::toggleDataPin()
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
}

void DS18B20::setPinOUTPUT()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void DS18B20::setPinINPUT()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void DS18B20::startSensor()
{
	setPinOUTPUT();
	setDataPin(false);

	_tim->delayUS(480);
	setPinINPUT();
	_tim->delayUS(80);
	HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13));
	_tim->delayUS(400);
}

void DS18B20::writeData(uint8_t data)
{
	setPinOUTPUT(); // set as output

	for (uint8_t i = 0; i < 8; i++)
	{

		if (data & (1 << i)) // if the bit is high
		{
			// write 1

			setPinOUTPUT();	   // set as output
			setDataPin(false); // pull the pin LOW
			_tim->delayUS(1);  // wait for 1 us

			setPinINPUT();	   // set as input
			_tim->delayUS(60); // wait for 60 us
		}
		else // if the bit is low
		{
			// write 0

			setPinOUTPUT();
			setDataPin(false); // pull the pin LOW
			_tim->delayUS(60); // wait for 60 us

			setPinINPUT();
		}
	}
}

uint8_t DS18B20::readData()
{
	uint8_t value = 0;
	setPinINPUT();

	for (uint8_t i = 0; i < 8; i++)
	{
		setPinOUTPUT(); // set as output

		setDataPin(false); // pull the data pin LOW
		_tim->delayUS(2);  // wait for 2 us

		setPinINPUT();							  // set as input
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)) // if the pin is HIGH
		{
			value |= 1 << i; // read = 1
		}
		_tim->delayUS(60); // wait for 60 us
	}
	return value;
}

float DS18B20::readTemperature()
{
	startSensor();
	HAL_Delay(1);
	writeData(0xCC);
	writeData(0x44);
	HAL_Delay(800);
	startSensor();
	writeData(0xCC);
	writeData(0xBE);

	uint8_t temp1 = readData();
	uint8_t temp2 = readData();

	uint16_t tempCom = (temp2 << 8) | temp1;

	return (float)(tempCom / 16.0);
}
