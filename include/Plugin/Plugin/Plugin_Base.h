#pragma once

#ifdef _WIN32
#define Plugin_Extern extern "C" __declspec(dllexport)
#else
#define Plugin_Extern extern "C"
#endif
//dll导出定义

enum PluginType
{
    //指定值求稳定
    custom = 0,
    chat = 1,
    filter = 2,
    action = 3
};