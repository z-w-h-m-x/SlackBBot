#pragma once

#include "../GlobalData.h"

inline void SLB_Init()
{
    logger.mode = 0;
    if (!logger.File_Init( (perfPath + "log.log").c_str() ))
    {
        logger.PrintError("Cant write logger file!");
    }
    logger<<"the message is from logger class";
}