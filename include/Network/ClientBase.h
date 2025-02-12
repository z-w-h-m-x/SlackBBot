#pragma once

#include "httplib.h"
#include "Message/MessageDefinition.h"

class IClient
{
    protected:
        bool active = false;
    public:
        virtual bool Init();
        virtual bool iSendMessage(MessageContent);
};