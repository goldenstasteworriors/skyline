#ifndef __SERVO_H
#define __SERVO_H
#include "main.h"
#define SERVOMAX1 2500
#define SERVOMAX2 2500
#define SERVOMAX3 2500
#define SERVOMAX4 2500
#define SERVOMIN1 500
#define SERVOMIN2 500
#define SERVOMIN3 500
#define SERVOMIN4 500
#define MAXANGLE1 360
#define MAXANGLE2 360
#define MAXANGLE3 360
#define MAXANGLE4 360
#define SERVODEGREEUNIT1 (SERVOMAX1-SERVOMIN1)/MAXANGLE1
#define SERVODEGREEUNIT2 (SERVOMAX2-SERVOMIN2)/MAXANGLE2
#define SERVODEGREEUNIT3 (SERVOMAX3-SERVOMIN3)/MAXANGLE3
#define SERVODEGREEUNIT4 (SERVOMAX4-SERVOMIN4)/MAXANGLE4
void servoInit(void);
void servoSetAngle1(int angle);
void servoSetAngle2(int angle);
void servoSetAngle3(int angle);
void servoSetAngle4(int angle);
#endif
