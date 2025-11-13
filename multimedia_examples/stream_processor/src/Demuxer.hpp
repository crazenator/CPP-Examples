#pragma once

#include <map>
#include <vector>

#include <string>
#include <optional>

extern "C"
{
#include <libavformat/avformat.h>
}

enum class StreamType
{
    Video,
    Audio,
    Data,
    Subtitle,
    Unknown
};

struct StreamChunk
{
    int pid;                   // PID from MPEG-TS
    StreamType type;           // Video, Audio, Subtitle
    uint64_t timestamp;        // PTS or DTS in milliseconds
    bool isKeyFrame;           // Indicate if the data has key frame
    std::vector<uint8_t> data; // Raw payload from AVPacket

    std::string channel;
};

class Demuxer
{
private:
    std::string channel;
    std::map<int, StreamType> pidToStream;

public:
    explicit Demuxer(const std::string &channel, const AVFormatContext *pFormatContext);

    StreamType getStreamType(int pid) const;
    std::optional<StreamChunk> extractChunk(const AVPacket *pAVPacket);
};
