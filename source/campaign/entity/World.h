//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_WORLD_H
#define LEADER_WORLD_H
#include "source/tools/Randomizer.h"
#include "source/campaign/entity/base/Entity.h"
#include "source/campaign/entity/ideology/Ideology.h"
#include "source/campaign/entity/population_identity/PopulationIdentityTemplate.h"
#include "source/campaign/entity/character/Character.h"
#include "source/campaign/entity/character/CharacterCreator.h"
#include "source/campaign/entity/Country.h"
#include <string>
#include <unordered_map>


namespace Leader
{
    class World: public Entity
    {
    private:
        const int world_initial_seed;
        Randomizer world_randomizer;
        std::vector<IdeologyAxis> world_ideology_axis_objects;
        std::unordered_map<std::string, PopulationIdentityTemplate> city_population_identity_templates;
        std::unordered_map<std::string, PopulationIdentityTemplate> party_population_identity_templates;
        std::vector<Country> world_country_objects;
        Character_Trait_Map world_character_trait_objects;
        Character_Name_Base world_character_name_base;
        unsigned int ideology_axis_count;
    public:
        explicit World(const int& _seed);
        std::vector<IdeologyAxis> get_world_ideology_axis_objects() const
        {
            return this->world_ideology_axis_objects;
        }
        std::unordered_map<std::string, PopulationIdentityTemplate> get_city_population_identity_objects_map() const
        {
            return this->city_population_identity_templates;
        }

        std::vector<Country>& get_world_country_objects()
        {
            return world_country_objects;
        }

        void initialize_country();
    };
}


#endif //LEADER_WORLD_H
