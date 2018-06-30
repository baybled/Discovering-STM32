/*
*
*   This helper file sends characters over communication interfaces
* 
*/

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_usart.h>
#include "uart.h"


int uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags)
{
    // Initialise peripheral clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |
                            RCC_APB2Periph_AFIO |
                            RCC_APB2Periph_GPIOA, ENABLE);

    // Configure Pins for Tx and Rx
    GPIO_InitTypeDef    GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

    // Initialise USART1_Tx
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // Initialise USART1_Rx
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure USART
    USART_InitTypeDef   USART_InitStructure;
    USART_StructInit(&USART_InitStructure);

    // Modify USART_InitStructure for non-defualt values
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USARTx, &USART_InitStructure);
    USART_Cmd(USARTx, ENABLE);
    return 0;

}

int uart_putc(int c, USART_TypeDef* USARTx)
{
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    USARTx->DR = (c & 0xff);
    return 0;
}

int uart_getc(USART_TypeDef* USARTx)
{
    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
    return USARTx->DR & 0xff;
}
