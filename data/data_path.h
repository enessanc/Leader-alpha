//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_DATA_PATH_H
#define LEADER_DATA_PATH_H
#include "config.h"
#include <string>
namespace Leader
//Path Correction Functions
{
    std::string correct_path(const std::string &s) {
        std::string new_string = s;
        std::replace(new_string.begin(), new_string.end(), '/', '\\'); // replace all 'x' to 'y'
        return new_string;
    }

}

namespace Leader
//Entity Paths
{
    const std::string CHARACTER_NAME_BASE_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/character/character_name_base.json");
    const std::string CHARACTER_TRAIT_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/character/character_trait.json");
    const std::string CITY_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/city/city.json");
    const std::string CITY_POPULATION_IDENTITY_TEMPLATE_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/city/city_population_identity_template.json");
    const std::string COUNTRY_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/country/country.json");
    const std::string IDEOLOGY_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/ideology/ideology.json");
    const std::string IDEOLOGY_AXIS_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/ideology/ideology_axis.json");
    const std::string PARTY_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) + "/data/json_file/entity/party/party.json");
    const std::string PARTY_POPULATION_IDENTITY_TEMPLATE_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) +
            "/data/json_file/entity/party/party_population_identity_template.json");

}


namespace Leader
//Preferences Path
{
    const std::string FIRST_ELECTION_DIFFICULTY_PATH = correct_path(std::string(PROJECT_SOURCE_DIR) +
            "/data/json_file/preference/base/difficulty/first_election_difficulty.json");

}

#endif //LEADER_DATA_PATH_H
