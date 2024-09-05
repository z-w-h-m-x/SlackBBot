#include "GlobalData.h"

#include <iostream>

#include "SDL.h"

#include "json.hpp"
#include "httplib.h"
#include "windows.h"

#include "Processor/CommandProcessor.h"

using namespace std;

#undef main

int main(int argc,char* argv[])
{
    // 初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    cout<<"QNTBOT DEV\n";

    RegisterCommandRule();
    SetFollowCommand(qoe::AnalysisArgOptToMap(argc,argv));

    return 0;
}
