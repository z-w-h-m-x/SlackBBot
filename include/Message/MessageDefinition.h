#pragma once 

/*
ver 1.0

私聊和群聊默认全部交给框架内部处理。
因此需要新的sendID(struct)，以满足储存
    真正的sendID、群聊ID(私聊时为0)、私聊/群聊类型、客户端类型。
同时插件也可获取

*/

enum IMessageSubType
{
    private_friend = 10,
    private_group = 11,//group temporary sessions
    private_other = 19,
    group_normal = 21,
    group_anonymous = 22,
    group_notice = 23,
    group_other = 29
};

enum IMessageType
{
    normal = 0,
    at = 1,
    poke = 2,
    record = 3,
    video = 4,
    music = 5,
    image = 6,
    reply = 7,
    forward = 8,
    node = 9
};

struct SendID //发送信息
{
    IMessageType messageType;
    IMessageSubType subType;
    bool isGroup;
    long long groupID;
    long long userID;//收到时是发送者，发送时是目标。发送至群聊中除了部分action外，这个没用
    int serverID = 0;//serverType. This is the index of vector
};
#pragma pack(push, 1)
struct MessageContent
{
    SendID sendID;
    const char * content = "";
    bool isEmpty = false;
};
#pragma pack(pop)