#include "Audio.hpp"

Audio::Audio(SegmentMode mode, uint64_t durationMs, std::shared_ptr<Emitter> emitter)
    : Segmentor(mode, durationMs, emitter)
{
}

/* === Public Functions === */
StreamType Audio::supportedType() const
{
    return StreamType::Audio;
}
