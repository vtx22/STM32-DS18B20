# STM32 DS18B20 Temperature Sensor Library
C++ Library for interfacing the DS18B20 Temperature Sensor with a STM32 like the STM32F103C8 (BLUEPILL)

Based on the Library by https://controllerstech.com/ds18b20-and-stm32/

# Usage
Using the Library is very easy. Follow these steps:

1. Create a hardware timer (htim) that ticks every microsecond. Calculate the necessary prescaler based on your mcu clock frequency.

2. Copy the .hpp and .cpp files to your source / include folder.
3. Include the header file
```C++
        #include "DS18B20.hpp"
```
5. Create a new DS18B20 object by passing the htim reference, the GPIO Port and the GPIO Pin of the sensor. If you are using htim1 and Pin PB13 for example, call
```C++
        DS18B20 temp_sensor = DS18B20(&htim1, GPIOB, GPIO_Pin_13);
```
7. Use the implemented functions to read the temperature
```C++
        float temperature = temp_sensor.read_temp_celsius();
        float temperature = temp_sensor.read_temp_fahrenheit();
```
