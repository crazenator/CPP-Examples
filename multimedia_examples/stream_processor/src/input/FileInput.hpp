#pragma once

#include "InputSource.hpp"

class FileInput : public InputSource
{
public:
    bool open(const std::string &uri) override;
    void close() override;
    AVFormatContext *getFormatContext() override;
    std::optional<AVPacketPtr> read() override;
};
