// 2022/6/7 12:28:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Barrier
{
    void Init();

    // ����������� �� ��������� � �������� ��������� ��� �������
    void Switch();

    bool IsOpened();

    // ������ ������� ����� ���������� ������������
    uint TimeElapsed();
}
