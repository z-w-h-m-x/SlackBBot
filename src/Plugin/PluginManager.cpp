#include "Plugin/PluginManager.h"

#include "SlackBot.h"
#include "Processor/ProgramStop.h"
#include "Processor/MessageQueueProcessor.h"

#include <map>
#include <filesystem>
#include <regex>

using std::filesystem::directory_iterator;

std::vector<std::string> targetPath;//Dynamic library in folder of plugins.
std::map<std::string,std::string> pluginPath;//<name,path>
std::map<int,void*> plugins;//plugin index, handle

typedef const char * (*iPluginName)();
typedef void (*iRF)(int,const char *);
typedef void (*iRSF)(int,const char *, SpecialType, const char*);
typedef void (*iSM)(MessageContent);
typedef void (*iInit)(int,iRF,iRSF,iSM);
typedef void (*pInit)();

//try to find floder in folder and wrtier path to "targetPath"
void SearchPluginInFolder()
{
    //Dynamic library file suffix
    std::regex DLibFileS(REGEX_PATTERN_DLIBFILES);
    for (auto const& dir_entry : directory_iterator(programPath + "plugin/"))
    {
        if (std::regex_match(dir_entry.path().u8string(),DLibFileS))
        {
            targetPath.push_back(dir_entry.path().u8string());
        }
    }
}

//尝试加载目录下所有插件
bool LoadAllPlugin()
{
    logger<<"Search Plugin...";

    SearchPluginInFolder();

    int index = 0;

    for (std::string i : targetPath)
    {
        void* handle = SDL_LoadObject(i.c_str());
        iPluginName getPluginName;
        iInit iiInit;
        pInit Init;

        if (handle == nullptr) {
            logger.PrintError("Fail to load object: " + i);
            SDL_UnloadObject(handle);
        }
        else {
            try
            {
                getPluginName = (iPluginName)tryGetFunction(handle,"PluginName");
                iiInit = (iInit)tryGetFunction(handle,"iInit");
                Init = (pInit)tryGetFunction(handle,"Init");
            }
            catch(const char * e)
            {
                SDL_UnloadObject(handle);
                logger.PrintError(e);
                continue;
            }

            plugins[index] = handle;
            pluginPath[getPluginName()] = i;
            iiInit(index,RegisterFunction,RegisterSpecialFunction,sendMessage);

            std::ostringstream oss;
            oss <<"Load Plugin: " << getPluginName() << " from " << i;
            logger<<oss.str();

            Init();

            index++;
        }
        
    }

    return true;
}

//尝试加载单个插件dll
bool LoadPlugin(const char *)
{
    logger<<"Loading a single plugin is not yet implemented.";
    return false;
}

void* tryGetFunction(void* handle,const char* functionName)
{
    void* tmp = SDL_LoadFunction(handle,functionName);
    if (tmp == nullptr)
    {
        throw "Can't to load Function";
    }
    return tmp;
}

std::map<std::string,int> mapName =
{   //1xxx fillter - 1oxx 1=Receive 2=Send 
    {"Fillter_AfterReceiveMessage",1101},
    {"Fillter_BeforeSendMessage",1201}
};

Function_Extern void RegisterFunction(int i,const char * name)
{
    if (plugins.find(i) == plugins.end())
        return ;

    try
    {
        logger<<mapName.count(name);
        if (mapName.count(name)>0)
        {   //存在
            switch (mapName[std::string(name)])
            {
            case 1101:
                logger<<"push";
                Fillter_AfterReceiveMessage.push_back((Fillter)tryGetFunction(plugins[i],name));
                break;
            case 1201:
                Fillter_BeforeSendMessage.push_back((Fillter)tryGetFunction(plugins[i],name));
                break;
            default:
                break;
            }
        }
        else
        {   //不存在

        }
    }
    catch(const char * e)
    {
        logger.PrintError(e);
    }
}

Function_Extern void RegisterSpecialFunction(int index,const char * name,SpecialType type,const char * parm)
{
    if (plugins.find(index) == plugins.end())
        return ;
}