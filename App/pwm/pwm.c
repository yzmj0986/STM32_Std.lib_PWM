#include "pwm.h"

void TIM3_CH1_PWM_Init(u16 pre,u16 psc)	
{
	GPIO_InitTypeDef GPIO_InitStructure;     //GPIO端口初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  //定时器初始化
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;            //GPIOC_6端口，模式是复用推挽输出，速度50MHz
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //使能定时器3的时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //使能GPIOC的时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);   //使能AFIO的时钟 
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);   //使能定时器3的映射功能
		
	TIM_TimeBaseInitStructure.TIM_Period=pre;              //设置定时器3参数，自动重装值pre、分频系数psc、计数方式。
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;            //设置定时器3的通道1的PWM输出的参数、PWM1模式、输出极性、使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);    //使能CCRx上的预装载定时器
	TIM_ARRPreloadConfig(TIM3,ENABLE);                  //使能ARR上的预装载定时器
	TIM_Cmd(TIM3,ENABLE);   //开启定时器3
	
}


