#ifndef __PCAP_DEVICE_H__
#define __PCAP_DEVICE_H__

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include <pcap.h>

#include "processor/packetProcessor.h"

using DeviceHandle = std::unique_ptr<pcap_t, decltype(&pcap_close)>;

class PcapDevice
{
private:
    /* Data Members */
    DeviceHandle deviceHandle;

    std::atomic<bool> keepRunning;
    std::thread captureTask;

    std::vector<std::shared_ptr<PacketProcessor>> processors;

    /* Local Utility Methods */
    void liveCapture(std::atomic<bool> &keepRunning);
    void processPacket(const struct pcap_pkthdr *pHeader, const u_char *pPacket);

    static void packetHandler(u_char *callback, const pcap_pkthdr *pHeader, const u_char *pPacket);

public:
    PcapDevice(pcap_t *pDeviceHandle);
    ~PcapDevice();

    /* Utility Methods */
    void startLiveCapture();
    void stopLiveCapture();

    void registerProcessor(std::shared_ptr<PacketProcessor> pProcessor);
    void deregisterProcessor(std::shared_ptr<PacketProcessor> pProcessor);
};

#endif // __PCAP_DEVICE_H__