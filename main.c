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
#include "display.h"
#include <stdio.h>
int temp = 0;
int temp2 = 0;
int i = 0;
int flag = 1;
int counter = 0;
void turnOnRow(int row);



////////////////////////////////////////
//     (red) R1: PC1      G1: PC5 (green)
//    (blue) B1: PC3     GND: done (grey)
//     (red) R2: PC2      G2: PC6 (green)
//    (blue) B2: PC4     GND: done (grey)
//   (orange) A: PB1       B: PB2 (yellow)
//    (white) C: PB3       D: PB4 (brown)
// (purple) CLK: PA1     LAT: PA2 (yellow)
//  (purple) OE: PA1     GND: done (grey)
////////////////////////////////////////

/*
 * TIM6: CLK
 * TIM7: pixel data
 * TIM3: LAT (CLK*64)
 *
 */
void turnOnABCD(int a, int b, int c, int d){
    if (a){
        GPIOB->BSRR |= GPIO_BSRR_BS_1;
    }
    else{
        GPIOB->BSRR |= GPIO_BSRR_BR_1;
    }

    if (b){
         GPIOB->BSRR |= GPIO_BSRR_BS_2;
     }
     else{
         GPIOB->BSRR |= GPIO_BSRR_BR_2;
     }

    if (c){
         GPIOB->BSRR |= GPIO_BSRR_BS_3;
     }
     else{
         GPIOB->BSRR |= GPIO_BSRR_BR_3;
     }

    if (d){
         GPIOB->BSRR |= GPIO_BSRR_BS_4;
     }
     else{
         GPIOB->BSRR |= GPIO_BSRR_BR_4;
     }

//    b ? GPIOB->BSRR |= GPIO_BSRR_BS_2 : GPIOB->BSRR |= GPIO_BSRR_BR_2;

}


void enablePorts(){


    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
     GPIOA->MODER &= ~GPIO_MODER_MODER1;
     GPIOA->MODER |= GPIO_MODER_MODER1_0;

    GPIOA->MODER &= ~GPIO_MODER_MODER2;
    GPIOA->MODER |= GPIO_MODER_MODER2_0;

    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    // setting up PB1,PB2, PB3, PB4 (A, B , C, D)
    GPIOB->MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4);
    GPIOB->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0);

    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    // setting up PC1, PC2, PC3, PC4, PC5, PC6 (R1, R2, B1, B2, G1, G2)
    GPIOC->MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6);
    GPIOC->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0);

//    GPIOC->ODR |= GPIO_ODR_1 | GPIO_ODR_3 | GPIO_ODR_5;
//    GPIOC->ODR |= GPIO_ODR_2 | GPIO_ODR_4 | GPIO_ODR_6;
}
void generateWave()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~GPIO_MODER_MODER1;
    GPIOA->MODER |= GPIO_MODER_MODER1_0;

   GPIOA->MODER &= ~GPIO_MODER_MODER2;
   GPIOA->MODER |= GPIO_MODER_MODER2_0;

//    GPIOA->MODER &= ~GPIO_MODER_MODER2;
//    GPIOA->MODER |= GPIO_MODER_MODER2_0;
//    GPIOA->BSRR |= GPIO_BSRR_BS_2;
//
//    GPIOA->MODER &= ~GPIO_MODER_MODER3;
//    GPIOA->MODER |= GPIO_MODER_MODER3_0;
//    GPIOA->BSRR |= GPIO_BSRR_BS_3;
//
//    GPIOA->MODER &= ~GPIO_MODER_MODER4;
//    GPIOA->MODER |= GPIO_MODER_MODER4_0;
//    GPIOA->BSRR |= GPIO_BSRR_BS_4;
//
//    GPIOA->MODER &= ~GPIO_MODER_MODER5;
//    GPIOA->MODER |= GPIO_MODER_MODER5_0;
//    GPIOA->BSRR |= GPIO_BSRR_BS_5;
//
//    GPIOA->MODER &= ~GPIO_MODER_MODER7;
//    GPIOA->MODER |= GPIO_MODER_MODER7_0;
//    GPIOA->BSRR |= GPIO_BSRR_BS_7;

//    GPIOA->MODER &= ~GPIO_MODER_MODER6;
//    GPIOA->MODER |= GPIO_MODER_MODER6_0;
//    GPIOA->BSRR |= GPIO_BSRR_BS_6;


    //
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6->PSC = 50-1;
    TIM6->ARR = 4800-1;
    TIM6->DIER |= TIM_DIER_UIE;
//    TIM6->CR2 &= ~TIM_CR2_MMS;
//    TIM6->CR2 |= TIM_CR2_MMS_1;
    NVIC->ISER[0] |= 1 << TIM6_DAC_IRQn;
    TIM6->CR1 |= 0x1;

}


void TIM6_DAC_IRQHandler(){
    TIM6->SR &= ~TIM_SR_UIF;
    if (counter >= 64)
    {counter = 0;
    }
    if (i >= 4){
            i = 0;
        }
            if(flag == 1)
            {
            GPIOC->ODR |= GPIO_ODR_1 | GPIO_ODR_3 | GPIO_ODR_5;
            GPIOC->ODR |= GPIO_ODR_2 | GPIO_ODR_4 | GPIO_ODR_6;
            flag = 0;
    //            for(int j = 0; j < 100; j++);
        }
        else
        {
            GPIOC->BSRR |= GPIO_BSRR_BR_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3 | GPIO_BSRR_BR_4 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6;
            flag = 1;
    //            for(int j = 0; j < 100; j++);
        }
//    if (temp == 1){
        GPIOA->BSRR |= GPIO_BSRR_BR_1;
//        temp = 0;
//    }
//    else{
        GPIOA->BSRR |= GPIO_BSRR_BS_1;
//        temp = 1;
//    }
        turnOnRow(i);
            i++;
    counter++;

}

void turnOnRow(int row){
    switch(row){
    case 0:
        turnOnABCD(0,0,0,0);
        break;
    case 1:
        turnOnABCD(1,0,0,0);
        break;
    case 2:
        turnOnABCD(0,1,0,0);
        break;
    case 3:
        turnOnABCD(1,1,0,0);
        break;
    case 4:
        turnOnABCD(0,0,1,0);
        break;
    case 5:
        turnOnABCD(1,0,1,0);
        break;
    case 6:
        turnOnABCD(0,1,1,0);
        break;
    case 7:
        turnOnABCD(1,1,1,0);
        break;
    case 8:
        turnOnABCD(0,0,0,1);
        break;
    case 9:
        turnOnABCD(1,0,0,1);
        break;
    case 10:
        turnOnABCD(0,1,0,1);
        break;
    case 11:
        turnOnABCD(1,1,0,1);
        break;
    case 12:
        turnOnABCD(0,0,1,1);
        break;
    case 13:
        turnOnABCD(1,0,1,1);
        break;
    case 14:
        turnOnABCD(0,1,1,1);
        break;
    case 15:
        turnOnABCD(1,1,1,1);
        break;
    default:
        break;

    }

}
void init_TIM7(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
   TIM7->PSC = 960-1;
   TIM7->ARR = 2000-1;
   TIM7->DIER |= TIM_DIER_UIE;
//    TIM6->CR2 &= ~TIM_CR2_MMS;
//    TIM6->CR2 |= TIM_CR2_MMS_1;
   NVIC->ISER[0] |= 1 << TIM7_IRQn;
   TIM7->CR1 |= 0x1;

}

void TIM7_IRQHandler(void){
    TIM7->SR &= ~TIM_SR_UIF;
    if (i >= 4){
        i = 0;
    }
        if(flag == 1)
        {
        GPIOC->ODR |= GPIO_ODR_1 | GPIO_ODR_3 | GPIO_ODR_5;
        GPIOC->ODR |= GPIO_ODR_2 | GPIO_ODR_4 | GPIO_ODR_6;
        flag = 0;
//            for(int j = 0; j < 100; j++);
    }
    else
    {
        GPIOC->BSRR |= GPIO_BSRR_BR_1 | GPIO_BSRR_BR_2 | GPIO_BSRR_BR_3 | GPIO_BSRR_BR_4 | GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6;
        flag = 1;
//            for(int j = 0; j < 100; j++);
    }
//    turnOnRow(0);
//    turnOnRow(1);
//    turnOnRow(2);
    turnOnRow(i);
    i++;
//    for(int j = 0; j < 20000; j++);

}

void init_TIM3(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
   TIM3->PSC = 1000-1; //50*64-1;
   TIM3->ARR = 48000-1;
   TIM3->DIER |= TIM_DIER_UIE;
//    TIM6->CR2 &= ~TIM_CR2_MMS;
//    TIM6->CR2 |= TIM_CR2_MMS_1;
   NVIC->ISER[0] |= 1 << TIM3_IRQn;
   TIM3->CR1 |= 0x1;
}

void TIM3_IRQHandler(void){
    TIM3->SR &= ~TIM_SR_UIF;
//    if(counter == 64)
//    {
//    if (temp2 == 1){
//            GPIOA->BSRR |= GPIO_BSRR_BR_2;
//            temp2 = 0;
//        }
//        else{
//            GPIOA->BSRR |= GPIO_BSRR_BS_2;
//            temp2 = 1;
//        }
//    }

    shiftDisplay();


}
int main(void)
{

//	generateWave();
	enablePorts();
	fillDisplay();
//	clockData();
	init_TIM3();
while(1)
{
//    clockData(1);
    clockData(2);
    clockData(3);
    clockData(4);

        clockData(7);
        clockData(8);
        clockData(9);


//    clockData(5);

//    shiftDisplay();
//    for(int i = 0; i < 10000; i++);
}
//	init_TIM7();
//	init_TIM3();
//	turnOnABCD(1,1,0,0);
//	turnOnRow(0);
//	turnOnRow(1);
}
