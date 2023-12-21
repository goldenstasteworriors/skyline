#include "main.h"
#include "tim.h"
#include "pid.h"
#include "Motor.h"
#include "usart.h"
motor Motor1 = { 0 };
motor Motor2 = { 0 };
motor Motor3 = { 0 };
motor Motor4 = { 0 };
extern motor Motor1;
extern motor Motor2;
extern motor Motor3;
extern motor Motor4;
	Pid_Typedef pid = {
.SetPoint = 100.0,
.PreError = 0.0,
.LastError = 0.0,
.dError = 0.0,
.SumError = 0.0,
.SetPointLast = 0.0,
.P = 1.0,
.I = 0.1,
.D = 0.01,
.IMax = 100.0,
.ErrorMax = 10.0,
.OutMax = 100.0,
.deadband = 0.1,
.POut = 0.0,
.IOut = 0.0,
.DOut = 0.0,
};
void Motor_Init()
{
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);      //开启编码器定时器
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理
	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE_IT(&htim4, TIM_IT_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim1, 5000);                //编码器定时器初始值设定为5000
	__HAL_TIM_SET_COUNTER(&htim2, 5000);
	__HAL_TIM_SET_COUNTER(&htim3, 5000);
	__HAL_TIM_SET_COUNTER(&htim4, 5000);
	HAL_TIM_Base_Start(&htim5);
	HAL_TIM_Base_Start(&htim5);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);            //开启PWM
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&htim7);                       //开启定时器中断用于检测速度
}
void SpeedAndAngleUpdate()
{
	//M1
	int deltaTick1 = COUNTERNUMM1 - 5000;
	Motor1.speed = deltaTick1 / (4.0 * 7.0 * 118) * 2400;
	__HAL_TIM_SET_COUNTER(&htim1, 5000);
	//M2
	int deltaTick2 = COUNTERNUMM2 - 5000;
	Motor2.speed = deltaTick2 / (4.0 * 7.0 * 118) * 2400;
	__HAL_TIM_SET_COUNTER(&htim2, 5000);
	//M3
	int deltaTick3 = COUNTERNUMM3 - 5000;
	Motor3.speed = deltaTick3 / (4.0 * 7.0 * 118) * 2400;
	__HAL_TIM_SET_COUNTER(&htim3, 5000);
	//M4
	int deltaTick4 = COUNTERNUMM4 - 5000;
	Motor4.speed = deltaTick4 / (4.0 * 7.0 * 118) * 2400;
	__HAL_TIM_SET_COUNTER(&htim4, 5000);
}
void applyControlOutput(float speed)
{
	pid.SetPoint=speed;
	int PWMVALUE1 =PID_Calc(&pid,ABSM1SPEED)*76.92307692f;
	int PWMVALUE2 =PID_Calc(&pid,ABSM2SPEED)*76.92307692f;
	int PWMVALUE3 =PID_Calc(&pid,ABSM3SPEED)*76.92307692f;
	int PWMVALUE4 =PID_Calc(&pid,ABSM4SPEED)*76.92307692f;
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, PWMVALUE1);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, PWMVALUE2);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, PWMVALUE3);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, PWMVALUE4);
}
void moveForward(){
	M1A(1);
	M1B(0);
	M2A(1);
	M2B(0);
	M3A(1);
	M3B(0);
	M4A(1);
	M4B(0);
}
void moveBackward(){
	M1A(0);
	M1B(1);
	M2A(0);
	M2B(1);
	M3A(0);
	M3B(1);
	M4A(0);
	M4B(1);
}
void moveLeft(){
	M1A(0);
	M1B(1);
	M2A(1);
	M2B(0);
	M3A(1);
	M3B(0);
	M4A(0);
	M4B(1);}
void moveRight(){
	M1A(1);
	M1B(0);
	M2A(0);
	M2B(1);
	M3A(0);
	M3B(1);
	M4A(1);
	M4B(0);}
void moveFL(){
  M1A(0);
	M1B(0);
	M2A(1);
	M2B(0);
	M3A(1);
	M3B(0);
	M4A(0);
	M4B(0);}
void moveFR(){
	M1A(1);
	M1B(0);
	M2A(0);
	M2B(0);
	M3A(0);
	M3B(0);
	M4A(1);
	M4B(0);}
void moveBL(){
	M1A(0);
	M1B(1);
	M2A(0);
	M2B(0);
	M3A(0);
	M3B(0);
	M4A(0);
	M4B(1);}
void moveBR(){
	M1A(0);
	M1B(0);
	M2A(0);
	M2B(1);
	M3A(0);
	M3B(1);
	M4A(0);
	M4B(0);}
void rotateCW(){
	M1A(1);
	M1B(0);
	M2A(0);
	M2B(1);
	M3A(1);
	M3B(0);
	M4A(0);
	M4B(1);}
void rotateCCW(){
	M1A(0);
	M1B(1);
	M2A(1);
	M2B(0);
	M3A(0);
	M3B(1);
	M4A(1);
	M4B(0);}
void printfSpeed()
{
	HAL_Delay(200);
	printf("%.2f,%.2f,%.2f,%.2f\n",Motor1.speed,Motor2.speed,Motor3.speed,Motor4.speed);
}
