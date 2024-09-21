#pragma once

#include "ServerData.h"

#include "json.hpp"

namespace Data
{
    using nlohmann::json;

    //ServerData

    inline void to_json(json &j,const ServerData &p)
    {
        j = json{{"port",p.port},{"napCatPort",p.napCatPort},
                {"napCatHost",p.napCatHost},{"host",p.host}
        };
    }

    inline void from_json(const json &j,ServerData &p)
    {
        j.at("port").get_to(p.port);
        j.at("napCatPort").get_to(p.napCatPort);
        j.at("napCatHost").get_to(p.napCatHost);
        j.at("host").get_to(p.host);
    }
}