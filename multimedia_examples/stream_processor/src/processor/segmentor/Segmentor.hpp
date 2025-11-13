#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "Demuxer.hpp"

#include "emitter/Emitter.hpp"
#include "processor/StreamProcessor.hpp"

enum class SegmentMode
{
    Duration, // Fixed duration (ms) of segments
    KeyFrame, // Segments aligned with key frame, applies to video ONLY
    Hybrid    // Segments aligned with key frame within the duration (ms), applies to video ONLY
};

constexpr uint64_t DEFAULT_SEGMENT_DURATION_MS = 4 * 1000;

class Segmentor : public StreamProcessor
{
private:
    bool shouldEmit(const StreamChunk &chunk);

protected:
    std::shared_ptr<Emitter> emitter;

    SegmentMode mode;
    uint64_t durationMs;
    uint64_t startTs;

    std::vector<StreamChunk> chunks;

    virtual void emitSegment();

    virtual StreamType supportedType() const = 0;

public:
    explicit Segmentor(SegmentMode mode,
                       uint64_t durationMs = DEFAULT_SEGMENT_DURATION_MS,
                       std::shared_ptr<Emitter> emitter = nullptr);

    void onChunk(const StreamChunk &chunk) override;
};
