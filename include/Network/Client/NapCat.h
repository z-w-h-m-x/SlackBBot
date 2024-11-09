#pragma once

#include "../../Export.h"

#include <string>

using std::string;

APIEXPORT void NAPCAT_SendPrivateMsg(string);
APIEXPORT void NAPCAT_SendGroupMsg(string);
APIEXPORT void NAPCAT_SendMsg();

APIEXPORT void NAPCAT_GetMsg();
APIEXPORT void NAPCAT_GetLoginInfo();

APIEXPORT void NAPCAT_SetOnlineStaus();
APIEXPORT void NAPCAT_SetSelfLongnick();//个人签名
APIEXPORT void NAPCAT_MarkAllAsRead();

APIEXPORT void NAPCAT_GetVersionInfo();