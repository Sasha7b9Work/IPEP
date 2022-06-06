#include "defines.h"
#include "Display/Zones.h"
#include "Display/Display.h"


void Zone::Clear()
{
    Rectangle(width, height).Fill(x, y, background);
}


void Zone::Send()
{
}


void ZoneFPS::Draw()
{
    Clear();

    string.Draw(x, y, Color::GRAY_10);

    Send();
}
