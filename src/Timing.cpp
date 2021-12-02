#include "Timing.hpp"

TIMER::TIMER(TIM_HandleTypeDef* tim)
{
	_tim = tim;
	HAL_TIM_Base_Start(_tim);
}

void TIMER::delayUS(uint16_t us)
{
	//__disable_irq();
	_tim->Instance->CNT = 0;			//Set Timer value to 0, the Timer ticks every microsecond and counts up
	while(_tim->Instance->CNT < us);	//Wait till the set delay time is elapsed
	//__enable_irq();
}
