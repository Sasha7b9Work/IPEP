// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "Device.h"


/*
* B8, B9 - �����
* B6 - ����� ����������
* 
* ���:
* B4 - DOUT (���� ������ �� ���)
* B3 - DRDY (ready ������)
* A15 - CLK
* A12 - DIN (������ ������ � ���)
*/



int main(void)
{
    Device::Init();

    while (true)
    {
        Device::Update();
    }
}
