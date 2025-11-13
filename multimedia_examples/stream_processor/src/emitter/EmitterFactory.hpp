#pragma once

#include <memory>

#include "Emitter.hpp"
#include "emitter/FileEmitter.hpp"

enum class EmitterType
{
    File
};

class EmitterFactory
{
public:
    static std::shared_ptr<Emitter> create(EmitterType type, const std::string &target)
    {
        switch (type)
        {
        case EmitterType::File:
            return std::make_shared<FileEmitter>(target);

        default:
            return nullptr;
        }
    }
};
