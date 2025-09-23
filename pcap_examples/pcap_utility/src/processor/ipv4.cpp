#include <iostream>
#include <string_view>

#include "ipv4.h"

void IPv4::process(const struct pcap_pkthdr *pHeader, const u_char *pPacket)
{
    if (isIpv4(pHeader, pPacket))
    {
        auto pIpv4Header = getIpv4Header(pPacket);

        std::cout << "##### IPv4 Packet #####" << std::endl;

        std::cout << "Src: " << getSource(pIpv4Header)
                  << " Dst: " << getDestination(pIpv4Header)
                  << std::endl;

        std::cout << "Options: " << hasOptions(pIpv4Header)
                  << " List: " << getOptions(pPacket).size()
                  << std::endl;
    }
}

constexpr int headerLenInBytes(int ip_hl) { return (ip_hl * 4); }

/* Local Utility Methods - Definition */
bool IPv4::hasOptions(const ip *pIpHeader) const
{
    if (pIpHeader == nullptr)
    {
        std::cerr << "Invalid IP header instance" << std::endl;
        return false;
    }

    return (headerLenInBytes(pIpHeader->ip_hl) > MIN_IPv4_HEADER_LEN);
}

std::vector<int> IPv4::getOptions(const u_char *pPacket) const
{
    std::vector<int> ipv4Options;

    auto pIpHeader = getIpv4Header(pPacket);
    if (pIpHeader == nullptr)
    {
        std::cerr << "Invalid IP header instance" << std::endl;
        return ipv4Options;
    }

    if (!hasOptions(pIpHeader))
    {
        return ipv4Options;
    }

    // Seek till IPv4 options in the packet
    auto pIpOptions = pPacket + ETHERNET_HEADER_LEN + MIN_IPv4_HEADER_LEN;
    auto ipOptionsLen = headerLenInBytes(pIpHeader->ip_hl) - MIN_IPv4_HEADER_LEN;

    // Traverse IPv4 options
    auto i = 0;
    while (i < ipOptionsLen)
    {
        uint8_t option = pIpOptions[i];
        ipv4Options.push_back(static_cast<int>(option));

        if (option == IPOPT_EOL) // End of list
        {
            break;
        }
        else if (option == IPOPT_NOOP) // No operation - 1 byte
        {
            ++i;
        }
        else // Multi-byte option
        {
            if ((i + 1) >= ipOptionsLen)
            {
                // Buffer overflow
                break;
            }

            // Fetch IPv4 option length
            uint8_t optionLen = pIpOptions[i + 1];
            i += optionLen;
        }
    }

    return ipv4Options;
}

std::string IPv4::getSource(const ip *pIpHeader) const
{
    if (pIpHeader == nullptr)
    {
        std::cerr << "Invalid IP header instance" << std::endl;
        return "";
    }

    return inet_ntoa(pIpHeader->ip_src);
}

std::string IPv4::getDestination(const ip *pIpHeader) const
{
    if (pIpHeader == nullptr)
    {
        std::cerr << "Invalid IP header instance" << std::endl;
        return "";
    }

    return inet_ntoa(pIpHeader->ip_dst);
}

bool IPv4::isMulticast(const ip *pIpHeader) const
{
    if (pIpHeader == nullptr)
    {
        std::cerr << "Invalid IP header instance" << std::endl;
        return "";
    }

    constexpr int minMulticast = 224;
    constexpr int maxMulticast = 239;

    auto dstIp = getDestination(pIpHeader);

    // Fetch first octate of the IPv4 address
    auto dotPosition = dstIp.find('.');
    if (dotPosition == std::string_view::npos)
        return false;

    int firstOctate = 0;
    try
    {
        // Convert first octate to integer
        firstOctate = std::stoi(dstIp.substr(0, dotPosition));
    }
    catch (const std::invalid_argument &invalidArg)
    {
        std::cerr << "Invalid first octate: " << invalidArg.what() << std::endl;
        return false;
    }

    return ((firstOctate >= minMulticast) &&
            (firstOctate <= maxMulticast));
}

bool IPv4::isIpSecPacket(const ip *pIpHeader) const
{
    return ((getIpv4Protocol(pIpHeader) == IPPROTO_AH) ||
            (getIpv4Protocol(pIpHeader) == IPPROTO_ESP));
}

bool IPv4::isIpTunnelPacket(const ip *pIpHeader) const
{
    return (getIpv4Protocol(pIpHeader) == IPPROTO_IPIP);
}
