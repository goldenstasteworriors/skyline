#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "main.h"
	extern TIM_HandleTypeDef htim1;
	extern TIM_HandleTypeDef htim5;
	extern TIM_HandleTypeDef htim6;
	void MX_TIM1_Init(void);
	void MX_TIM5_Init(void);
	void MX_TIM6_Init(void);
	void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim);
#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

