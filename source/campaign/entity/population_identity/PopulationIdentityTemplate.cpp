//
// Created by tacoe on 28.04.2022.
//

#include "PopulationIdentityTemplate.h"

#include <utility>
#include "source/tools/JsonTools.h"
#include "spdlog/spdlog.h"

namespace Leader
{

    std::unordered_map<std::string, PopulationIdentityTemplate> load_population_identity_template_objects(const std::string &file_path)
    {
        std::unordered_map<std::string, PopulationIdentityTemplate> population_identity_template_objects_map;
        json data = load_json_file(file_path);
        for(auto& population_identity_template:data)
        {
            PopulationIdentityTemplate new_template =
            {
            std::move(population_identity_template.at("stringId")),
            std::move(population_identity_template.at("gender_groups_weights")),
            std::move(population_identity_template.at("age_groups_weights")),
            std::move(population_identity_template.at("job_groups_weights")),
            std::move(population_identity_template.at("economical_groups_weights")),
            std::move(population_identity_template.at("educational_groups_weights"))
            };

            population_identity_template_objects_map[new_template.stringId] = new_template;
        }
        return population_identity_template_objects_map;
    }

    static std::vector<float> merge_weights(const std::vector<float> &first, const std::vector<float> &second)
    {
        if(first.size() != second.size())
        {
            spdlog::error("The length of weight must be same, this is an critical error, program is shutting down...");
            exit(EXIT_FAILURE);
        }
        std::vector<float> new_weights;
        for(int i =0; i < first.size(); ++i)
        {
            float new_weight = (first.at(i) + second.at(i)) / 2;
            new_weights.push_back(new_weight);
        }
        return new_weights;
    }

    PopulationIdentityTemplate merge_population_identity_templates(const PopulationIdentityTemplate &first,
                                                                   const PopulationIdentityTemplate &second)
    {
        PopulationIdentityTemplate new_template;
        new_template.stringId = first.stringId + "_"+ second.stringId;
        new_template.gender_groups_weights = merge_weights(first.gender_groups_weights,second.gender_groups_weights);
        new_template.age_groups_weights = merge_weights(first.age_groups_weights,second.age_groups_weights);
        new_template.age_groups_weights.at(0) = 0;
        /*
         Correcting child weights to zero after merging. We do not want child characters in the game,
         they are just used in creating pop units for cities.
         */
        new_template.job_groups_weights = merge_weights(first.job_groups_weights,second.job_groups_weights);
        new_template.economical_groups_weights = merge_weights(first.economical_groups_weights,second.economical_groups_weights);
        new_template.educational_groups_weights = merge_weights(first.educational_groups_weights,second.educational_groups_weights);

        return new_template;
    }
}
