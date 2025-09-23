#ifndef __TCP_PACKET_PROCESSOR_H__
#define __TCP_PACKET_PROCESSOR_H__

#include <netinet/tcp.h>

#include "packetProcessor.h"

class TCP : public PacketProcessor
{
private:
    /* Local Utility Methods */
    bool isTcp(const struct pcap_pkthdr *pHeader, const u_char *pPacket) const;

public:
    void process(const struct pcap_pkthdr *pHeader, const u_char *pPacket);
};

#endif // __TCP_PACKET_PROCESSOR_H__