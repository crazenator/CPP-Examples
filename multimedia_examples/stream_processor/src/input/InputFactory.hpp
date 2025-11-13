#pragma once

#include "InputSource.hpp"
#include "FileInput.hpp"
#include "NetworkInput.hpp"

enum class InputType
{
    File,   // TS
    Network // UDP, SRT, RTP
};

class InputFactory
{
public:
    static std::unique_ptr<InputSource> create(InputType type, const std::string &uri)
    {
        switch (type)
        {
        case InputType::File:
            return std::make_unique<FileInput>();
        case InputType::Network:
            return std::make_unique<NetworkInput>();

        default:
            return nullptr;
        }
    }
};
