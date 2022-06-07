// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Device.h"


/*
* B8, B9 - мотор
* B6 - сброс напряжения
* 
* АЦП:
* B4 - DOUT (приём данных из АЦП)
* B3 - DRDY (ready данных)
* A15 - CLK
* A12 - DIN (запись данных в АЦП)
*/



int main(void)
{
    Device::Init();

    while (true)
    {
        Device::Update();
    }
}
