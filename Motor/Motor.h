#ifndef  __MOTOR_H
#define __MOTOR_H
#define RR 30u    //������ٱ�
#define RELOADVALUE __HAL_TIM_GetAutoreload(&htim1)    //��ȡ�Զ�װ��ֵ,������Ϊ20000
#define COUNTERNUM __HAL_TIM_GetCounter(&htim1)        //��ȡ��������ʱ���еļ���ֵ
#define IN1(state) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,(GPIO_PinState)(state))    //M1
#define IN2(state) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,(GPIO_PinState)(state))    //M2

#include "main.h"

void Motor_Init();
void SpeedAndAngleUpdate();
float getActualSpeed();
void EncodingTimerUpdate();
void applyControlOutput(float speed);
//����ṹ��
typedef struct _Motor
{
	int32_t lastAngle;        //��10msת���ĽǶ�
	int32_t totalAngle;       //�ܵĽǶ�
	int16_t loopNum;          //�����������ֵ
	float speed;              //��������Ŀǰת��,��λΪRPM
}Motor;
#endif