//
// Created by tacoe on 6.07.2022.
//

#ifndef LEADER_CHARACTERCREATOR_H
#define LEADER_CHARACTERCREATOR_H
#include "source/campaign/entity/character/Character.h"


namespace Leader
{
    typedef std::unordered_map <std::string ,std::unordered_map<std::string, std::vector<std::string>> > Character_Name_Base;
    Character_Name_Base load_character_name_base(const std::string& name_base_file_path);
}


#endif //LEADER_CHARACTERCREATOR_H
