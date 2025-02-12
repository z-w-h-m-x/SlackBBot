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
typedef void (*iRSF)(int,const char *, SpecialType, const char*);
typedef void (*iSM)(MessageContent);

extern iRF RegisterFunction;
extern iRSF RegisterSpecialFunction;
extern iSM SendMessage;
extern int index;

Plugin_Extern const char * PluginName();

Plugin_Extern void iInit(int ,iRF, iRSF, iSM);

void SubmitFunction(const char * name);
void SubmitSpecialFunction(SpecialType,const char * name,const char * parm);