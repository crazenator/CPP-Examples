#ifndef __PACKET_PROCESSOR_H__
#define __PACKET_PROCESSOR_H__

#include <netinet/ip.h>

#include <pcap.h>

constexpr int ETHERNET_HEADER_LEN = 14;
constexpr int MIN_IPv4_HEADER_LEN = 20;

class PacketProcessor
{
public:
    virtual void process(const struct pcap_pkthdr *pHeader, const u_char *pPacket) = 0;
    virtual ~PacketProcessor() = default;

protected:
    /* Utility Methods */
    bool isIpv4(const struct pcap_pkthdr *pHeader, const u_char *pPacket) const;
    const ip *getIpv4Header(const u_char *pPacket) const;
    int getIpv4Protocol(const ip *pIpHeader) const;
};

#endif // __PACKET_PROCESSOR_H__