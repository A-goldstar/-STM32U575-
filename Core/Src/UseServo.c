#include "UseServo.h"
#include "main.h"
#define DELAYE 1000
#define ATTACK_SPEED 400
#define MIN_DELAYE 10
int state = -1; //-1睡眠，1站立，2动作状态
void stop()    
{
    HAL_Delay(DELAYE);
    Servo_Angle1(180);//左后
	Servo_Angle2(180);//左前
	Servo_Angle3(180);//右前
    Servo_Angle4(180);//右后

}//睡眠状态
void stand()    
{
    Servo_Angle1(90);//左后
	Servo_Angle2(90);//左前
	Servo_Angle3(90);//右前
    Servo_Angle4(90);//右后

}//站立状态

void move0()
{
    switch(state)
    {
        case -1:
            HAL_Delay(DELAYE);
            Servo_Angle1(90);//左后
            Servo_Angle2(135);//左前
            Servo_Angle3(135);//右前
            Servo_Angle4(90);//右后
        case 1:
        case 2:    
            HAL_Delay(DELAYE);
            stand();
        break;
    }
}//站立转换
void move1()
{
    HAL_Delay(DELAYE);    
    Servo_Angle1(180);//左后
    Servo_Angle2(90);//左前
    Servo_Angle3(90);//右前
    Servo_Angle4(135);//右后
    HAL_Delay(ATTACK_SPEED);
}//摔倒了
void move2()
{
    HAL_Delay(DELAYE);
    Servo_Angle1(90);//左后
	Servo_Angle2(45);//左前
	Servo_Angle3(45);//右前
    Servo_Angle4(0);//右后
    HAL_Delay(ATTACK_SPEED);
}//握手
void move3()
{
    Servo_Angle1(125);//左后
	Servo_Angle2(160);//左前
	Servo_Angle3(160);//右前
    Servo_Angle4(125);//右后
    HAL_Delay(ATTACK_SPEED);
}//伸懒腰
void move4()
{
    
    Servo_Angle1(35);//左后
	Servo_Angle2(160);//左前
	Servo_Angle3(160);//右前
    Servo_Angle4(35);//右后
    HAL_Delay(ATTACK_SPEED);
}//坐下
//////////////////////////////////持续动作////////////////////////
void move5()
{
    Servo_Angle1(35);//左后
	Servo_Angle2(125);//左前
	Servo_Angle3(35);//右前
    Servo_Angle4(125);//右后
    HAL_Delay(ATTACK_SPEED);

    Servo_Angle1(125);//左后
	Servo_Angle2(35);//左前
	Servo_Angle3(125);//右前
    Servo_Angle4(35);//右后
    HAL_Delay(ATTACK_SPEED);
}//跳舞
void move6()
{
    Servo_Angle1(90);//左后
	Servo_Angle2(45);//左前
	Servo_Angle3(45);//右前
    Servo_Angle4(0);//右后
    HAL_Delay(ATTACK_SPEED);
    Servo_Angle1(90);//左后
	Servo_Angle2(90);//左前
	Servo_Angle3(90);//右前
    Servo_Angle4(90);//右后
    HAL_Delay(ATTACK_SPEED);
    Servo_Angle1(0);//左后
	Servo_Angle2(45);//左前
	Servo_Angle3(45);//右前
    Servo_Angle4(90);//右后
    HAL_Delay(ATTACK_SPEED);

}//攻击