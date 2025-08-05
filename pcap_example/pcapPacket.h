#ifndef __PCAP_PACKET_H__
#define __PCAP_PACKET_H__

#include <pcap.h>

#include <string>

class PcapPacket
{
private:
    const pcap_pkthdr *pHeader;
    const u_char *pPacket;

public:
    PcapPacket(const pcap_pkthdr *pHeader, const u_char *pPacket);
    ~PcapPacket() = default;

    int getPacketSize() const;

    /* IPv4 Functions */
    bool isIPv4Packet() const;
    bool hasIPv4Options() const;
    int getIPv4PacketLength() const;
    int getL4Protocol() const;
    std::string getIPv4Source() const;
    std::string getIPv4Destination() const;
};

#endif // __PCAP_PACKET_H__