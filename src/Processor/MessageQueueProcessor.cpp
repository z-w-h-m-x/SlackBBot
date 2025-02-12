#include "Processor/MessageQueueProcessor.h"

#include "GlobalData.h"
#include "Processor/ProgramStop.h"

#include <list>
#include <queue>
#include <thread>
#include <mutex>

//待处理上报消息队列
std::queue<MessageContent> pendingMessages;
std::mutex pendingMutex;

//待发送消息队列
std::queue<MessageContent> sendMessages;
std::mutex sendMutex;

std::thread tPendingProcessor;
std::thread tSendProcessor;

std::list<Fillter> Fillter_AfterReceiveMessage;
std::list<Fillter> Fillter_BeforeSendMessage;

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

void ReceiveMessage(MessageContent content)
{
    std::unique_lock<std::mutex> lock(pendingMutex);
    pendingMessages.push(content);
}

MessageContent GetRMessage()
{
    std::unique_lock<std::mutex> lock(pendingMutex);
    MessageContent tmp;
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

MessageContent GetSMessage()
{
    std::unique_lock<std::mutex> lock(sendMutex);
    MessageContent tmp;
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
    sendMessages.push(content);
}

void PendingProcessor()
{
    int ec=0;//周期内尝试为空的次数
    bool slow=false;//慢模式，休眠100
    MessageContent message;
    for ( ;!needStop; )//不需要停止
    {
        message = GetRMessage();
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
            //关键词匹配
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
    for ( ;!needStop; )//不需要停止
    {
        message = GetSMessage();
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