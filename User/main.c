/**
  ******************************************************************************
  * @file    main.c
  * @author  DZH-HIT
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   ADIS��ȡ���ݲ�������̬����
	**main.c
	**stm32f4xx_it.c			���ļ��д���SysTick�жϺ�ADIS�ж�
	**bsp_spi_adis.c			����imu�����ݶ�ȡ�ͳ�ʼ���������ڸ��ļ���
	**bsp_exti.c					����ADIS�ж�����
	**kalman.c						�������˲�����ش���
	**attitude_solution.c	��̬�������ش���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_debug_usart.h"
#include "./adis/bsp_spi_adis.h" 
#include "./exit/bsp_exti.h"
#include "./systick/bsp_SysTick.h"
#include "./kalman/kalman.h"
#include "./attitude_solution/attitude_solution.h"

//ȫ�ֱ���
struct angle euler={0,0,0};
int new_data;

// ��ʱ����
void Delay_us(u32 time)
{
  u32 i=8*time;
  while(i--);
}

/*���������*/
uint32_t Task_Delay[NumOfTask]={0};

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 	
	/******************** ���ֳ�ʼ�� **************************/
	LED_GPIO_Config();
	SysTick_Init();	
	Debug_USART_Config();	
	EXTI_Config();
	ADIS16465_Init();	 		
	
	//���ADIS16564
	if (SPI_ADIS_ReadID())
	{	
		while(1)
		{
				if(new_data)
				{				
						AHRS_update();
						printf("zƫ����=%3.5f\n",euler.yaw);
//						printf(" y������=%3.5f, x�����=%3.5f��zƫ����=%3.5f\n",euler.pitch,euler.roll,euler.yaw);
						new_data = 0;				
				}
		 }
	}
	else
	{
			LED_RED; 	
			while(1);		
	 }
}

/*********************************************END OF FILE**********************/


