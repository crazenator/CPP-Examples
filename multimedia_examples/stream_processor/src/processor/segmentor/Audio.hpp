#pragma once

#include "Segmentor.hpp"

class Audio : public Segmentor
{
public:
    explicit Audio(SegmentMode mode,
                   uint64_t durationMs = DEFAULT_SEGMENT_DURATION_MS,
                   std::shared_ptr<Emitter> emitter = nullptr);

    StreamType supportedType() const override;
};
