#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stdio.h"

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


void COM1Init(u32 BaudRate)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	USART_InitTypeDef USART_InitStructure;
  
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);  
  	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);    
  	USART_InitStructure.USART_BaudRate = BaudRate;//波特率设置
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
  	USART_Init(USART1, &USART_InitStructure);
  	USART_Cmd(USART1, ENABLE);
  	USART_ClearFlag(USART1, USART_FLAG_TC);
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

int my_putc(int ch)
{
  	USART_SendData(USART1, (u8) ch);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  	return ch;
}

struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;         
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{
  	USART_SendData(USART1, (u8) ch);
  	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
  	return ch;
}

int fputs(const char *ch, FILE *f)
{
	while (*ch) {
		fputc(*ch, f);
		ch++;
	}
	return 0;
}

int puts(const char *ch)
{
	return 0;
}

int main()
{
	LED_Init();
	COM1Init(115200);

	while (1) {
		GPIOB->ODR = 0x0000;
		delay(1000);
		GPIOB->ODR = 0xFFFF;
		delay(1000);
		printf("debug info\r\n");
	}

	return 0;
}
