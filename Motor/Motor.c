#include "Motor.h"
void Motor_Init()
{
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);      //������������ʱ��
	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);           //������������ʱ�������ж�,���������
	HAL_TIM_Base_Start_IT(&htim6);                       //����10ms��ʱ���ж�
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);            //����PWM
	__HAL_TIM_SET_COUNTER(&htim1, 10000);                //��������ʱ����ʼֵ�趨Ϊ10000
	motor.loopNum = 0;                                   //�������
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
	// �����ٶȼ���PWMֵ
	uint16_t pwmValue = (uint16_t)(speed * TIM3->ARR / 100.0);
	// ����PWMֵ
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pwmValue);
}
