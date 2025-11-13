#pragma once

#include <cstdint>

extern "C"
{
#include <libavcodec/avcodec.h>
}

class StreamProcessor
{
public:
    virtual ~StreamProcessor() = default;
    virtual StreamType supportedType() const = 0;
    virtual void onChunk(const StreamChunk &chunk) = 0;
};
