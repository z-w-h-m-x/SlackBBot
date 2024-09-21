#pragma once

#include <string>

namespace slb
{

enum ActionType
{
    _message = 0,
    _poke = 1,
};

enum RoomType
{
    _private = 0,
    _group = 1,
};

struct ChatMessage
{
    int roomID;
    int UID;//user
    RoomType roomType;
    ActionType actionType;
    std::string message;
    std::string rawMessage;
};

}