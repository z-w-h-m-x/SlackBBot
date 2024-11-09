#include "GlobalData.h"

//Global variable
Data::ServerData serverConfig;
std::string programPath;
std::string perfPath;
SLBLog logger;

IServer* server;

bool disableLogSaving = false;