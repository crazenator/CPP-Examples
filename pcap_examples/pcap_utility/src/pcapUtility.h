#ifndef __PCAP_UTILITY_H__
#define __PCAP_UTILITY_H__

#include <memory>
#include <vector>

#include "pcapDevice.h"

struct DeviceInfo_t
{
    std::string name;
    std::string description;
};
using DeviceInfo = DeviceInfo_t;

class PcapUtility
{
private:
    PcapUtility() = default;
    PcapUtility(const PcapUtility &) = delete;
    PcapUtility &operator=(const PcapUtility &) = delete;

public:
    static PcapUtility &getInstance()
    {
        static PcapUtility instance;
        return instance;
    }

    /* Utility Methods */
    std::vector<DeviceInfo_t> getDevicesInfo();
    std::unique_ptr<PcapDevice> openDevice(const DeviceInfo_t deviceInfo);
};

#endif // __PCAP_UTILITY_H__