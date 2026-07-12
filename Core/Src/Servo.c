#include "Servo.h"
#include "tim.h"

void Servo_Init(void)
{
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);	

}
	
void Servo_Angle1(float Angle)//左后   PC7
{
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,(180-Angle) / 180 * 2000 + 500);//右上
}

void Servo_Angle2(float Angle)//    PC6   左前腿
{	
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,(180-Angle) / 180 * 2000 + 500);//左上
}

void Servo_Angle3(float Angle)//   PB15    右前腿
{
    __HAL_TIM_SetCompare(&htim15, TIM_CHANNEL_2,Angle / 180 * 2000 + 500);//左下
}

void Servo_Angle4(float Angle)//右后   PB14
{
    __HAL_TIM_SetCompare(&htim15, TIM_CHANNEL_1,Angle / 180 * 2000 + 500);//右下
}

