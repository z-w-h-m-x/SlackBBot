#include "Data/Data.h"
#include "GlobalData.h"

#include <fstream>
#include <iostream>

namespace Data
{
    void InitAndReadConfig()
    {
        std::ifstream jFile(perfPath + "ServerConfig.json");
        json tmp;
        if (jFile.good() != true)
        {
            
        }
        else {
            jFile >> tmp;
            serverConfig  = tmp.get<ServerData>();
        }
    }
}