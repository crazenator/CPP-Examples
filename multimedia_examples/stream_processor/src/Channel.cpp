#include <iostream>

#include "Channel.hpp"

#include "input/InputFactory.hpp"
#include "emitter/EmitterFactory.hpp"

#include "processor/segmentor/Video.hpp"
#include "processor/segmentor/Audio.hpp"

Channel::Channel(const std::string &name, const std::string &uri, const std::string &target)
    : name(name), uri(uri), target(target)
{
}

Channel::~Channel()
{
    if (dispatcher)
    {
        // remove all stream processors
        dispatcher->unregisterAllProcessors();
    }

    if (inputSource)
    {
        // Close input source
        inputSource->close();
    }
}

/* === Private Functions === */
void Channel::initInputSource()
{
    InputType type;
    if (uri.starts_with("udp://") || uri.starts_with("srt://") || uri.starts_with("rtp://"))
    {
        type = InputType::Network;
    }
    else if (uri.starts_with("file://"))
    {
        type = InputType::File;
    }
    else
    {
        std::cerr << "URI format is not supported; URI=" << uri << std::endl;
        return;
    }

    inputSource = InputFactory::create(type, uri);
    if (inputSource)
    {
        inputSource->open(uri);
    }
}

void Channel::initDemuxer()
{
    // Get AVFormatContext from the input
    auto pFormatContext = inputSource->getFormatContext();
    if (pFormatContext == nullptr)
    {
        std::cerr << "Input source is not initialized properly" << std::endl;
        return;
    }

    // Instantiate demuxer for the channel
    demuxer = std::make_unique<Demuxer>(name, pFormatContext);
}

void Channel::initDispatcher()
{
    constexpr int SEGMENT_DURATION_MS = 4 * 1000;

    // Instantiate dispatcher for the channel
    dispatcher = std::make_unique<Dispatcher>();

    // Register stream processors
    // Video segmentor
    auto videoSegmentor = std::make_shared<Video>(SegmentMode::Hybrid, SEGMENT_DURATION_MS, emitter);
    dispatcher->registerProcessor(videoSegmentor);
    // Audio segmentor
    auto audioSegmentor = std::make_shared<Audio>(SegmentMode::Duration, SEGMENT_DURATION_MS, emitter);
    dispatcher->registerProcessor(audioSegmentor);
}

void Channel::initEmitter()
{
    std::string channelRoot = target.append("/").append(name);
    emitter = EmitterFactory::create(EmitterType::File, channelRoot);
}

/* === Public Functions === */
int Channel::initialize()
{
    // Initialize input source
    initInputSource();

    // Initialize emitter for media segments
    initEmitter();

    // Initialize demuxer
    initDemuxer();

    // Initialize dispatcher
    initDispatcher();

    return 0;
}

void Channel::ingest()
{
    while (1)
    {
        auto optPacket = inputSource->read();
        if (!optPacket.has_value())
        {
            std::cout << "Failed to read from input source " << uri << std::endl;
            continue;
        }

        // Convert packet to StreamChunk
        auto optStreamChunk = demuxer->extractChunk(optPacket.value().get());
        if (!optStreamChunk.has_value())
        {
            std::cout << "Failed to create stream chunk from packet" << std::endl;
            continue;
        }

        // Dispatch the stream chunk
        dispatcher->dispatch(optStreamChunk.value());
    }
}
