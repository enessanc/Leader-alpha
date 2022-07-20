//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_JSONTOOLS_H
#define LEADER_JSONTOOLS_H
#include <external/json.hpp>


using nlohmann::json;

namespace Leader
{
    std::wstring utf8_to_wstring(const std::string& str);
    json load_json_file(const std::string &f);
}


#endif //LEADER_JSONTOOLS_H
