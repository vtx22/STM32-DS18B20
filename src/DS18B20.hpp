#ifndef DS18B20_HPP
#define DS18B20_HPP

// Use the following flags for compiling the right library, e.g.: -D STM32F1
#if defined(STM32F0)
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_tim.h"
#elif defined(STM32F1)
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#elif defined(STM32F2)
#include "stm32f2xx_hal.h"
#include "stm32f2xx_hal_tim.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_tim.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_tim.h"
#else
#error "Unsupported STM32 microcontroller. Make sure you build with -STM32F1 for example!"
#endif

#include <stdint.h>

class DS18B20
{
public:
	DS18B20(TIM_HandleTypeDef *tim, GPIO_TypeDef *port, uint16_t pin);

	float read_temp_celsius();
	float read_temp_fahrenheit();

private:
	void set_data_pin(bool on);
	void toggle_data_pin();

	void set_pin_output();
	void set_pin_input();

	GPIO_PinState read_data_pin();

	void start_sensor();

	void writeData(uint8_t data);
	uint8_t read_data();

	void delay_us(uint16_t us);

	TIM_HandleTypeDef *_tim;
	GPIO_TypeDef *_port;
	uint16_t _pin;
};

#endif // DS18B20_HPP
