#include "Network/ServerBase.h"

#include "GlobalData.h"
#include "Processor/ProgramStop.h"

bool IServer::Run(const char * host,int port)
{
    try
    {
        {
            std::thread temp( [this,host,port](){svr.listen(host,port);} );
            svr_thread.swap(temp);
        }
        isRun = true;
    }
    catch(const std::exception& e)
    {
        logger << "catch error in running server";
        logger.Print( e.what() );
        Stop_Error();
    }

    return true;

}

bool IServer::Stop()
{

    AfterStop();

    svr.stop();

    if (svr_thread.joinable())
    {
        svr_thread.join();
    }

    return true;
}

void IServer::AfterStop() {}

bool IServer::Init() {return true;}
bool IServer::Active() {return true;}