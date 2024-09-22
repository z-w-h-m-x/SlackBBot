#include "Processor/InitializingFramework.h"

#include "GlobalData.h"

#include <iostream>
#include <string>

void SLB_Init()
{
    if (!disableLogSaving)
        {logger.mode = 0;}
    else
        {logger.mode = 2;}

    if (!logger.File_Init( (perfPath + "log.log").c_str() ))
    {
        logger.PrintError("Cant write logger file!");
    }
    logger<<"the message is from SLBLog class";
}