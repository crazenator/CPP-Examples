#pragma once

#include "Segmentor.hpp"

class Video : public Segmentor
{
public:
    explicit Video(SegmentMode mode,
                   uint64_t durationMs = DEFAULT_SEGMENT_DURATION_MS,
                   std::shared_ptr<Emitter> emitter = nullptr);

    StreamType supportedType() const override;
};
