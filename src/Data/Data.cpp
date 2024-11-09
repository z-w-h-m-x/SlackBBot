#include "Data/Data.h"

#include "GlobalData.h"
#include "Processor/ProgramStop.h"

#include <fstream>
#include <iostream>

namespace Data
{
    void InitAndReadConfig()
    {
        std::ifstream jump(perfPath + "jump");
        if (jump.good() == true)
            jump >> perfPath;
        jump.close();
        
        std::ifstream jFile(perfPath + "ServerConfig.json",std::ios::in);
        json tmp;
        if (jFile.good() != true)
        {
            logger.PrintError("Cant read config!");
            Stop_Error();
        }
        else {
            jFile >> tmp;
            serverConfig = tmp.get<ServerData>();
        }
    }
}