#pragma once

#include "Plugin_FunctionDefinition.h"
#include "Message/MessageDefinition.h"

#ifdef _WIN32
#define Plugin_Extern extern "C" __declspec(dllexport)
#else
#define Plugin_Extern extern "C"
#endif
//dll导出定义

typedef void (*iRF)(int,const char *);
typedef void (*iRSF)(int,const char *, SpecialType, int);
typedef void (*iSM)(MessageContent);

extern iRF RegisterFunction;
extern iRSF RegisterSpecialFunction;
extern iSM BotSendMessage;
extern int pIndex;

Plugin_Extern const char * PluginName();
Plugin_Extern void Init();

Plugin_Extern void iInit(int ,iRF, iRSF, iSM);

void SubmitFunction(const char * name);
void SubmitSpecialFunction(SpecialType,const char * name,int parm);

void SubmitMessageTrigger(IMessageType,const char * name);