# STM32 DS18B20 Temperature Sensor Library
C++ Library for interfacing the DS18B20 Temperature Sensor with a STM32 like the STM32F103C8 (BLUEPILL)

Based on the Library by https://controllerstech.com/ds18b20-and-stm32/

# Usage
Using the Library is very easy. Follow the steps.

1. Copy the four files of the src folder to your source / include folder.
2. Include the two header files 
        
        #include "Timing.hpp"
        #include "DS18B20.hpp"
3. Create a new TIMING object by using a hardware timer. Make sure the timer is enabled and ticks every microsecond
        
        TIMING timing = TIMING(&htim1);
4. Create a new DS18B20 object
        
        DS18B20 temp = DS18B20(&timing);
5. Use the implemented functions to read the temperature
        
        float temperature = temp.readTemperature();
