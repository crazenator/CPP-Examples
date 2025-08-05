#include <iostream>

#include "pcapUtility.h"

void pcapCallback(u_char *callback, const pcap_pkthdr *pHeader, const u_char *pPacket)
{
    /* Typecast the shared pointer callback to packetHandler pointer */
    auto packetHandler = reinterpret_cast<PacketHandler *>(callback);
    if (packetHandler && *packetHandler)
    {
        /* Create an instance of the PcapPacket */
        PcapPacket pcapPacket(pHeader, pPacket);

        /* Invoke user callback */
        (*packetHandler)(pcapPacket);
    }
}

std::vector<DeviceInfo> PcapUtility::getDevices()
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

    /* Traverse the linked list of devices */
    pcap_if_t *pDevice = pDeviceList;
    while (pDevice)
    {
        std::cout << "Device: " << pDevice->name << " " << pDevice->description << std::endl;
        devicesInfo.push_back({pDevice->name,
                               pDevice->description ? pDevice->description : "No description available"});
        pDevice = pDevice->next;
    }

    return devicesInfo;
}

DeviceHandle PcapUtility::openDevice(const DeviceInfo deviceInfo)
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
    }

    return DeviceHandle(pDeviceHandle, pcap_close);
}

void PcapUtility::receiveFromDevice(const DeviceHandle &deviceHandle,
                                    PacketHandler packetHandler)
{
    constexpr int PACKETS_TO_RECEIVE = 1;

    /* Wrap the packetHandler as shared pointer so it can be type casted */
    auto callback = std::make_shared<PacketHandler>(packetHandler);

    pcap_dispatch(deviceHandle.get(), PACKETS_TO_RECEIVE, pcapCallback,
                  reinterpret_cast<u_char *>(callback.get()));
}
