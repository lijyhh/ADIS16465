/**
  ******************************************************************************
  * @file    main.c
  * @author  Dong-HIT
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   SPI ADIS������д����,��Ҫ������bsp_spi_adis.c��
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
int ircnt=0;
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
	float Acel[3] = {0};
	float Gyro[3] = {0};
	float Acel2Angle[3] = {0};
	float Angle[3] = {0};
	float Velocity[3] = {0};
	float Temp = 0;	
	int count = 0;
	int cnt = 0;
	float avTemp = 0;	
	float endAngle = 0;	
//	int Temp1;	

	//����һ������������ṹ�壬�������������ṹ��
	KalmanCountData k[3];
	Kalman_Filter_Init(k);
	
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
//					printf(" y������=%3.5f, x�����=%3.5f\n",euler.pitch,euler.roll);
					new_data = 0;				
			}
//			if(Task_Delay[0]==TASK_ENABLE)
//			{				
//				AHRS_update();
//				printf(" y������=%3.2f, x�����=%3.2f, zƫ����=%3.2f\n",euler.pitch,euler.roll,euler.yaw);
//				
////				LED2_TOGGLE;
//				Task_Delay[0]=500;
// 
//			}
//			
//			if(Task_Delay[1]==0)
//			{
////				ADIS16465ReadAcc(Acel);
////				printf(" ���ٶȣ�%5.5f  %5.5f  %5.5f\n",Acel[0],Acel[1],Acel[2]);
////				
////				ADIS16465ReadGyro(Gyro);
////				printf(" �����ǣ�%2.5f  %2.5f  %2.5f\n",Gyro[0],Gyro[1],Gyro[2]);
////			
////				ADIS16465ReadAngle(Angle);
////				printf(" ��λ�ƣ�%2.5f  %2.5f  %2.5f\n",Angle[0],Angle[1],Angle[2]);
////				
////				ADIS16465ReadVelocity(Velocity);
////				printf("   �ٶȣ�%2.5f  %2.5f  %2.5f\r\n",Velocity[0],Velocity[1],Velocity[2]);
//				
////				accel2angle(Acel,Acel2Angle);
////				printf("ת���ĽǶȣ�%3.8f  %3.8f  %3.8f\r\n",Acel2Angle[0],Acel2Angle[1],Acel2Angle[2]);
//				
////				Kalman_Filter(Acel2Angle[0],Gyro[0],&k[0]);
//////				printf("1   %2.5f and %2.5f -------- %f and %f\n",Acel2Angle[0],Gyro[0],k[0].Angle_Final,k[0].Gyro_Final);
////				Kalman_Filter(Acel2Angle[1],Gyro[1],&k[1]);
//////				printf("2   %2.5f and %2.5f -------- %f and %f\n",Acel2Angle[1],Gyro[1],k[1].Angle_Final,k[1].Gyro_Final);
////				Kalman_Filter(Acel2Angle[2],Gyro[2],&k[2]);
//////				printf("3   %2.5f and %2.5f -------- %f and %f\n\r",Acel2Angle[2],Gyro[2],k[2].Angle_Final,k[2].Gyro_Final);
////					printf("Angle1=%2.3f Angle2=%2.3f Angle3=%2.3f------Gyro1=%2.3f Gyro2=%2.3f Gyro3=%2.3f\n",Acel2Angle[0],\
////					Acel2Angle[1],Acel2Angle[2],Gyro[0],Gyro[1],Gyro[2]);
////					printf("Anglex=%2.3f Angley=%2.3f Anglez=%2.3f------Gyrox=%2.3f Gyroy=%2.3f Gyroz=%2.3f\n\r",k[0].Angle_Final,\
////					k[1].Angle_Final,k[2].Angle_Final,k[0].Gyro_Final,k[1].Gyro_Final,k[2].Gyro_Final);

////				printf("\n\r");
////				ADIS16465ReadTemp(&Temp);
////				printf("    �¶�%.1f\r\n",Temp);				
//				
////				Temp1 = ADIS_ReadReg(DATA_CNTR);
////				printf(" ������%d\r\n",Temp1);	
//				
//				Task_Delay[1]=100; //����һ�����ݣ��ɸ����Լ���������߲���Ƶ�ʣ���100ms����һ��
//				
//			 }

			//*************************************	��������������ĸ�ʽ************************************//
	//		if(Task_Delay[i]==0)
	//		{
	//			Task(i);
	//			Task_Delay[i]=;
	//		}

		 }
	}
	else
	{
			LED_RED; 	
			while(1);		
	 }
}

/*********************************************END OF FILE**********************/


