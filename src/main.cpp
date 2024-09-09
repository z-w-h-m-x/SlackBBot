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

#include <iostream>

#include "SDL.h"
#include "SDL_filesystem.h"

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

    perfPath = SDL_GetPrefPath("SlackDev","SlackBot");

    cout<<"QNTBOT DEV\n";

    RegisterCommandRule();
    SetFollowCommand(qoe::AnalysisArgOptToMap(argc,argv));

    return 0;
}
