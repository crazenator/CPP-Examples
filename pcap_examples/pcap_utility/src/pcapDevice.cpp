#include <algorithm>
#include <iostream>

#include "pcapDevice.h"

PcapDevice::PcapDevice(pcap_t *pDeviceHandle)
    : deviceHandle(pDeviceHandle, pcap_close),
      keepRunning(false)
{
}

PcapDevice::~PcapDevice()
{
    stopLiveCapture();
}

/* Utility Methods - Definition */
void PcapDevice::startLiveCapture()
{
    // Start capture task
    keepRunning.store(true);
    captureTask = std::thread(&PcapDevice::liveCapture, this, std::ref(keepRunning));
}

void PcapDevice::stopLiveCapture()
{
    // Signal the task to stop and wait till the task is stopped
    keepRunning.store(false);
    captureTask.join();
}

void PcapDevice::registerProcessor(std::shared_ptr<PacketProcessor> pProcessor)
{
    if (pProcessor == nullptr)
    {
        std::cerr << "Invalid processor instance provided to register" << std::endl;
        return;
    }

    // Check for duplicates
    if (std::find(processors.begin(), processors.end(), pProcessor) != processors.end())
    {
        std::cerr << "The processor instance already registered: "
                  << "processors=" << processors.size()
                  << std::endl;
        return;
    }

    processors.push_back(pProcessor);
}

void PcapDevice::deregisterProcessor(std::shared_ptr<PacketProcessor> pProcessor)
{
    if (pProcessor == nullptr)
    {
        std::cerr << "Invalid processor instance provided to deregister" << std::endl;
        return;
    }

    // Remove all possible instances of the processor
    processors.erase(std::remove(processors.begin(), processors.end(), pProcessor),
                     processors.end());
}

/* Local Utility Methods - Definition */
void PcapDevice::liveCapture(std::atomic<bool> &keepRunning)
{
    constexpr int PACKETS_TO_RECEIVE = 1;

    while (keepRunning.load())
    {
        pcap_dispatch(deviceHandle.get(), PACKETS_TO_RECEIVE, PcapDevice::packetHandler, reinterpret_cast<u_char *>(this));
    }
}

void PcapDevice::processPacket(const pcap_pkthdr *pHeader,
                               const u_char *pPacket)
{
    for (auto &pProcessor : processors)
    {
        pProcessor->process(pHeader, pPacket);
    }
}

void PcapDevice::packetHandler(u_char *userData,
                               const pcap_pkthdr *pHeader,
                               const u_char *pPacket)
{
    auto pPcapDevice = reinterpret_cast<PcapDevice *>(userData);
    pPcapDevice->processPacket(pHeader, pPacket);
}
