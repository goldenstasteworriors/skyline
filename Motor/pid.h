#ifndef __PID_H
#define __PID_H
#include "main.h"
#define ABS(x) ((x)>0? (x):(-(x))) 
#define LIMIT_MAX_MIN(x, max, min)	(((x) <= (min)) ? (min):(((x) >= (max)) ? (max) : (x)))
typedef struct PID{
		float SetPoint;			//�趨Ŀ��ֵ
		float SetPointLast;
		float deadband; //����
		
		float P;						//��������
		float I;						//���ֳ���
		float D;						//΢�ֳ���
		
		float LastError;		//ǰ�����
		float PreError;			//��ǰ���
		float SumError;			//�������
		float dError;
		
		float ErrorMax;			//ƫ������ ����ƫ���򲻼����������
		float IMax;					//��������
		
		float POut;					//�������
		float IOut;					//�������
		float DOut;					//΢�����
	  float OutMax;       //�޷�
}Pid_Typedef;

float PID_Calc(Pid_Typedef * P, float ActualValue);  
#endif /* __PID_H__ */
