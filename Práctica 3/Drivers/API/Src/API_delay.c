#include "stm32f4xx_hal.h"
#include "API_delay.h"

/* USER CODE BEGIN 4 */
static bool_t delayIsRunning(delay_t* delay){
	return delay->running;
}

void delayInit(delay_t* delay, tick_t duration){
	delay->duration = duration;
	delay->running = false;
}

bool_t delayRead(delay_t* delay){
	if (delayIsRunning(delay)){
		if ((HAL_GetTick() - delay->startTime) >= delay->duration){
			delay->running = false;
			return true;
		}
	}
	else{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	return false;
}

void delayWrite(delay_t* delay, tick_t duration){
	if (!delayIsRunning(delay)){
		delay->duration = duration;
	}
	else{
		Error_Handler(); //Si falla, dejo el led encendido
	}
}


/* USER CODE END 4 */
