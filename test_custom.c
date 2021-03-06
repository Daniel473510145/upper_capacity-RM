#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "pid.h"
#include "sys.h"
#include  "gimbal_task.h"
 

int16_t upper_moto_position[10] = {0};
int16_t upper_moto_speed[10] =  {0};
int16_t upper_intaker_position[10] = {0};
int16_t upper_intaker_speed[10] = {0};
int16_t upper_moto_current[10]={0};
uint8_t test_servo;
uint8_t key1;
	/*upper controller */
/**
pid_t pid_test_upper_M3508_left ={0};
pid_t pid_test_upper_M3508_right={0};
pid_t pid_test_upper_M2006_left= {0};
pid_t pid_test_upper_M2006_right={0};
pid_t pid_test_upper_intaker = {0};
pid_t pid_huan = {0};
*/
//uint16_t ANGLE_MAX_VALUE[3] = {90, 370, 260};
void set_test_gimbal_current1(int16_t test_gimbal_current[]);

/**
int SpeedP[] = {28, 8, 8};
int SpeedD[] = {175, 100, 110};
int PositionP[] = {8, 8, 8};
int PositionD[] = {3, 3, 3}; */

void test_moto_control(void)
{
   //LED控制函数
	 for(int i=0;i<12;i++){
	 write_led_io(i,LED_ON);	
	 }
   //电机的速度给定
	 /*
	 ch1-右侧左右
	 ch2-左侧上下
	 ch3-左侧左右
	 ch4-左侧上下*/
	 
	 /**
	 switch (rc.sw1){
		 case 1 :
			 	send_chassis_moto_zero_current();//底盘电机
	 upper_moto_position[0] = rc.ch2 / RC_MAX_VALUE * MAX_VALUE_M3508; //left M3508 controller_ID1
   upper_moto_position[1] = -rc.ch2 / RC_MAX_VALUE * MAX_VALUE_M3508; //right M3508 controller_ID2
	 upper_moto_position[2] = rc.ch4 / RC_MAX_VALUE * MAX_VALUE_M2006; // left M2006 controller_ID3
   upper_moto_position[3] = -rc.ch4  / RC_MAX_VALUE * MAX_VALUE_M2006; //right M2006 controller_ID4
	 upper_intaker_position[0] = -rc.ch3 /RC_MAX_VALUE* MAX_VALUE_M2006;//  intaker M2006 controller_ID5
     break;
		 
	   case 3: 
			 send_gimbal_moto_zero_current();
		   
			 
	 
	 
	 }
	 */
	 /**
	 if (rc.kb.bit.Q){
	 	 send_gimbal_moto_zero_current();
	 }
	 else {
	 	 send_gimbal_moto_zero_current();
	 } 
	 */
	 /**
   upper_moto_position[0] = rc.ch2 / RC_MAX_VALUE * MAX_VALUE_M3508; //left M3508 controller_ID1
   upper_moto_position[1] = -rc.ch2 / RC_MAX_VALUE * MAX_VALUE_M3508; //right M3508 controller_ID2
	 upper_moto_position[2] = rc.ch4 / RC_MAX_VALUE * MAX_VALUE_M2006; // left M2006 controller_ID3
   upper_moto_position[3] = -rc.ch4  / RC_MAX_VALUE * MAX_VALUE_M2006; //right M2006 controller_ID4
	 upper_intaker_position[0] = -rc.ch3 /RC_MAX_VALUE* MAX_VALUE_M2006;//  intaker M2006 controller_ID5
*/
	 
	
	 
   upper_moto_speed[0] = pid_calc(&pid_test_upper_M3508_left,        moto_chassis[0].speed_rpm, upper_moto_position[0]);//The speed of left M3508 controller_ID1
   upper_moto_speed[1] = pid_calc(&pid_test_upper_M3508_right,       moto_chassis[1].speed_rpm, upper_moto_position[1]);//The speed of right M3508 controller_ID2
   upper_moto_speed[2] = pid_calc(&pid_test_upper_M2006_left,        moto_chassis[2].speed_rpm, upper_moto_position[2]);//The speed of left M2006 controller_ID3
   upper_moto_speed[3] = pid_calc(&pid_test_upper_M2006_right,       moto_chassis[3].speed_rpm, upper_moto_position[3]);//The speed of right M2006 controller_ID4
   upper_intaker_speed[0] = pid_calc(&pid_test_upper_intaker,        moto_yaw.speed_rpm       , upper_intaker_position[0] );//The speed of intaker M2006 controller_ID5
	 //pid 是6ID
	//双环pid控制上层机构
	 /**位置环
	 example
    upper_moto_position[3] = -rc.ch4  / RC_MAX_VALUE * 90; 
	 upper_moto_speed[5] = pid_calc(&pid_huan, moto_chassis[0].total_angle/19.2,upper_moto_position[3]);
	 */
   
   //上层机构发送电机电流
   set_test_motor_current(upper_moto_speed);
	 set_test_gimbal_current1(upper_intaker_speed);
	 
	    //舵机控制函数周期设定
			/*
   set_pwm_group_param(PWM_GROUP1,20000);
	*/
	/**
   //开启控制端�
	    start_pwm_output(PWM_IO1);
    
	//舵机控制命令
		if(test_servo == 0 )
		  {
			set_pwm_param(PWM_IO1,2200);
		  }
		else
		  {
		  set_pwm_param(PWM_IO1,1500);
		  }
   */

//  扩展板的按键控制电机
//      read_key_io(KEY_IO1,&key1);  
//			if(key1 ==1)
//		{
//			 set_test_motor_current(test_moto_current);
//			}
			
			
			
}
   //电机初始化参数设定
	void test_moto_init(void)
		{
			 pid_init(&pid_test_upper_M3508_left, 7000, 0, 10, 0, 0);//初始化pid_test_upper_M3508_left
	     pid_init(&pid_test_upper_M3508_right, 7000, 0, 10, 0, 0);//初始化pid_test_upper_M3508_right

			 pid_init(&pid_test_upper_M2006_left, 7000, 0, 10, 0, 0);//初始化pid_test_upper_M2006_right
	     pid_init(&pid_test_upper_M2006_right, 7000, 0, 10, 0, 0);//初始化pid_test_upper_M2006_right
		 
		   pid_init(&pid_test_upper_intaker, 7000, 0, 10, 0, 0);//初始化pid_test_upper_intaker
			/**
	     pid_init(&pid_test_moto_position_move, 7000, 0, PositionP[1], 0, PositionD[1]);
		 
		   pid_init(&pid_test_moto_speed_guardmove, 7000, 0, SpeedP[2], 0, SpeedD[2]);
	     pid_init(&pid_test_moto_position_guardmove, 7000, 0, PositionP[2], 0, PositionD[2]); */
	}	
