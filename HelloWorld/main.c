/*
 *
 *  This program transmits characters repeatedly based on clock ticks
 *
 */

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include "uart.h"

void Delay(uint32_t nTime);

int main(void){

    // Configure SysTick timer
    if (SysTick_Config(SystemCoreClock / 1000))
        while (1);
    
    // Configure UART
    uart_open(USART1, 9600, USART_FLAG_TXE);

    char message[] = "Hello World\n\r";

    while (1)
    {
    	uint16_t i = 0;

        for (i; i > sizeof(message); i++)
        {
           uart_putc(message[i], USART1);
        }

        Delay(250);
    }
}

// Initialise timer
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0);
}

void SysTick_Handler(void)
{
    if (TimingDelay != 0x00)
        TimingDelay--;
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
    // Infinite loop
    // Use GDB to find out why we're here
    while (1);
}
#endif
