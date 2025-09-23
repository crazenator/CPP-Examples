#include <iostream>

#include "tcp.h"

void TCP::process(const struct pcap_pkthdr *pHeader, const u_char *pPacket)
{
    if (isTcp(pHeader, pPacket))
    {
        std::cout << "##### TCP Packet #####" << std::endl;
    }
}

/* Local Utility Methods - Definition */
bool TCP::isTcp(const struct pcap_pkthdr *pHeader, const u_char *pPacket) const
{
    if (!isIpv4(pHeader, pPacket))
    {
        return false;
    }

    auto ipv4Header = getIpv4Header(pPacket);
    return (getIpv4Protocol(ipv4Header) == IPPROTO_TCP);
}
