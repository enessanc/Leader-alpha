//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_POPULATIONIDENTITYTEMPLATE_H
#define LEADER_POPULATIONIDENTITYTEMPLATE_H
#include <string>
#include <unordered_map>
#include <filesystem>
#include <vector>
#include <source/campaign/entity/base/Entity.h>
#include "external/json.hpp"

namespace Leader 
{

    struct PopulationIdentityTemplate
    {
        std::string stringId;
        std::vector<float> gender_groups_weights;
        std::vector<float> age_groups_weights;
        std::vector<float> job_groups_weights;
        std::vector<float> economical_groups_weights;
        std::vector<float> educational_groups_weights;
    };

    PopulationIdentityTemplate merge_population_identity_templates(const PopulationIdentityTemplate& first, const PopulationIdentityTemplate& second);
    std::unordered_map <std::string, PopulationIdentityTemplate> load_population_identity_template_objects(const std::string & file_path);

}

#endif //LEADER_POPULATIONIDENTITYTEMPLATE_H
