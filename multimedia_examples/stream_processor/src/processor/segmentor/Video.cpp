#include "Video.hpp"

Video::Video(SegmentMode mode, uint64_t durationMs, std::shared_ptr<Emitter> emitter)
    : Segmentor(mode, durationMs, emitter)
{
}

/* === Public Functions === */
StreamType Video::supportedType() const
{
    return StreamType::Video;
}
