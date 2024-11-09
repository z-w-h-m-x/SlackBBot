#pragma once

#include <vector>
#include <string>

#include "Data/ServerData.h"
#include "Network/ServerBase.h"

#include "SLBLog.h"

//Global variable
extern Data::ServerData serverConfig;
extern std::string programPath;
extern std::string perfPath;
extern SLBLog logger;

extern IServer* server;

extern bool disableLogSaving;