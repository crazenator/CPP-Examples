#ifndef __PCAP_UTILITY_H__
#define __PCAP_UTILITY_H__

#include <pcap.h>

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "pcapPacket.h"

struct DeviceInfo_t
{
    std::string name;
    std::string description;
};
using DeviceInfo = DeviceInfo_t;

/* Declare expression for a unique pointer with custom delete method */
using DeviceHandle = std::unique_ptr<pcap_t, decltype(&pcap_close)>;

using PacketHandler = std::function<void(const PcapPacket &)>;

class PcapUtility
{
public:
    static std::vector<DeviceInfo> getDevices();
    static DeviceHandle openDevice(const DeviceInfo deviceInfo);
    static void receiveFromDevice(const DeviceHandle &deviceHandle, PacketHandler packetHandler);
};

#endif // __PCAP_UTILITY_H__
