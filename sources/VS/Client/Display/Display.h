// 2022/04/29 16:44:45 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"
#define WIN32_LEAN_AND_MEAN
#include <wx/wx.h>


struct TypeMeasure
{
    enum E
    {
        Pressure,           // ��������
        Illumination,       // ������������
        Velocity,           // ��������
        Temperature,        // �����������
        Humidity,           // ���������
        Count
    };

    static pchar GetTitle(TypeMeasure::E);
    static pchar GetUnits(TypeMeasure::E);
};


namespace Display
{
    static const int WIDTH = 320;
    static const int HEIGHT = 180;

    extern wxBitmap bitmap;

    void Update();

    void SetMeasure(TypeMeasure::E, float value);

    void SwitchMeasure(TypeMeasure::E);

    void Reset();
}
