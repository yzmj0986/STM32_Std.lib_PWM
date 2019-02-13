#include "stm32f10x.h"
#include "led.h"
#include "system.h"
#include "exti.h"
#include "pwm.h"
#include "Systick.h"


int main()
{
  u16 i=0;
	u8 fx=0;
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	TIM3_CH1_PWM_Init(500,72-1);  //2KÆµÂÊ

	
	while(1)
	{
		if(fx==0)
		{
			i++;
			if(i==300)
			{
				fx=1;
			}
		}
		else
		{
			i--;
			if(i==0)
			{
				fx=0;
			}
		}
		TIM_SetCompare1(TIM3,i);
		delay_ms(10);
	}

}

