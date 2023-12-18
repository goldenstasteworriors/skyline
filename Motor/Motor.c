#include "Motor.h"
void Motor_Init()
{
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);      //开启编码器定时器
	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理
	HAL_TIM_Base_Start_IT(&htim6);                       //开启10ms定时器中断
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);            //开启PWM
	__HAL_TIM_SET_COUNTER(&htim1, 10000);                //编码器定时器初始值设定为10000
	motor.loopNum = 0;                                   //溢出计数
}
void SpeedAndAngleUpdate()
{
	int16_t pluse = COUNTERNUM - RELOADVALUE / 2;
	Motor.totalAngle = pluse + Motor.loopNum * RELOADVALUE / 2;
	Motor.speed = (float)(Motor.totalAngle - Motor.lastAngle) / (4 * 13 * RR) * 6000;
	Motor.lastAngle = Motor.totalAngle;
}
float getActualSpeed()
{
	SpeedAndAngleUpdate();
	return Motor.speed;
}
void EncodingTimerUpdate()
{
	if (COUNTERNUM < 10000)
		Motor.loopNum++;
	else if (COUNTERNUM > 10000)
		Motor.loopNum--;
	__HAL_TIM_SetCounter(&htim1, 10000);
}
void applyControlOutput(float speed)
{
	// 根据速度计算PWM值
	uint16_t pwmValue = (uint16_t)(speed * TIM3->ARR / 100.0);
	// 更新PWM值
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwmValue);
}
