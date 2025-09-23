#include <csignal>
#include <iostream>

#include "pcapUtility.h"

using namespace std;

volatile bool keepRunning = true;
void signalHandler(int signal)
{
    if (signal == SIGINT)
    {
        keepRunning = false;
        return;
    }
    cout << "Received " << signal << ", ignoring..." << endl;
}

int main()
{
    /* Register signal handler */
    signal(SIGINT, signalHandler);

    int index = 0;
    auto devicesInfo = PcapUtility::getDevices();
    if (devicesInfo.empty())
    {
        return 1;
    }

    /* Traverse devices information */
    for (auto deviceInfo : devicesInfo)
    {
        cout << index++ << ": "
             << deviceInfo.name << " | " << deviceInfo.description << endl;
    }

    cout << "Select device index: ";
    cin >> index;
    if ((index < 0) || (index >= devicesInfo.size()))
    {
        cerr << "Invalid index selected" << endl;
        return 1;
    }

    /* Open selected device */
    auto deviceHandle = PcapUtility::openDevice(devicesInfo.at(index));
    if (deviceHandle == nullptr)
    {
        return 1;
    }

    cout << "Capturing packets on " << devicesInfo.at(index).name << endl;
    cout << "Press Ctrl+C to stop" << endl;

    while (keepRunning)
    {
        /* Capture packet(s) from opened device */
        PcapUtility::receiveFromDevice(deviceHandle,
                                       [](const PcapPacket &packet)
                                       {
                                           /* Access constant methods ONLY since the object is constant */
                                           if (packet.isIPv4Packet())
                                           {
                                               cout << "Received IPv4 packet" << endl;
                                               cout << "Contains IPv4 Options: " << packet.hasIPv4Options() << endl;
                                               cout << "IPv4 Packet Length: " << packet.getIPv4PacketLength() << endl;
                                               cout << "IPv4 Source: " << packet.getIPv4Source()
                                                    << " Destination: " << packet.getIPv4Destination() << endl;
                                               cout << "L4 Protocol: " << packet.getL4Protocol() << endl;
                                           }
                                           else
                                           {
                                               cout << "Unsupported packet received" << endl;
                                           }
                                       });
    }

    return 0;
}
