// 2022/05/04 14:41:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/LAN/ServerTCP.h"
#include "Hardware/LAN/libnet/netserver.h"
#include "Hardware/LAN/libnet/netpacket.h"
#include "Utils/Buffer.h"
#include "Utils/Math.h"
#include "Display/Display.h"
#include "Hardware/Timer.h"


namespace ServerTCP
{
    net__::netserver server(2);

    sock_t socket = -1;

    TimeMeterMS meter;

    size_t OnReceiveData(net__::netpacket *, void *);

    size_t OnConnection(sock_t, void *);

    void ProcessData(Buffer<uint8, 1024> &);
}


void ServerTCP::Open(uint16 port)
{
    Close();

    socket = server.openPort(port);

    server.setConnectCB(OnConnection, nullptr);
}


bool ServerTCP::Opened()
{
    return !server.isClosed(socket);
}


void ServerTCP::Close()
{
    if (!Opened())
    {
        return;
    }

    server.closePort();
}


size_t ServerTCP::OnReceiveData(net__::netpacket *packet, void *)
{
    static Buffer<uint8, 1024> buffer;

    size_t num_bytes = packet->get_maxsize();

    buffer.Append(packet->get_ptr(), num_bytes);

    while (buffer.Size() >= 12)
    {
        ProcessData(buffer);
    }

    meter.Reset();

    return num_bytes;
}


void ServerTCP::ProcessData(Buffer<uint8, 1024> &data)
{
    while (data.Size() >= 12 && !(data[0] == 'A' && data[1] == 'B' && data[2] == 'C'))
    {
        data.Front();
    }

    if (data.Size() < 12)
    {
        return;
    }

    uint hash = 0;

    std::memcpy(&hash, &data[3], 4);

    if (hash == Math::CalculateHash(&data[7], 5))
    {
        float value = 0.0f;
        std::memcpy(&value, &data[8], 4);

        Display::SetMeasure((TypeMeasure::E)data[7], value);
    }

    data.RemoveFront(12);
}


size_t ServerTCP::OnConnection(sock_t sock, void *)
{
    server.setConPktCB(sock, OnReceiveData, nullptr);

    return 0;
}


void ServerTCP::Update()
{
    server.run();

    if (meter.ElapsedTime() > 4000)
    {
        Display::Reset();
    }
}
