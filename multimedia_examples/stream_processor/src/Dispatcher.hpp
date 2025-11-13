#pragma once

#include <unordered_map>
#include <vector>

#include <memory>
#include <mutex>
#include <shared_mutex>

#include "Demuxer.hpp"
#include "processor/StreamProcessor.hpp"

class Dispatcher
{
private:
    mutable std::shared_mutex registryMutex;
    std::unordered_map<StreamType, std::vector<std::shared_ptr<StreamProcessor>>> processorRegistry;

public:
    void registerProcessor(std::shared_ptr<StreamProcessor> processor);
    void unregisterProcessor(std::shared_ptr<StreamProcessor> processor);
    void unregisterAllProcessors();

    std::vector<std::shared_ptr<StreamProcessor>> getRegisteredProcessors(const StreamType type) const;
    void dispatch(const StreamChunk &chunk) const;
};
