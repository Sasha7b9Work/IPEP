// 2022/6/7 9:07:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/ADC.h"
#include <stm32f1xx_hal.h>


namespace ADC
{
#define PORT_READY GPIOA
#define PIN_READY GPIO_PIN_0
#define READY PORT_READY, PIN_READY

#define PORT_CS GPIOA
#define PIN_CS GPIO_PIN_1
#define CS PORT_CS, PIN_CS

#define PORT_CLK GPIOA
#define PIN_CLK GPIO_PIN_2
#define CLK PORT_CLK, PIN_CLK

#define PORT_IN GPIOA
#define PIN_IN GPIO_PIN_3
#define IN PORT_IN, PIN_IN

#define PORT_OUT GPIOA
#define PIN_OUT GPIO_PIN_4
#define OUT PORT_OUT, PIN_OUT
}


void ADC::Init()
{
    GPIO_InitTypeDef is =
    {
        PIN_READY,
        GPIO_MODE_INPUT,
        GPIO_PULLUP,
        GPIO_SPEED_FREQ_HIGH
    };

    HAL_GPIO_Init(PORT_READY, &is);

    is.Pin = PIN_CS;
    is.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(PORT_CS, &is);

    is.Pin = PIN_CLK;
    is.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(PORT_CLK, &is);

    is.Pin = PIN_IN;
    is.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(PORT_IN, &is);

    is.Pin = PIN_OUT;
    is.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(PORT_OUT, &is);
}
