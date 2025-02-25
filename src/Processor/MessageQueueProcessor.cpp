#include "Processor/MessageQueueProcessor.h"

#include "GlobalData.h"
#include "Processor/ProgramStop.h"

#include <list>
#include <queue>
#include <thread>
#include <mutex>

//待处理上报消息队列
std::queue<iMessageContent> pendingMessages;
std::mutex pendingMutex;

//待发送消息队列
std::queue<iMessageContent> sendMessages;
std::mutex sendMutex;

std::thread tPendingProcessor;
std::thread tSendProcessor;

std::list<Fillter> Fillter_AfterReceiveMessage;
std::list<Fillter> Fillter_BeforeSendMessage;
std::list<Msg_Normal> MessageNormal;
std::map<IMessageType,std::list<Msg_Tirgger>> MessageTirgger;

//上报消息队列处理
void PendingProcessor();
//发送消息队列处理
void SendProcessor();
bool needStop = false;

bool MessageProcessorInit()
{
    try
    {
        std::thread tmpP(PendingProcessor);
        std::thread tmpS(SendProcessor);
        tPendingProcessor.swap(tmpP);
        tSendProcessor.swap(tmpS);
    }
    catch(const std::exception& e)
    {
        logger.PrintError(e.what());
        Stop_Error();
    }
    

    return true;
}

void MessageProcessorStop()
{
    needStop=true;
    if (tPendingProcessor.joinable())
        tPendingProcessor.join();
    if (tSendProcessor.joinable())
        tSendProcessor.join();
}

void ReceiveMessage(iMessageContent content)
{
    std::unique_lock<std::mutex> lock(pendingMutex);
    pendingMessages.push(content);
}

iMessageContent GetRMessage()
{
    std::unique_lock<std::mutex> lock(pendingMutex);
    iMessageContent tmp;
    if (!pendingMessages.empty())
    {
        tmp = pendingMessages.front();
        pendingMessages.pop();
        return tmp;
    }
    else
    {
        tmp.isEmpty = true;
        return tmp;
    }
}

iMessageContent GetSMessage()
{
    std::unique_lock<std::mutex> lock(sendMutex);
    iMessageContent tmp;
    if (!sendMessages.empty())
    {
        tmp = sendMessages.front();
        sendMessages.pop();
        return tmp;
    }
    else
    {
        tmp.isEmpty = true;
        return tmp;
    }
}

Function_Extern void sendMessage(MessageContent content)
{
    logger<<content.content;
    std::unique_lock<std::mutex> lock(sendMutex);
    sendMessages.push(ToIMessageContent(content));
}

void PendingProcessor()
{
    int ec=0;//周期内尝试为空的次数
    bool slow=false;//慢模式，休眠100
    iMessageContent iMessage;
    MessageContent message;
    for ( ;!needStop; )//不需要停止
    {
        iMessage = GetRMessage();
        message = ToMessageContent(iMessage);
        if (!message.isEmpty)
        {
            if (slow)
            {
                slow = false;
                ec = 0;
            }
            for (Fillter process : Fillter_AfterReceiveMessage)
            {
                if ( !process(message) )
                    break;
            }

            //消息类型匹配
            if (message.sendID.messageType != normal)
            {
                if (MessageTirgger.find(message.sendID.messageType) != MessageTirgger.end())
                {
                    for (Msg_Tirgger F : MessageTirgger[message.sendID.messageType])
                    {
                        F(message);
                    }
                }
            }
            //normal
            for (Msg_Normal F : MessageNormal)
            {
                if ( F(message) != true)
                    break;
            }
        }
        else//为空队列
        {
            if (slow)
            {
                Sleep(100);
            }
            else
            {
                ec++;
                if (ec >= 10000)//万次空循环后进入慢模式
                    slow = true;
            }
        }
    }
}

void SendProcessor()
{
    int ec=0;//周期内尝试为空的次数
    bool slow=false;//慢模式，休眠100
    MessageContent message;
    iMessageContent iMessage;
    for ( ;!needStop; )//不需要停止
    {
        iMessage = GetSMessage();
        message = ToMessageContent(iMessage);
        message.content = iMessage.contentS.c_str();//避免悬空
        if (!message.isEmpty)
        {
            if (slow)
            {
                slow = false;
                ec = 0;
            }
            for (Fillter process : Fillter_BeforeSendMessage)
            {
                if ( !process(message) )
                    break;
            }
            client->iSendMessage(message);
        }
        else//为空队列
        {
            if (slow)
            {
                Sleep(100);
            }
            else
            {
                ec++;
                if (ec >= 10000)//万次空循环后进入慢模式
                    slow = true;
            }
        }
    }
}