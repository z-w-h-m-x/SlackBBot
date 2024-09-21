#pragma once

#include <string>

namespace Data
{
    struct ServerData
    {
        int port = 1234;
        int napCatPort = 3000;
        std::string napCatHost = "127.0.0.1";
        std::string host = "0.0.0.0";
    };

} 
