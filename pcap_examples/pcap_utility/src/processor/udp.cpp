#include <iostream>

#include "udp.h"

void UDP::process(const struct pcap_pkthdr *pHeader, const u_char *pPacket)
{
    if (isUdp(pHeader, pPacket))
    {
        std::cout << "##### UDP Packet #####" << std::endl;
    }
}

/* Local Utility Methods - Definition */
bool UDP::isUdp(const struct pcap_pkthdr *pHeader, const u_char *pPacket) const
{
    if (!isIpv4(pHeader, pPacket))
    {
        return false;
    }

    auto ipv4Header = getIpv4Header(pPacket);
    return (getIpv4Protocol(ipv4Header) == IPPROTO_UDP);
}
