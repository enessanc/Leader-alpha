//
// Created by tacoe on 27.04.2022.
//

#include <fstream>
#include "JsonTools.h"
#include <codecvt>

namespace Leader
{
    std::wstring utf8_to_wstring(const std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }

    json load_json_file(const std::string &f)
    {
        std::ifstream file(f);
        json data;
        file >> data;
        return data;
    }
}
