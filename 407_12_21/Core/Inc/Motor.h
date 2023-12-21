#ifndef  __MOTOR_H
#define __MOTOR_H
#include "main.h"
#define RR 118u    //电机减速比
#define ABSM1SPEED ABS(Motor1.speed)
#define ABSM2SPEED ABS(Motor2.speed)
#define ABSM3SPEED ABS(Motor3.speed)
#define ABSM4SPEED ABS(Motor4.speed)
#define COUNTERNUMM1 __HAL_TIM_GetCounter(&htim1)  //获取寄存器计数值
#define COUNTERNUMM2 __HAL_TIM_GetCounter(&htim2)
#define COUNTERNUMM3 __HAL_TIM_GetCounter(&htim3)
#define COUNTERNUMM4 __HAL_TIM_GetCounter(&htim4)
#define M1A(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,(GPIO_PinState)(state))
#define M1B(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,(GPIO_PinState)(state))
#define M2A(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,(GPIO_PinState)(state))
#define M2B(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,(GPIO_PinState)(state))
#define M3A(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,(GPIO_PinState)(state))
#define M3B(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,(GPIO_PinState)(state))
#define M4A(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_11,(GPIO_PinState)(state))
#define M4B(state) HAL_GPIO_WritePin(GPIOF,GPIO_PIN_12,(GPIO_PinState)(state))

void Motor_Init(void);
void SpeedAndAngleUpdate(void);
void applyControlOutput(float speed);
void moveForward(void);
void moveBackward(void);
void moveLeft(void);
void moveRight(void);
void moveFL(void);
void moveFR(void);
void moveBL(void);
void moveBR(void);
void rotateCW(void);
void rotateCCW(void);
void printfSpeed(void);
//电机结构体
typedef struct _Motor
{
	float speed;              //电机输出轴目前转速,单位为RPM
}motor;
#endif
