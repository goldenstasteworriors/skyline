#include "servo.h"
#include "tim.h"

void servoInit() {
	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
}
void servoSetAngle1(int angle) {
	angle *= SERVODEGREEUNIT1;
	__HAL_TIM_SET_COMPARE(&tim10, TIM_CHANNEL_1, angle);
}
void servoSetAngle2(int angle) {
	angle *= SERVODEGREEUNIT2;
	__HAL_TIM_SET_COMPARE(&tim11, TIM_CHANNEL_1, angle);
}
void servoSetAngle3(int angle) {
	angle *= SERVODEGREEUNIT3;
	__HAL_TIM_SET_COMPARE(&tim8, TIM_CHANNEL_3, angle);
}
void servoSetAngle4(int angle) {
	angle *= SERVODEGREEUNIT4;
	__HAL_TIM_SET_COMPARE(&tim13, TIM_CHANNEL_1, angle);
}
