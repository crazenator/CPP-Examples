#include "input/NetworkInput.hpp"

bool NetworkInput::open(const std::string &uri)
{
    constexpr std::string_view INPUT_TIMEOUT = "5000000";

    AVDictionary *pOpts = nullptr;
    av_dict_set(&pOpts, "timeout", INPUT_TIMEOUT.data(), 0);

    return (avformat_open_input(&pFormatContext, uri.c_str(), nullptr, &pOpts) == 0) &&
           (avformat_find_stream_info(pFormatContext, nullptr) >= 0);
}

void NetworkInput::close()
{
    if (pFormatContext != nullptr)
    {
        avformat_close_input(&pFormatContext);
    }
}

AVFormatContext *NetworkInput::getFormatContext()
{
    return pFormatContext;
}

std::optional<AVPacketPtr> NetworkInput::read()
{
    auto packet = makeAVPacketPtr();
    if (av_read_frame(pFormatContext, packet.get()) >= 0)
    {
        return packet;
    }
    return std::nullopt;
}
