#include "Plugin/PluginManager.h"

#include "SlackBot.h"
#include "Processor/ProgramStop.h"

#include <map>
#include <filesystem>
#include <regex>

using std::filesystem::directory_iterator;

std::vector<std::string> targetPath;//Dynamic library in folder of plugins.
std::map<std::string,std::string> pluginPath;//<name,path>

//[WIP]Don't use.
void FindPlugin()
{
    //Dynamic library file suffix
    std::regex DLibFileS(REGEX_PATTERN_DLIBFILES);
    for (auto const& dir_entry : directory_iterator(perfPath))
    {
        if (std::regex_match(dir_entry.path().u8string(),DLibFileS))
        {
            targetPath.push_back(dir_entry.path().u8string());
        }
    }
}

//尝试加载目录下所有插件
bool LoadPlugin()
{
    return true;
}

//尝试加载单个插件dll
bool LoadPlugin(const char *)
{
    logger<<"Loading a single plugin is not yet implemented.";
    return false;
}