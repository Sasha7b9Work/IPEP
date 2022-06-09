// 2022/6/7 9:07:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Modules/ADC.h"
#include "Hardware/Timer.h"
#include <stm32f1xx_hal.h>


/*
* Полярность?
*/


namespace ADC
{
//#define PORT_RESET  GPIOB           // Сброс напряжения
//#define PIN_RESET   GPIO_PIN_6

#define PORT_READY GPIOB            // АЦП готовность данных
#define PIN_READY GPIO_PIN_14
#define READY PORT_READY, PIN_READY

#define PORT_CLK GPIOB              // АЦП такты
#define PIN_CLK GPIO_PIN_13
#define CLK PORT_CLK, PIN_CLK

#define PORT_IN GPIOB               // АЦП вход. Сюда записываем данные
#define PIN_IN GPIO_PIN_12
#define IN PORT_IN, PIN_IN

#define PORT_OUT GPIOB              // АЦП выход. Отсюда читаем данные
#define PIN_OUT GPIO_PIN_15
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

    is.Pin = PIN_CLK;
    is.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(PORT_CLK, &is);

    is.Pin = PIN_IN;
    is.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(PORT_IN, &is);

    is.Pin = PIN_OUT;
    is.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(PORT_OUT, &is);

    is.Pin = GPIO_PIN_13;
    is.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOC, &is);

    PIN_CLK_SET;

    while (true)
    {
        //        WriteByte(0x10 | (1 << 3));
        //        Delay();
        //        uint8 byte1 = ReadByte();
        //        byte1 = byte1;
        //
        //        Delay();

        //        WriteByte(0x20 | (1 << 3));
        //        Delay();
        //        uint8 byte2 = ReadByte();
        //        byte2 = byte2;
        //
        //        Delay();

        Timer::Delay(20);

        WriteByte(0x68);
        Timer::Delay(1);
        uint8 byte1 = ReadByte();
        byte1 = byte1;
        Timer::Delay(1);
        uint8 byte2 = ReadByte();
        byte2 = byte2;
        Timer::Delay(1);
        uint8 byte3 = ReadByte();
        byte3 = byte3;

        Delay();
//        uint8 byte3 = ReadByte();
//        byte3 = byte3;

//        Timer::Delay(50);
    }

    WriteByte(0x10);        // \ Выбор активного входа
    Delay();
    WriteByte(0x02);        // /
    Delay();
    WriteByte(0x20);
    Delay();
    WriteByte(0x04);
    Delay();

    while (true)
    {
//        WriteByte(0x10 | (1 << 3));
//        Delay();
//        uint8 byte1 = ReadByte();
//        byte1 = byte1;
//
//        Delay();

//        WriteByte(0x20 | (1 << 3));
//        Delay();
//        uint8 byte2 = ReadByte();
//        byte2 = byte2;
//
//        Delay();

        WriteByte(0x48);
        Delay();
        uint8 byte3 = ReadByte();
        byte3 = byte3;

        Timer::Delay(50);
    }


//    WriteByte(0x60);      // 24 бита в калибровочный регистр
//    WriteByte(0x14);
//    WriteByte(0xF2);
//    WriteByte(0x44);
//    WriteByte(0x70);      // 24 бита в регистр смещения
//    WriteByte(0xAD);
//    WriteByte(0xE4);
//    WriteByte(0xBF);
}


bool ADC::DataReady()
{
    bool ready = HAL_GPIO_ReadPin(READY) == GPIO_PIN_RESET;

    static TimeMeterMS meter;

    if (meter.ElapsedTime() > 100)
    {
        meter.Reset();
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, ready ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    return ready;
}


float ADC::GetVoltage()
{
    WriteByte(0x38);

    float result = (float)((ReadByte() << 8) + ReadByte());

    return result;
}


void ADC::Reset()
{
//    HAL_GPIO_WritePin(PORT_RESET, PIN_RESET, GPIO_PIN_SET);

    HAL_Delay(1000);

//    HAL_GPIO_WritePin(PORT_RESET, PIN_RESET, GPIO_PIN_RESET);
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

        result <<= 1;

        if (HAL_GPIO_ReadPin(OUT) == GPIO_PIN_SET)
        {
            result |= 0x01;
        }

        PIN_CLK_SET;
    }

    return result;
}
