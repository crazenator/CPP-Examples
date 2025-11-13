#include <iostream>

#include "Demuxer.hpp"

Demuxer::Demuxer(const std::string &channel, const AVFormatContext *pFormatContext) : channel(channel)
{
    if (pFormatContext == nullptr)
    {
        std::cerr << "Invalid AV format context; make sure that the input source is open" << std::endl;
        return;
    }

    // Traverse the programs and stream information
    for (size_t p = 0; p < pFormatContext->nb_programs; p++)
    {
        auto pAVProgram = pFormatContext->programs[p];
        for (size_t s = 0; s < pAVProgram->nb_stream_indexes; s++)
        {
            auto pAVStream = pFormatContext->streams[pAVProgram->stream_index[s]];

            switch (pAVStream->codecpar->codec_type)
            {
            case AVMEDIA_TYPE_AUDIO:
                pidToStream[pAVStream->id] = StreamType::Audio;
                break;
            case AVMEDIA_TYPE_VIDEO:
                pidToStream[pAVStream->id] = StreamType::Video;
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                pidToStream[pAVStream->id] = StreamType::Subtitle;
                break;
            case AVMEDIA_TYPE_DATA:
                pidToStream[pAVStream->id] = StreamType::Data;
                break;

            default:
                pidToStream[pAVStream->id] = StreamType::Unknown;
                break;
            }
        }
    }
}

/* === Public Functions === */
StreamType Demuxer::getStreamType(int pid) const
{
    auto itr = pidToStream.find(pid);
    return itr == pidToStream.end() ? StreamType::Unknown : itr->second;
}

std::optional<StreamChunk> Demuxer::extractChunk(const AVPacket *pAVPacket)
{
    StreamType type = getStreamType(pAVPacket->stream_index);
    if (type == StreamType::Unknown)
        return std::nullopt;

    if ((pAVPacket->flags & AV_PKT_FLAG_CORRUPT) != 0)
    {
        // The packet is curropted, drop the packet
        std::cout << "The packet is corrupted, dropping the packet" << std::endl;
        return std::nullopt;
    }

    StreamChunk chunk;
    chunk.pid = pAVPacket->stream_index;
    chunk.type = getStreamType(chunk.pid);
    chunk.timestamp = pAVPacket->pts;
    chunk.isKeyFrame = (pAVPacket->flags & AV_PKT_FLAG_KEY) != 0;
    chunk.data.assign(pAVPacket->data, pAVPacket->data + pAVPacket->size);
    chunk.channel = channel;

    return chunk;
}
