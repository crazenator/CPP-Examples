#pragma once

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <string>

#include "Emitter.hpp"

class FileEmitter : public Emitter
{
private:
    uint64_t counter = 0;
    std::filesystem::path rootDir;

    std::tm ptsToUtc(uint64_t pts90k);

    std::string getDirName(const std::tm &time);
    std::string getFileName(uint64_t startTs);

    std::filesystem::path createRotationDir(uint64_t startTs);

public:
    explicit FileEmitter(const std::string &dir);

    void emit(uint64_t startTs, const std::vector<StreamChunk> &chunks) override;
};
