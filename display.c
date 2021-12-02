#include "display.h"
#include <stdio.h>
#include "stm32f0xx.h"



void fillDisplay()
{

    for(int i = 0; i < 32; i++)
       {
           for (int j = 0; j < 64; j++)
           {
               displayMatrix[i][j] = 0;
           }
       }
    for(int i = 1; i < 10; i++)
    {
        for (int j = 2; j < 6; j++)
        {
            displayMatrix[i][j] = 1;
//            printf("%d ",displayMatrix[i][j]);
        }
//
//        displayMatrix[5][9] = 1;
//        displayMatrix[5][31] = 1;
//        displayMatrix[5][62] = 1;
//        displayMatrix[5][63] = 1;

//        printf("\n");
    }
    for(int i = 1; i < 10; i++)
        {
            for (int j = 15; j < 30; j++)
            {
                displayMatrix[i][j] = 1;
//                printf("%d ",displayMatrix[i][j]);
            }

//            displayMatrix[5][9] = 1;
//            displayMatrix[5][31] = 1;
//            displayMatrix[5][62] = 1;
//            displayMatrix[5][63] = 1;

//            printf("\n");
        }
    }

void clockData(int i)
{
    GPIOA->MODER &= ~GPIO_MODER_MODER3;
    GPIOA->MODER |= GPIO_MODER_MODER3_0;

//    for(int i = 0; i < 32; i++){


        for(int j = 0; j < 64; j++){
            GPIOA->BSRR |= GPIO_BSRR_BR_1;
            if (displayMatrix[i][j]){
                GPIOC->BSRR |= GPIO_BSRR_BS_1;
                GPIOC->BSRR |= GPIO_BSRR_BS_4;
                GPIOC->BSRR |= GPIO_BSRR_BS_2;
               GPIOC->BSRR |= GPIO_BSRR_BS_6;
            }
            else{
                GPIOC->BSRR |= GPIO_BSRR_BR_1;
                GPIOC->BSRR |= GPIO_BSRR_BR_4;
                GPIOC->BSRR |= GPIO_BSRR_BR_2;
               GPIOC->BSRR |= GPIO_BSRR_BR_6;
            }
            GPIOA->BSRR |= GPIO_BSRR_BS_1;
        }

        GPIOA->BSRR |= GPIO_BSRR_BR_3;
//        turnOnRow(1);
//        turnOnRow(2);
//        turnOnRow(3);
//        turnOnRow(4);
        turnOnRow(i);
        GPIOA->BSRR|= GPIO_BSRR_BS_2;
        GPIOA->BSRR|= GPIO_BSRR_BR_2;
        GPIOA->BSRR |= GPIO_BSRR_BS_3;
//    }

}

void shiftDisplay()
{
    for(int i =  0; i < 32; i++)
    {
        int temp = displayMatrix[i][0];
        for(int j = 0; j < 63; j++)
        {
            displayMatrix[i][j] =  displayMatrix[i][j+1];
        }
        displayMatrix[i][63] = temp;
    }
}



