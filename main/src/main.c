/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
int temp = 0;

void generateWave()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~GPIO_MODER_MODER1;
    GPIOA->MODER |= GPIO_MODER_MODER1_0;

    ///

    GPIOA->MODER &= ~GPIO_MODER_MODER2;
    GPIOA->MODER |= GPIO_MODER_MODER2_0;
    GPIOA->BSRR |= GPIO_BSRR_BS_2;

    GPIOA->MODER &= ~GPIO_MODER_MODER3;
    GPIOA->MODER |= GPIO_MODER_MODER3_0;
    GPIOA->BSRR |= GPIO_BSRR_BS_3;

    GPIOA->MODER &= ~GPIO_MODER_MODER4;
    GPIOA->MODER |= GPIO_MODER_MODER4_0;
    GPIOA->BSRR |= GPIO_BSRR_BS_4;

    GPIOA->MODER &= ~GPIO_MODER_MODER5;
    GPIOA->MODER |= GPIO_MODER_MODER5_0;
    GPIOA->BSRR |= GPIO_BSRR_BS_5;
//
//    GPIOA->MODER &= ~GPIO_MODER_MODER6;
//    GPIOA->MODER |= GPIO_MODER_MODER6_0;
//    GPIOA->BSRR |= GPIO_BSRR_BS_6;


    //
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 1-1;
    TIM6->ARR = 48000-1;
    TIM6->DIER |= TIM_DIER_UIE;
//    TIM6->CR2 &= ~TIM_CR2_MMS;
//    TIM6->CR2 |= TIM_CR2_MMS_1;
    NVIC->ISER[0] |= 1 << TIM6_DAC_IRQn;
    TIM6->CR1 |= 0x1;

}


void TIM6_DAC_IRQHandler(){
    TIM6->SR &= ~TIM_SR_UIF;
    if (temp == 1){
        GPIOA->BSRR |= GPIO_BSRR_BR_1;
        temp = 0;
    }
    else{
        GPIOA->BSRR |= GPIO_BSRR_BS_1;
        temp = 1;
    }

}
int main(void)
{

	generateWave();
}
