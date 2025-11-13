#include "Segmentor.hpp"

Segmentor::Segmentor(SegmentMode mode, uint64_t durationMs, std::shared_ptr<Emitter> emitter)
    : mode(mode), durationMs(durationMs), emitter(emitter)
{
    startTs = 0;
}

/* === Protected Functions === */
bool Segmentor::shouldEmit(const StreamChunk &chunk)
{
    switch (mode)
    {
    case SegmentMode::Duration:
        return (chunk.timestamp - startTs) >= durationMs;
    case SegmentMode::KeyFrame:
        return chunk.isKeyFrame;
    case SegmentMode::Hybrid:
        return ((chunk.timestamp - startTs) >= durationMs) &&
               (chunk.isKeyFrame);

    default:
        return true;
    }
}

void Segmentor::emitSegment()
{
    if (emitter)
    {
        // Emit chunks as a segment
        emitter->emit(startTs, chunks);
    }
}

/* === Public Functions === */
void Segmentor::onChunk(const StreamChunk &chunk)
{
    if (chunks.empty())
    {
        // Start of the segment
        startTs = chunk.timestamp;
    }

    chunks.push_back(chunk);

    if (shouldEmit(chunk))
    {
        // Emit the segment
        emitSegment();

        // Reset segment chunks and timestamp
        chunks.clear();
        startTs = chunk.timestamp;
    }
}
