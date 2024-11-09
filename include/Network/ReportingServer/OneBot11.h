#pragma once

#include "../ServerBase.h"

#include <ctime>
#include <chrono>
#include <mutex>

class Server_OneBot11 : public IServer 
{
    private:
        std::thread heartBeat_thread;
        bool stop = false;
        std::chrono::milliseconds lastHeartBeatTime;
        void HeartBeatProcessor();
        std::mutex mutex_Beat;
        u_int count = 0;
    protected:

    public:
        bool Init() override;
        bool Active() override;
        void AfterStop() override;
        
        void HeartBeat();
};