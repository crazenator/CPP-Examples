#include <algorithm>
#include <iostream>

#include "Dispatcher.hpp"

/* === Public Functions === */
void Dispatcher::registerProcessor(std::shared_ptr<StreamProcessor> processor)
{
    std::unique_lock lock(registryMutex);

    // Register stream processor
    processorRegistry[processor->supportedType()].push_back(processor);
}

void Dispatcher::unregisterProcessor(std::shared_ptr<StreamProcessor> processor)
{
    std::unique_lock lock(registryMutex);

    // Locate processors for required stream type
    auto processorsIt = processorRegistry.find(processor->supportedType());
    if (processorsIt == processorRegistry.end())
    {
        std::cout << "No processor registered for the given stream type" << std::endl;
        return;
    }
    auto &processors = processorsIt->second;

    // Remove the stream processor
    processors.erase(std::remove_if(processors.begin(), processors.end(),
                                    [&](const std::shared_ptr<StreamProcessor> &refProcessor)
                                    {
                                        return refProcessor.get() == processor.get();
                                    }),
                     processors.end());
}

void Dispatcher::unregisterAllProcessors()
{
    // Traverse all entries in processor registry
    for (auto &entry : processorRegistry)
    {
        // Traverse all processors
        for (auto &processor : entry.second)
        {
            // Unregister the processor
            unregisterProcessor(processor);
        }
    }
}

std::vector<std::shared_ptr<StreamProcessor>> Dispatcher::getRegisteredProcessors(const StreamType type) const
{
    auto processorsIt = processorRegistry.find(type);
    if (processorsIt == processorRegistry.end())
    {
        std::cout << "No processor registered for the given stream type" << std::endl;
        return {};
    }

    return processorsIt->second;
}

void Dispatcher::dispatch(const StreamChunk &chunk) const
{
    std::shared_lock lock(registryMutex);

    auto processorsIt = processorRegistry.find(chunk.type);
    if (processorsIt == processorRegistry.end())
    {
        std::cout << "No processor registered for the given stream type" << std::endl;
        return;
    }

    // Dispatch the stream chunk to registered processors
    for (auto &processor : processorsIt->second)
    {
        processor->onChunk(chunk);
    }
}
