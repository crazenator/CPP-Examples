#include <algorithm>
#include <chrono>
#include <csignal>
#include <iostream>

#include "processor/ipv4.h"
#include "processor/tcp.h"
#include "processor/udp.h"

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

    auto devicesInfo = PcapUtility::getInstance().getDevicesInfo();
    for (auto deviceInfo : devicesInfo)
    {
        cout << deviceInfo.name << ": " << deviceInfo.description << endl;
    }

    // Fetch the desired device
    constexpr string_view targetDeviceName("any");
    auto targetDeviceInfoIt = find_if(devicesInfo.begin(), devicesInfo.end(),
                                      [&](const DeviceInfo &deviceInfo)
                                      {
                                          return (deviceInfo.name == targetDeviceName);
                                      });
    if (targetDeviceInfoIt == devicesInfo.end())
    {
        cerr << "Failed to find target device " << targetDeviceName << " in available devices" << endl;
        return 1;
    }

    // Open desired device
    auto targetDevice = PcapUtility::getInstance().openDevice(*targetDeviceInfoIt);
    if (targetDevice == nullptr)
    {
        return 1;
    }

    // Register packet processor(s)
    auto ipv4 = make_shared<IPv4>();
    targetDevice.get()->registerProcessor(ipv4);
    auto tcp = make_shared<TCP>();
    targetDevice.get()->registerProcessor(tcp);
    auto udp = make_shared<UDP>();
    targetDevice.get()->registerProcessor(udp);

    // Start live capture on desired device
    targetDevice.get()->startLiveCapture();

    while (keepRunning)
    {
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Clean-up for shutdown
    targetDevice.get()->stopLiveCapture();
    targetDevice.get()->deregisterProcessor(ipv4);

    return 0;
}
