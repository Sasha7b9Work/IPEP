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

#define PIN_CLK_SET   HAL_GPIO_WritePin(CLK, GPIO_PIN_SET)      ; Delay()
#define PIN_CLK_RESET HAL_GPIO_WritePin(CLK, GPIO_PIN_RESET)    ; Delay()

#define PIN_IN_SET    HAL_GPIO_WritePin(IN, GPIO_PIN_SET)       ; Delay()
#define PIN_IN_RESET  HAL_GPIO_WritePin(IN, GPIO_PIN_RESET)     ; Delay()

    void WriteByte(uint8);

    uint8 ReadByte();

    void Delay()
    {
        volatile int i = 0;

        while (i < 100)
        {
            i++;
        }
    }
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


bool ADC::DataReady()
{
    return HAL_GPIO_ReadPin(READY) == GPIO_PIN_RESET;
}


float ADC::GetVoltage()
{
    return (float)((ReadByte() << 8) + ReadByte());
}


void ADC::Reset()
{

}


void ADC::WriteByte(uint8 byte)
{
    for (int i = 0; i < 8; i++)
    {
        PIN_CLK_RESET;

        if (byte & 0x80)
        {
            PIN_IN_SET;
        }
        else
        {
            PIN_IN_RESET;
        }

        byte <<= 1;

        PIN_CLK_SET;
    }
}


uint8 ADC::ReadByte()
{
    uint8 result = 0;

    for (int i = 0; i < 8; i++)
    {
        PIN_CLK_RESET;

        result >>= 1;

        if (HAL_GPIO_ReadPin(OUT) == GPIO_PIN_SET)
        {
            result |= 0x80;
        }

        PIN_CLK_SET;
    }

    return result;
}
