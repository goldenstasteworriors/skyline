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

#include "SEEKFREE_MT9V03X_CONFIG.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_MT9V03X.h"



volatile uint8_t mt9v03x_finish_flag = 0;                                                 // һ��ͼ��ɼ���ɱ�־λ
 __attribute__((aligned (4))) uint8_t mt9v03x_image[MT9V03X_H][MT9V03X_W];

static uint16_t mt9v03x_version = 0x00;



// ��Ҫ���õ�����ͷ������ �����������޸Ĳ���
static int16_t mt9v03x_set_confing_buffer[MT9V03X_CONFIG_FINISH][2] =
{
    {MT9V03X_INIT,              0},                                             // ����ͷ��ʼ��ʼ��

    {MT9V03X_AUTO_EXP,          MT9V03X_AUTO_EXP_DEF},                          // �Զ��ع�����
    {MT9V03X_EXP_TIME,          MT9V03X_EXP_TIME_DEF},                          // �ع�ʱ��
    {MT9V03X_FPS,               MT9V03X_FPS_DEF},                               // ͼ��֡��
    {MT9V03X_SET_COL,           MT9V03X_W},                                     // ͼ��������
    {MT9V03X_SET_ROW,           MT9V03X_H},                                     // ͼ��������
    {MT9V03X_LR_OFFSET,         MT9V03X_LR_OFFSET_DEF},                         // ͼ������ƫ����
    {MT9V03X_UD_OFFSET,         MT9V03X_UD_OFFSET_DEF},                         // ͼ������ƫ����
    {MT9V03X_GAIN,              MT9V03X_GAIN_DEF},                              // ͼ������
    {MT9V03X_PCLK_MODE,         MT9V03X_PCLK_MODE_DEF},                         // ����ʱ��ģʽ
};

// ������ͷ�ڲ���ȡ������������ �����������޸Ĳ���
static int16_t mt9v03x_get_confing_buffer[MT9V03X_CONFIG_FINISH - 1][2] =
{
    {MT9V03X_AUTO_EXP,          0},                                             // �Զ��ع�����
    {MT9V03X_EXP_TIME,          0},                                             // �ع�ʱ��
    {MT9V03X_FPS,               0},                                             // ͼ��֡��
    {MT9V03X_SET_COL,           0},                                             // ͼ��������
    {MT9V03X_SET_ROW,           0},                                             // ͼ��������
    {MT9V03X_LR_OFFSET,         0},                                             // ͼ������ƫ����
    {MT9V03X_UD_OFFSET,         0},                                             // ͼ������ƫ����
    {MT9V03X_GAIN,              0},                                             // ͼ������
    {MT9V03X_PCLK_MODE,         0},                                             // ����ʱ��ģʽ���� PCLKģʽ < ������� MT9V034 V1.5 �Լ����ϰ汾֧�ָ����� >
};


//-------------------------------------------------------------------------------------------------------------------
//  @brief      MS����ʱ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void system_delay_ms(uint16_t ms)
{

    extern void HAL_Delay(uint32_t Delay);
    HAL_Delay(ms);

}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ�������
//  @param      *Data		BUFF��ַ
//  @param      len			���ݳ���
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void uart_write_buffer(UART_HandleTypeDef* huart, uint8_t* Data, uint32_t len)
{
//    uart_putbuff(USARTx, Data, len);
	HAL_UART_Transmit(huart, Data, len, 0xFFFF);
}

static uint8_t rx_buff;
static uint8_t mt9v03x_uart_receive[3];
static uint8_t mt9v03x_receive_num = 0;
static volatile uint8_t mt9v03x_uart_receive_flag = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����������ͷ������2�ж��¼��ص�����
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       //��������MT9V032(���������ͷ)�ͽ������������ͷ����
//-------------------------------------------------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {
        mt9v03x_uart_receive[mt9v03x_receive_num] = rx_buff;
        mt9v03x_receive_num++;

        if(1==mt9v03x_receive_num && 0XA5!=mt9v03x_uart_receive[0])  
			mt9v03x_receive_num = 0;
        if(3 == mt9v03x_receive_num)
        {
			mt9v03x_receive_num = 0;
			mt9v03x_uart_receive_flag = 1;
        }
        HAL_UART_Receive_IT(&huart2,&rx_buff,1);
    }
}




//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ�̼��汾
// ����˵��     void
// ���ز���     uint16_t          0-��ȡ���� N-�汾��
// ʹ��ʾ��     mt9v03x_get_version();                          // ���øú���ǰ���ȳ�ʼ������
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint16_t mt9v03x_get_version(void)
{
    uint16_t temp = 0;
    uint8_t  uart_buffer[4];
    uint16_t timeout_count = 0;
    uint16_t return_value = 0;
//    uint32_t uart_buffer_index = 0;

    mt9v03x_uart_receive_flag = 0;

    uart_buffer[0] = 0xA5;
    uart_buffer[1] = MT9V03X_GET_STATUS;
    temp = MT9V03X_GET_VERSION;
    uart_buffer[2] = temp >> 8;
    uart_buffer[3] = (uint8_t)temp;
    uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

    do
    {
        if(mt9v03x_uart_receive_flag)
        {
            return_value = mt9v03x_uart_receive[1] << 8 | mt9v03x_uart_receive[2];
            break;
        }
        system_delay_ms(1);
    }
    while((MT9V03X_INIT_TIMEOUT > timeout_count ++));


    return return_value;
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��������ͷ�ڲ�������Ϣ
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8_t           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     mt9v03x_set_config(mt9v03x_set_confing_buffer);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t mt9v03x_set_config(int16_t buff[MT9V03X_CONFIG_FINISH][2])
{
    uint8_t return_state = 1;
    uint8_t  uart_buffer[4];
    uint16_t temp = 0;
    uint16_t timeout_count = 0;
    uint32_t loop_count = 0;
//    uint32_t uart_buffer_index = 0;



    switch(mt9v03x_version)
    {
		case 0x0230:
			loop_count = MT9V03X_PCLK_MODE;
			break;
		default:
			loop_count = MT9V03X_GAIN;
			break;
    }
	mt9v03x_uart_receive_flag = 0;
    // ���ò���  ������ο���������ֲ�
    // ��ʼ��������ͷ�����³�ʼ��
    for(; MT9V03X_SET_DATA > loop_count; loop_count --)
    {
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = buff[loop_count][0];
        temp = buff[loop_count][1];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8_t)temp;
        uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

        system_delay_ms(2);
    }

    do
    {
        if(mt9v03x_uart_receive_flag)
        {
            return_state = 0;
            break;
        }
        system_delay_ms(1);
    }
    while(MT9V03X_INIT_TIMEOUT > timeout_count ++);
    // ���ϲ��ֶ�����ͷ���õ�����ȫ�����ᱣ��������ͷ��51��Ƭ����eeprom��
    // ����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
    return return_state;
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ����ͷ�ڲ�������Ϣ
// ����˵��     buff            ����������Ϣ�ĵ�ַ
// ���ز���     uint8_t           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     mt9v03x_get_config(mt9v03x_get_confing_buffer);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t mt9v03x_get_config(int16_t buff[MT9V03X_CONFIG_FINISH - 1][2])
{
    uint8_t return_state = 0;
    uint8_t  uart_buffer[4];
    uint16_t temp = 0;
    uint16_t timeout_count = 0;
    uint32_t loop_count = 0;
//    uint32_t uart_buffer_index = 0;



    switch(mt9v03x_version)
    {
    case 0x0230:
        loop_count = MT9V03X_PCLK_MODE;
        break;
    default:
        loop_count = MT9V03X_GAIN;
        break;
    }

    for(loop_count = loop_count - 1; 1 <= loop_count; loop_count --)
    {
		mt9v03x_uart_receive_flag = 0;
        if((0x0230 > mt9v03x_version) && (MT9V03X_PCLK_MODE == buff[loop_count][0]))
        {
            continue;
        }
        uart_buffer[0] = 0xA5;
        uart_buffer[1] = MT9V03X_GET_STATUS;
        temp = buff[loop_count][0];
        uart_buffer[2] = temp >> 8;
        uart_buffer[3] = (uint8_t)temp;
        uart_write_buffer(MT9V03X_COF_UART, uart_buffer, 4);

        timeout_count = 0;
        do
        {
            if(mt9v03x_uart_receive_flag)
            {
                return_state = 0;
				buff[loop_count][1] = mt9v03x_uart_receive[1] << 8 | mt9v03x_uart_receive[2];
                break;
            }
            system_delay_ms(1);
        }
        while(MT9V03X_INIT_TIMEOUT > timeout_count ++);


        if(MT9V03X_INIT_TIMEOUT < timeout_count)                                // ��ʱ
        {
            return_state = 1;
            break;
        }
    }
    return return_state;
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ����ͷ֡�ж��¼��ص�����
//  @return     void
//  @since      v1.1
//  Sample usage:		�ú�����stm32f4xx_hal_dcmi.c�ļ��е�HAL_DCMI_IRQHandler�����н��лص�
//-------------------------------------------------------------------------------------------------------------------
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
    mt9v03x_finish_flag = 1; 										//��־λ��Ϊ1
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ͷͼ��������λ���鿴ͼ��
//  @param      *imgaddr            ѹ��ͼ�����ݵ�ַ
//  @param      *imgsize            ͼ���С
//  @return     void
//  @since      v1.0
//  Sample usage:                   ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_mt9v03x(UART_HandleTypeDef* huart, void *imgaddr, uint32_t imgsize)
{
	uint8_t dat[] = {0x00, 0xff, 0x01, 0x01};

	uart_write_buffer(huart, dat, 4);
	uart_write_buffer(huart, imgaddr, imgsize);

}

//-------------------------------------------------------------------------------------------------------------------
// �������     MT9V03X ����ͷ��ʼ��
// ����˵��     void
// ���ز���     uint8_t           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     zf_log(mt9v03x_init(), "mt9v03x init error");
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
uint8_t mt9v03x_init(void)
{
    uint8_t return_state = 0;

	do
    {
        // �ȴ�����ͷ�ϵ��ʼ���ɹ�
        system_delay_ms(1000);    	// ��ʱ1��                                          	 

        // ����ʹ��IIC���г�ʼ���������ʼ�����ɹ����ͻ�ִ�д��ڳ�ʼ��
        simiic_init();
        // mt9v03x_set_config_sccb ����ֵ1����ʧ�ܣ�����0����ɹ�
        // mt9v03x_set_config_sccb ��������Ѿ�����װ��lib���������ṩ��
        if(mt9v03x_set_config_sccb(mt9v03x_set_confing_buffer) == 0)
        {
			// ����MCU�ĵ�Ƭ����ʼ��ʧ��
            break;
        }
		else
        {
			system_delay_ms(200);
			// ��ʼ������
            MX_USART2_UART_Init();
			HAL_UART_MspInit(MT9V03X_COF_UART);
			// ���ý����ж�
			HAL_UART_Receive_IT(MT9V03X_COF_UART,&rx_buff,1);
			
			// ��ȡ�汾��
            mt9v03x_version = mt9v03x_get_version();

            if(mt9v03x_set_config(mt9v03x_set_confing_buffer))
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���

                return_state = 1;
                break;
            }

            // ��ȡ���ñ��ڲ鿴�����Ƿ���ȷ
            if(mt9v03x_get_config(mt9v03x_get_confing_buffer))
            {
                // �������������˶�����Ϣ ������ʾ����λ��������
                // ��ô���Ǵ���ͨ�ų�����ʱ�˳���
                // ���һ�½�����û������ ���û������ܾ��ǻ���

                return_state = 1;
                break;
            }
        }
    }while(0);


	// ʹ��DCMI�ж�
    __HAL_DCMI_ENABLE_IT(&hdcmi, DCMI_IT_FRAME); 				// ����֡�жϣ�һ֡�ж�һ��
    HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_CONTINUOUS,(uint32_t)mt9v03x_image, MT9V03X_H * MT9V03X_W/4);	// ʹ��DCMI_DMA�������ɼ�ͼ��
	
    return return_state;
}
