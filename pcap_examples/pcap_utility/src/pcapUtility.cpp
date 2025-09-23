#include <iostream>

#include <memory>

#include <pcap.h>

#include "pcapUtility.h"

/* Utility Methods - Definition */
std::vector<DeviceInfo_t> PcapUtility::getDevicesInfo()
{
    char errBuffer[PCAP_ERRBUF_SIZE];

    pcap_if_t *pDeviceList;

    /* Define unique pointer with custom delete method */
    std::unique_ptr<pcap_if_t, decltype(&pcap_freealldevs)> devices(pDeviceList, pcap_freealldevs);

    std::vector<DeviceInfo> devicesInfo;

    /* Find all devices */
    if (pcap_findalldevs(&pDeviceList, errBuffer) == -1)
    {
        std::cerr << "Failed to find devices: " << errBuffer << std::endl;
        return devicesInfo;
    }

    /* Traverse the linked list of devices and populate the devicesInfo */
    pcap_if_t *pDevice = pDeviceList;
    while (pDevice)
    {
        devicesInfo.push_back({pDevice->name,
                               pDevice->description ? pDevice->description : "No description available"});
        pDevice = pDevice->next;
    }

    return devicesInfo;
}

std::unique_ptr<PcapDevice> PcapUtility::openDevice(const DeviceInfo_t deviceInfo)
{
    constexpr int PROMISCUOUS_MODE = 1;
    constexpr int PACKET_TIMEOUT_MS = 1 * 1000;

    char errBuffer[PCAP_ERRBUF_SIZE];
    pcap_t *pDeviceHandle = pcap_open_live(deviceInfo.name.c_str(),
                                           BUFSIZ, PROMISCUOUS_MODE, PACKET_TIMEOUT_MS,
                                           errBuffer);
    if (pDeviceHandle == nullptr)
    {
        std::cerr << "Failed to open device " << deviceInfo.name << ": "
                  << errBuffer << std::endl;

        return nullptr;
    }

    return std::make_unique<PcapDevice>(pDeviceHandle);
}
