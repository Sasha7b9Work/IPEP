// Sasha7b9@tut.by (c)
#include "defines.h"
#include "Hardware/InterCom.h"
#include "Hardware/CDC/CDC.h"
#include "Display/Display.h"
#include "Utils/Text/String.h"
#include "Utils/Buffer.h"
#include "Utils/Math.h"
#include <cstdio>


#ifdef GUI
    #include "Hardware/LAN/ClientTCP.h"
#endif


namespace InterCom
{
}


void InterCom::Send(float value)
{
    char message[32];

    sprintf(message, "%f", value);

    CDC::Transmit(message, (int)std::strlen(message) + 1);

#ifdef GUI

    ClientTCP::Transmit(data.Data(), 12);

#endif
}
