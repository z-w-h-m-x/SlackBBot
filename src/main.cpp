/*
    SlackBot
    Copyright (C) 2024 SlackBotDevelopers

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "GlobalData.h"
#include "ProgramInfo.h"

#include <iostream>

#include "SDL.h"
#include "SDL_filesystem.h"

#include "httplib.h"
#include "windows.h"

#include "Data/Data.h"
#include "Processor/CommandProcessor.h"
#include "Processor/InitializingFramework.h"

using namespace std;

#undef main

int main(int argc,char* argv[])
{
    // 初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    perfPath = SDL_GetPrefPath("SlackBotDev","SlackBot");

    SLB_Init();

    cout<<ProjectName<<" "<<ProjectVersion<<endl
        <<"Built in "<<CMAKE_SYSTEM_NAME<<endl;

    RegisterCommandRule();
    SetFollowCommand(qoe::AnalysisArgOptToMap(argc,argv));

    return 0;
}
