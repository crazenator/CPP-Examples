#ifndef __IP_PACKET_PROCESSOR_H__
#define __IP_PACKET_PROCESSOR_H__

#include <vector>

#include "packetProcessor.h"

/**
 * https://en.wikipedia.org/wiki/IPv4
 * https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers
 */

class IPv4 : public PacketProcessor
{
private:
    /* Local Utility Methods */
    bool hasOptions(const ip *pIpHeader) const;
    std::vector<int> getOptions(const u_char *pPacket) const;

    std::string getSource(const ip *pIpHeader) const;
    std::string getDestination(const ip *pIpHeader) const;
    bool isMulticast(const ip *pIpHeader) const;

    bool isIpSecPacket(const ip *pIpHeader) const;
    bool isIpTunnelPacket(const ip *pIpHeader) const;

public:
    void process(const struct pcap_pkthdr *pHeader, const u_char *pPacket);
};

#endif // __IP_PACKET_PROCESSOR_H__