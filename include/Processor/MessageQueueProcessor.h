#pragma once

#include "Message/MessageDefinition.h"
#include "Message/iMessageDefinition.h"
#include "FunctionExtern.h"
#include <list>
#include <map>

typedef bool (*Fillter)(MessageContent);
typedef bool (*Msg_Normal)(MessageContent);
typedef void (*Msg_Tirgger)(MessageContent);

extern std::list<Fillter> Fillter_AfterReceiveMessage;
extern std::list<Fillter> Fillter_BeforeSendMessage;
extern std::list<Msg_Normal> MessageNormal;
extern std::map<IMessageType,std::list<Msg_Tirgger>> MessageTirgger;

bool MessageProcessorInit();
void MessageProcessorStop();

//上报收到消息
void ReceiveMessage(iMessageContent);
//从上报队列获取消息
iMessageContent GetRMessage();
//从发送队列获取消息
iMessageContent GetSMessage();

Function_Extern void sendMessage(MessageContent);