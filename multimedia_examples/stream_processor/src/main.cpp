#include <iostream>
#include <map>
#include <memory>

extern "C"
{
#include <libavformat/avformat.h>
}

#include "Channel.hpp"

void initializeAV()
{
    // Set log level
    av_log_set_level(AV_LOG_ERROR);
}

int main()
{
    initializeAV();

    std::string channelName = "test";
    std::string uri = "file:/";
    std::string target = "./channels";

    // Instantiate channel
    std::unique_ptr<Channel> channel = std::make_unique<Channel>(channelName, uri, target);
    channel->initialize();

    // Start ingesting
    channel->ingest();
}
