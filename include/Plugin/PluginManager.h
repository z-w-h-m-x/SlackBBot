#pragma once

#include "GlobalData.h"

#ifdef _WIN32
#define REGEX_PATTERN_DLIBFILES ".[dD][lL][lL]$"
#else
#define REGEX_PATTERN_DLIBFILES ".[sS][oO]$"
#endif

//尝试加载目录下所有插件
bool LoadPlugin();
//尝试加载单个插件dll
bool LoadPlugin(const char *);