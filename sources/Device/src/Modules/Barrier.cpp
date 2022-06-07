// 2022/6/7 12:28:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/Barrier.h"
#include <stm32f1xx_hal.h>


namespace Barrier
{
    bool opened = false;
}


void Barrier::Init()
{
    GPIO_InitTypeDef is =
    {
        GPIO_PIN_8 | GPIO_PIN_9,
        GPIO_MODE_OUTPUT_PP,
        GPIO_PULLUP,
        GPIO_SPEED_FREQ_HIGH
    };

    HAL_GPIO_Init(GPIOB, &is);

    opened = false;
}


void Barrier::Open()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);

    opened = true;
}


void Barrier::Close()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);

    opened = false;
}


bool Barrier::IsOpened()
{
    return opened;
}
