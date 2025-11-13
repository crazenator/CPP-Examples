
#include <fstream>

#include "emitter/FileEmitter.hpp"

FileEmitter::FileEmitter(const std::string &dir)
{
    // Create output directory for the channel
    rootDir = std::filesystem::path(dir);
    std::filesystem::create_directories(rootDir);
}

/* === Private Functions === */
std::tm FileEmitter::ptsToUtc(uint64_t pts90k)
{
    // Convert 90 kHz PTS to milli-seconds
    auto ms = pts90k / 90;

    // Convert milli-seconds to time
    std::time_t t = static_cast<std::time_t>(ms / 1000);

    // UTC representation of time
    return *gmtime_r(&t, nullptr);
}

std::string FileEmitter::getDirName(const std::tm &time)
{
    constexpr auto format = "%Y/%m/%d/%H";

    std::ostringstream oss;
    oss << std::put_time(&time, format);
    return oss.str();
}

std::string FileEmitter::getFileName(uint64_t startTs)
{
    constexpr auto format = "%Y%m%dT%H%M%SZ";

    auto tm = ptsToUtc(startTs);

    std::ostringstream oss;
    oss << "_" << std::put_time(&tm, format)
        << "_" << std::setw(6) << std::setfill('0') << counter;

    return oss.str();
}

std::filesystem::path FileEmitter::createRotationDir(uint64_t startTs)
{
    auto tm = ptsToUtc(startTs);
    auto dir = rootDir / getDirName(tm);
    auto newDirCreated = std::filesystem::create_directories(dir);
    if (newDirCreated)
    {
        counter = 0;
    }

    return dir;
}

/* === Public Functions === */
void FileEmitter::emit(uint64_t startTs, const std::vector<StreamChunk> &chunks)
{
    // Ensure the directory is present
    auto dir = createRotationDir(startTs);

    // Create output binary file for the transport stream
    auto filePath = dir / (getFileName(startTs) + ".ts");
    std::ofstream ofs(filePath, std::ios::binary);

    // Traverse all chunks and write to the disk
    for (const auto &chunk : chunks)
    {
        ofs.write(reinterpret_cast<const char *>(chunk.data.data()),
                  static_cast<std::streamsize>(chunk.data.size()));
    }

    counter++;
}
