#pragma once

#include "httplib.h"

#include <thread>

class IServer
{
    protected:
        httplib::Server svr;
        std::thread svr_thread;
        bool active = false;

    public:
        bool isRun = false;
        bool Run(const char * host,int port);
        bool Stop();
        virtual bool Init();
        virtual bool Active();
        virtual void AfterStop();
};