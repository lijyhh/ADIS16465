#ifndef __ATTITUDE_SOLUTION_H
#define   __ATTITUDE_SOLUTION_H

#include "stm32f4xx.h"

#define Ki 0.008f
#define Kp 0.3f
#define dtt 0.05f   //Ƶ�ʵ���������������

//����ǶȽṹ��
struct angle 
{
	float pitch,roll,yaw;
};

void AHRS_update();










#endif   /*__ATTITUDE_SOLUTION_H*/
