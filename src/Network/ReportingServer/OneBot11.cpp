#include "Network/ReportingServer/OneBot11.h"

#include "GlobalData.h"
#include <string>
#include <sstream>
#include <map>

#include "json.hpp"

using std::string;
using std::map;
using std::chrono::system_clock;
using nlohmann::json;

httplib::Client client("192.168.1.36",3000);

map<string,int> postTypeMap = 
{
    {"meta_event",1},{"message",2},{"notice",3}
};
map<string,int> metaEventTypeMap = 
{
    {"heartbeat",1}
};
map<string,int> messageTypeMap = //sub type(99xx),message block(50xx)
{
    {"private",1},{"group",2},
    {"at",5001},{"shake",5002},
    {"friend",9901},{"group",9902},{"other",9903},{"normal",9951},{"anonymous",9952},{"notice",9953}//sub type(private:xx<50,group:xx>=50)
};
map<string,int> noticeTypeMap = //sub type(99xx)
{
    {"notify",1},
    {"poke",9901}
};

bool Server_OneBot11::Init()
{
    {
        std::thread temp( [this](){HeartBeatProcessor();} );
        heartBeat_thread.swap(temp);
    }

    svr.Post("/", [this](const httplib::Request& req,httplib::Response& res){
        json body = json::parse(req.body.c_str());
        if (body["post_type"].is_string())//is json from onebot
        {
            string post_type = body["post_type"];
            int self_id = body["self_id"];
            switch (postTypeMap[post_type])
            {
            case 1://meta_event
                if (body["meta_event_type"].is_string())
                {   string meta_event_type = body["meta_event_type"];
                    switch (metaEventTypeMap[meta_event_type])
                    {
                    case 1://heartbeat
                        HeartBeat();
                        logger.Screen(self_id + "hit server");
                        count++;//合规计数
                        break;

                    default:
                        break;
                    }
                }
                break;
            
            case 2://message
                if (body["message_type"].is_string())
                {   string message_type = body["message_type"];
                    std::stringstream reply;
                    switch (messageTypeMap[message_type])
                    {
                    case 1://private
                        count++;//合规计数
                        reply<< "{\"reply\":\"Hit x" << count << "\"}";
                        logger.Screen(reply.str());
                        res.status=200;
                        res.set_content(reply.str(),"application/json");
                        break;
                    
                    case 2://group
                        reply<< "Hit x" << count;
                        if (body["message"][0]["type"].is_string())
                        {
                            string s = body["message"][0]["type"];
                            string qq = body["message"][0]["data"]["qq"];
                            int id = body["group_id"];
                            if ( (s=="at" && atoi(qq.c_str()) == self_id) || s == "shake") 
                            {
                                count++;//合规计数
                                json j;
                                j["group_id"] = id;
                                j["message"] = reply.str();
                                j["auto_escape"] = true;
                                Sleep(1000);
                                auto post_res = client.Post("/send_group_msg_rate_limited",j.dump(),"application/json");
                                if (post_res && post_res->status == 200) {
                                    
                                } else {
                                    std::cout << "POST request failed" << std::endl;
                                }
                            }
                        }
                        break;

                    default:
                        break;
                    }
                }
                break;

            case 3://notice
                if (body["notice_type"].is_string())
                {   string notice_type = body["notice_type"];
                    std::stringstream reply;
                    if (notice_type == "notify")
                    {
                        string sub_type = body["sub_type"];
                        if (sub_type=="poke")
                        {
                            count++;//合规计数
                            reply<< "Hit x" << count;
                            if (body["group_id"].is_number())
                            {
                                int id = body["group_id"];
                                json j;
                                j["group_id"] = id;
                                j["message"] = reply.str();
                                j["auto_escape"] = true;
                                Sleep(1000);
                                auto post_res = client.Post("/send_group_msg_rate_limited",j.dump(),"application/json");
                                if (post_res && post_res->status == 200) {
                                    std::cout << "POST request succeeded: " << post_res->body << std::endl;
                                } else {
                                    std::cout << "POST request failed" << std::endl;
                                }
                            }
                        }
                    }
                }
                break;

            default:
                break;
            }

        }
    });


    return true;
}

bool Server_OneBot11::Active()
{
    return true;
}

void Server_OneBot11::AfterStop()
{
    stop = true;

    if (heartBeat_thread.joinable()) heartBeat_thread.join();

    
}

void Server_OneBot11::HeartBeat()
{
    mutex_Beat.lock();
    lastHeartBeatTime = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
    mutex_Beat.unlock();
}

void Server_OneBot11::HeartBeatProcessor()
{
    std::chrono::duration duration = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch());
    while (!stop)
    {
        mutex_Beat.lock();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(duration - lastHeartBeatTime);
        mutex_Beat.unlock();

        if (duration.count() <= 3000)//3s
        {
            if(!active)
                active = true;
        }
        else
        {
            if(active)
                active = false;
        }

        Sleep(1000);
    }
}