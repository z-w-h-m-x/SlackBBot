#include "SLBLog.h"

#include <ctime>
#include <chrono>
#include <string>

using namespace std;

namespace slb
{

const char * GetCurrentTimeString()
{
    using std::chrono::system_clock;

    system_clock::time_point now = system_clock::now();
    std::time_t now_time_t = system_clock::to_time_t(now);
    std::tm* now_tm = localtime(&now_time_t);

    char buffer[128];
    strftime(buffer,sizeof(buffer),"%F %T", now_tm);

    chrono::nanoseconds ns;

    ns = chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;

    std::string tmp;

    tmp = buffer;

    return tmp.c_str();

}

}

void SLBLog::CloseFileStream()
{
    logFile.close();
}

void SLBLog::Close()
{
    if (isOpenFile)
        CloseFileStream();
}

bool SLBLog::File_Init(const char *filePath)
{
    logFile.open(filePath);
    if (!logFile.good())
    {
        CloseFileStream();
        return false;
    }
    isOpenFile = true;
    return true;
}
