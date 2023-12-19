/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�����
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @Software 		MDK 5.24
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-01-03
 * @note
					����ͷ���߶��壺
					------------------------------------
					ģ��ܽ�            ��Ƭ���ܽ�
					TX                 UART2_RX_A3
					RX                 UART2_TX_A2
					VSY(���ж�)         A0
					PCLK(�����ж�)      E11
					HREF(���ж�)		����Ҫ
					D0-D7(���ݿ�)       B0-B7
					------------------------------------
					Ĭ�Ϸֱ���       	160*120
					Ĭ��FPS             50֡
					------------------------------------
 ********************************************************************************************************************/
 
#ifndef _zf_device_config_h_
#define _zf_device_config_h_

#include "SEEKFREE_IIC.h"

unsigned char   mt9v03x_set_config_sccb         (short int buff[10][2]);
unsigned char   mt9v03x_set_exposure_time_sccb  (unsigned short int light);
unsigned char   mt9v03x_set_reg_sccb            (unsigned char addr, unsigned short int data);


extern unsigned char mt9v03x_set_config_sccb (short int buff[10][2]);

#endif
