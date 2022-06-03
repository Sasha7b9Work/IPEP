// 2022/05/05 14:53:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Pages.h"


extern const DPage pageHC12;
extern const DPage pageMain;


void ClosePageHC12()
{
    PageHC12::self->Close();
}

DEF_BUTTN( bClosePageHC12,
    "�������",
    pageHC12,
    ClosePageHC12
);

DEF_PAGE_1( pageHC12,
    "HC12",
    pageMain,
    bClosePageHC12
)

const Page *const PageHC12::self = (const Page *)&pageHC12;
