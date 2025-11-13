#pragma once

#include <memory>
#include <optional>
#include <string>

extern "C"
{
#include <libavformat/avformat.h>
}

using AVPacketPtr = std::unique_ptr<AVPacket, void (*)(AVPacket *)>;

class InputSource
{
protected:
    AVFormatContext *pFormatContext = nullptr;

    inline AVPacketPtr makeAVPacketPtr()
    {
        AVPacket *pAVPacket = av_packet_alloc();
        return AVPacketPtr(pAVPacket,
                           [](AVPacket *pAVPacket)
                           {
                               av_packet_unref(pAVPacket);
                               av_packet_free(&pAVPacket);
                           });
    }

public:
    virtual bool open(const std::string &uri) = 0;
    virtual void close() = 0;
    virtual AVFormatContext *getFormatContext() = 0;
    virtual std::optional<AVPacketPtr> read() = 0;

    virtual ~InputSource()
    {
        if (pFormatContext)
        {
            avformat_close_input(&pFormatContext);
        }
    }
};
