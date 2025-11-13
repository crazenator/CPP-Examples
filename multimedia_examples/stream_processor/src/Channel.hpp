#pragma once

#include <map>
#include <memory>
#include <string>

#include "Demuxer.hpp"
#include "Dispatcher.hpp"

#include "emitter/Emitter.hpp"
#include "input/InputSource.hpp"

class Channel
{
private:
    std::string name;
    std::string uri;
    std::string target;

    std::unique_ptr<InputSource> inputSource = nullptr;
    std::unique_ptr<Demuxer> demuxer = nullptr;
    std::unique_ptr<Dispatcher> dispatcher = nullptr;

    std::shared_ptr<Emitter> emitter = nullptr;

    void initInputSource();
    void initEmitter();
    void initDemuxer();
    void initDispatcher();

public:
    explicit Channel(const std::string &name, const std::string &uri, const std::string &target);
    ~Channel();

    int initialize();
    void ingest();
};
