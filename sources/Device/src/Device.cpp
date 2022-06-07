// 2022/04/27 11:48:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/CDC/CDC.h"
#include "Hardware/Timer.h"
#include "Hardware/InterCom.h"
#include "Modules/ADC.h"


void Device::Init()
{
    HAL::Init();

    ADC::Init();
}


void Device::Update()
{
    static TimeMeterMS meter;

    if (meter.ElapsedTime() > 1000)
    {
        meter.Reset();

        InterCom::Send(1.0f);
    }
}
