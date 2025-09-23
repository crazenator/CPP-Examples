#ifndef __UDP_PACKET_PROCESSOR_H__
#define __UDP_PACKET_PROCESSOR_H__

#include <netinet/udp.h>

#include "packetProcessor.h"

class UDP : public PacketProcessor
{
private:
    /* Local Utility Methods */
    bool isUdp(const struct pcap_pkthdr *pHeader, const u_char *pPacket) const;

public:
    void process(const struct pcap_pkthdr *pHeader, const u_char *pPacket);
};

#endif // __UDP_PACKET_PROCESSOR_H__