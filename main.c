#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


void LED_Init(void)
{
  	GPIO_InitTypeDef  GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void delay(unsigned long i)
{
	unsigned long j;
	while (i--) {
		for (j = i; j > 0; j--) {
			if (j == 10)
				j--;
		}
	}
}

int main()
{
	LED_Init();

	while (1) {
		GPIOB->ODR = 0x0000;
		delay(1000);
		GPIOB->ODR = 0xFFFF;
		delay(1000);
	}

	return 0;
}
