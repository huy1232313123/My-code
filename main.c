#include "stm32f10x.h"     


void config_GPIO(void);

void uart_Config(void);

void Uart_Send_Char(char c);


void Uart_Send_String(char *c);


uint8_t Uart_Receive(void);

void delay(long t);





int main()
	
{
	config_GPIO();
	uart_Config();
	while (1)
	{
		 Uart_Send_String("huy dep trai");
			delay(10000000);
		
		
		
		
	}
	
	
}




void config_GPIO(void)
{
	/*enable GPIO A */
	RCC->APB2ENR |= (1<<2) | (1<<0);
	/*enable uart 2*/
	RCC->APB1ENR |= (1<<17);
	/* PA3 : RX2; PA2: TX2*/
	GPIOA->CRL = 0x00;
	GPIOA->CRL |= (0xB <<8) | (0x8 <<12);
	/*PA3 is set*/
	GPIOA->ODR |= (1<<3);
}


void uart_Config(void)
{
	USART2->CR1 = 0x00;
	/*enable uart , 1 start 8 bit n stop bit, transmit enable, receive enable*/
	USART2->CR1 |= (1<<13) ;
	/*baud rate 9600*/
	USART2->BRR |= 0xEA6;
	
	USART2->CR1 |= (1<<2) | (1<<3);
	
}



void Uart_Send_Char(char c)
{
	
	// while (USART2->SR & (1<<7) == 0);
	USART2->DR = c;
	while ((USART2->SR & (1<<6)) == 0);
}


void Uart_Send_String(char *c)
{
	int i=0;
	while (c[i])
	{
		Uart_Send_Char(c[i]);
		i++;
	}
}

uint8_t Uart_Receive(void)
{
	uint8_t tempt;
	while ((USART2->SR & (1<<5)) == 0);
	tempt = USART2->DR;
	return tempt; 
	
	
}


void delay(long t)
{
	while (t) t--;
}



