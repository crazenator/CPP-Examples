#include "input/FileInput.hpp"

bool FileInput::open(const std::string &uri)
{
    // Open input file stream and validate the stream information
    return (avformat_open_input(&pFormatContext, uri.c_str(), nullptr, nullptr) == 0) &&
           (avformat_find_stream_info(pFormatContext, nullptr) >= 0);
}

void FileInput::close()
{
    if (pFormatContext != nullptr)
    {
        avformat_close_input(&pFormatContext);
    }
}

AVFormatContext *FileInput::getFormatContext()
{
    return pFormatContext;
}

std::optional<AVPacketPtr> FileInput::read()
{
    auto packet = makeAVPacketPtr();
    if (av_read_frame(pFormatContext, packet.get()) >= 0)
    {
        return packet;
    }
    return std::nullopt;
}