#include <iostream>

#include <netinet/ether.h>

#include "packetProcessor.h"

/* Utility Methods - Definition */
bool PacketProcessor::isIpv4(const struct pcap_pkthdr *pHeader, const u_char *pPacket) const
{
    if (pHeader->len < (ETHERNET_HEADER_LEN + MIN_IPv4_HEADER_LEN))
    {
        return false;
    }

    const ether_header *pEthernetHeader = reinterpret_cast<const ether_header *>(pPacket);
    return (ntohs(pEthernetHeader->ether_type) == ETHERTYPE_IP);
}

const ip *PacketProcessor::getIpv4Header(const u_char *pPacket) const
{
    return reinterpret_cast<const ip *>(pPacket + ETHERNET_HEADER_LEN);
}

int PacketProcessor::getIpv4Protocol(const ip *pIpHeader) const
{
    if (pIpHeader == nullptr)
    {
        std::cerr << "Invalid IP header instance" << std::endl;
        return -1;
    }

    return pIpHeader->ip_p;
}
