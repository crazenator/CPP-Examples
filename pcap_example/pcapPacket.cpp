#include <arpa/inet.h>

#include <netinet/ether.h>
#include <netinet/ip.h>

#include "pcapPacket.h"

constexpr int ETHERNET_HEADER_LEN = 14;
constexpr int MIN_IPv4_HEADER_LEN = 20;
constexpr int MIN_IPv4_AND_ETHERNET_LEN = ETHERNET_HEADER_LEN + MIN_IPv4_HEADER_LEN;

PcapPacket::PcapPacket(const pcap_pkthdr *pHeader, const u_char *pPacket)
    : pHeader(pHeader), pPacket(pPacket)
{
}

int PcapPacket::getPacketSize() const
{
    return pHeader->len;
}

/* IPv4 Functions */
const ip *getIPv4Header(const u_char *pPacket)
{
    return reinterpret_cast<const ip *>(pPacket + ETHERNET_HEADER_LEN);
}

bool PcapPacket::isIPv4Packet() const
{
    const ether_header *pEthernetHeader = reinterpret_cast<const ether_header *>(pPacket);
    return (ntohs(pEthernetHeader->ether_type) == ETHERTYPE_IP);
}

bool PcapPacket::hasIPv4Options() const
{
    if (pHeader->len < MIN_IPv4_AND_ETHERNET_LEN)
        return false;

    const ip *pIpHeader = getIPv4Header(pPacket);
    return ((pIpHeader->ip_hl * 4) > MIN_IPv4_HEADER_LEN);
}

int PcapPacket::getIPv4PacketLength() const
{
    if (pHeader->len < MIN_IPv4_AND_ETHERNET_LEN)
        return 0;

    const ip *pIpHeader = getIPv4Header(pPacket);
    return ntohs(pIpHeader->ip_len);
}

int PcapPacket::getL4Protocol() const
{
    if (pHeader->len < MIN_IPv4_AND_ETHERNET_LEN)
        return 0;

    const ip *pIpHeader = getIPv4Header(pPacket);
    return pIpHeader->ip_p;
}

std::string PcapPacket::getIPv4Source() const
{
    if (pHeader->len < MIN_IPv4_AND_ETHERNET_LEN)
        return "";

    const ip *pIpHeader = getIPv4Header(pPacket);
    return inet_ntoa(pIpHeader->ip_src);
}

std::string PcapPacket::getIPv4Destination() const
{
    if (pHeader->len < MIN_IPv4_AND_ETHERNET_LEN)
        return "";

    const ip *pIpHeader = getIPv4Header(pPacket);
    return inet_ntoa(pIpHeader->ip_dst);
}
