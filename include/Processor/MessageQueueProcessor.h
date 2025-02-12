#pragma once

#include "Message/MessageDefinition.h"
#include "FunctionExtern.h"
#include <list>

typedef bool (*Fillter)(MessageContent);

extern std::list<Fillter> Fillter_AfterReceiveMessage;
extern std::list<Fillter> Fillter_BeforeSendMessage;

bool MessageProcessorInit();
void MessageProcessorStop();

//上报收到消息
void ReceiveMessage(MessageContent);
//从上报队列获取消息
MessageContent GetRMessage();
//从发送队列获取消息
MessageContent GetSMessage();

Function_Extern void sendMessage(MessageContent);