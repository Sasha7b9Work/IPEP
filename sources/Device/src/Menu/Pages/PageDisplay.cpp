// 2022/05/05 13:14:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"
#include "Settings/Settings.h"


extern const DPage pageMain;
extern const DPage pageDisplay;
extern const DPage pageMeasures;


DEF_CHOICE_2( chPressure,
    "��������",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Pressure],
    "����", "���"
)

DEF_CHOICE_2(chIllumination,
    "������������",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Illumination],
    "����", "���"
)

DEF_CHOICE_2(chVelocity,
    "��������",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Velocity],
    "����", "���"
)

DEF_CHOICE_2(chTemperature,
    "�����������",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Temperature],
    "����", "���"
)

DEF_CHOICE_2(chHumidity,
    "���������",
    pageMeasures,
    gset.display.show_measure[TypeMeasure::Humidity],
    "����", "���"
)

static void CloseMeasures()
{
    PageDisplay::PageMeasures::self->Close();
};

DEF_BUTTN( bCloseMeasures,
    "�������",
    pageMeasures,
    CloseMeasures
)

DEF_PAGE_6( pageMeasures,
    "���������",
    pageDisplay,
    chPressure,
    chIllumination,
    chVelocity,
    chTemperature,
    chHumidity,
    bCloseMeasures
)


void ClosePageDisplay()
{
    PageDisplay::self->Close();
}

DEF_BUTTN( bClosePageDisplay,
    "�������",
    pageDisplay,
    ClosePageDisplay
)

DEF_PAGE_2(pageDisplay,
    "�������",
    pageMain,
    pageMeasures,
    bClosePageDisplay
)

const Page * const PageDisplay::self = (const Page *)&pageDisplay;
const Page * const PageDisplay::PageMeasures::self = (const Page *)&pageMeasures;
