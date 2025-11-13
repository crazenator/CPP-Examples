#pragma once

#include <vector>

#include "Demuxer.hpp"

class Emitter
{
public:
    virtual ~Emitter() = default;

    virtual void emit(uint64_t startTs, const std::vector<StreamChunk> &chunks) = 0;
};
