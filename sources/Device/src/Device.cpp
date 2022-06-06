// 2022/04/27 11:48:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Device.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/CDC/CDC.h"
#include "Hardware/Timer.h"
#include "Hardware/InterCom.h"
#include "Display/Display.h"
#include "Hardware/Keyboard.h"


void Device::Init()
{
    HAL::Init();

    Keyboard::Init();
}


void Device::Update()
{
    Keyboard::Update();

    Display::Update();
}