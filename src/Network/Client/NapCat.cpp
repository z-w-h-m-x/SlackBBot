#include "Network/Client/NapCat.h"

#include "GlobalData.h"

#include "json.hpp"

using nlohmann::json;

bool Napcat::Init()
{
    clnt = httplib::Client("127.0.0.1",3000);
    return true;
}

bool Napcat::iSendMessage(MessageContent message)
{
    json j;
    j["auto_escape"] = true;
    if (message.sendID.isGroup)
    {
        j["group_id"] = message.sendID.groupID;
        j["message"] = message.content;
        clnt.Post("/send_group_msg",j.dump(),"application/json");
    }
    else
    {
        j["user_id"] = message.sendID.userID;
        j["message"] = message.content;
        clnt.Post("/send_private_msg",j.dump(),"application/json");
    }
    return true;
}