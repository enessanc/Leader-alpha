//
// Created by tacoe on 27.04.2022.
//

#include "World.h"
#include <iostream>
#include "spdlog/spdlog.h"
#include "data/json_file/entity/entity_path.h"

namespace Leader {

    static std::string generate_world_stringId(const int& _seed)
    {
        return std::string("world") + std::to_string(_seed);
    }

    World::World(const int &_seed): Entity(generate_world_stringId(_seed)), world_initial_seed(_seed)
    {
        this->world_randomizer.set_seed(this->world_initial_seed);
        this->world_ideology_axis_objects = load_ideology_axis_objects(IDEOLOGY_AXIS_PATH, IDEOLOGY_PATH);
        spdlog::info("The world ideology axis objects are loaded.");
        this->ideology_axis_count = world_ideology_axis_objects.size();
        this->city_population_identity_templates = load_population_identity_template_objects(CITY_POPULATION_IDENTITY_TEMPLATE_PATH);
        this->party_population_identity_templates = load_population_identity_template_objects(PARTY_POPULATION_IDENTITY_TEMPLATE_PATH);
        spdlog::info("The city population identity templates are loaded.");
        this->world_country_objects = load_country_objects(
                COUNTRY_PATH,
                CITY_PATH,
                city_population_identity_templates,
                world_ideology_axis_objects
                );
        this->world_character_name_base = load_character_name_base(CHARACTER_NAME_BASE_PATH);
        spdlog::info("The countries are loaded.");

    }

    void World::initialize_country()
    {
        for(auto& country: world_country_objects)
        {
            country.create_country_population_identities(world_randomizer);
        }
        spdlog::info("The countries are initialized.");
    }
}