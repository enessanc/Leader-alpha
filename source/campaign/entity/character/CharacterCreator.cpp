//
// Created by tacoe on 6.07.2022.
//

#include "CharacterCreator.h"
#include <random>
#include "source/campaign/entity/population_identity/PopulationIdentityEnums.h"
#include "source/campaign/entity/population_identity/PopulationIdentityTemplate.h"
#include "source/campaign/entity/ideology/IdeologyMathTools.h"
#include "source/tools/JsonTools.h"
#include "spdlog/spdlog.h"

namespace Leader
// static part of this cpp file
{

    static std::wstring generate_character_name(std::mt19937_64* randomizer,
                                                const GenderGroup& gender,
                                                const std::string& character_country_stringId,
                                                const Character_Name_Base& character_names
                                                )
    {
        std::vector<std::string> temp_name;
        std::vector<std::string> temp_surname;

        //selecting surname randomly by given seed
        std::sample(character_names.at(character_country_stringId).at("surnames").begin(),
                    character_names.at(character_country_stringId).at("surnames").end(),
                    std::back_inserter(temp_surname),
                    1,
                    *randomizer
                    );
        std::wstring surname = utf8_to_wstring(temp_surname.at(0));

        //to add naturality and variety, we want some people have two names
        std::uniform_int_distribution<> is_two_named_selector(0,1);
        bool is_two_named = is_two_named_selector(*randomizer);

        //selecting name randomly by given seed
        std::wstring name;
        switch(gender)
        {
            case Male:
                if(is_two_named)
                {
                    std::sample(character_names.at(character_country_stringId).at("male_names").begin(),
                                character_names.at(character_country_stringId).at("male_names").end(),
                                std::back_inserter(temp_name),
                                2,
                                *randomizer
                                );
                    // we should turn into wstrings, because the character names can have special characters
                    name = utf8_to_wstring(temp_name.at(0)) + L" "+ utf8_to_wstring(temp_name.at(1));
                } else
                {
                    std::sample(character_names.at(character_country_stringId).at("male_names").begin(),
                                character_names.at(character_country_stringId).at("male_names").end(),
                                std::back_inserter(temp_name),
                                1,
                                *randomizer
                    );
                    // we should turn into wstrings, because the character names can have special characters
                    name = utf8_to_wstring(temp_name.at(0));
                }
                break;
            case Female:
                if(is_two_named)
                {
                    std::sample(character_names.at(character_country_stringId).at("female_names").begin(),
                                character_names.at(character_country_stringId).at("female_names").end(),
                                std::back_inserter(temp_name),
                                2,
                                *randomizer
                    );
                    // we should turn into wstrings, because the character names can have special characters
                    name = utf8_to_wstring(temp_name.at(0)) + L" "+ utf8_to_wstring(temp_name.at(1));
                } else
                {
                    std::sample(character_names.at(character_country_stringId).at("female_names").begin(),
                                character_names.at(character_country_stringId).at("female_names").end(),
                                std::back_inserter(temp_name),
                                1,
                                *randomizer
                    );
                    // we should turn into wstrings, because the character names can have special characters
                    name = utf8_to_wstring(temp_name.at(0));
                }
                break;
            default:
                spdlog::error("This is an unexpected result in generating character names randomly, program is shutting down...");
                std::exit(EXIT_FAILURE);
        }

        return name + L" " + surname;
    }

    static float find_initial_character_expediture(EconomicalGroup economical_group)
    {
        switch(economical_group)
        {
            case Poor:
                return -500.0;
            case Middle:
                return 0.0;
            case Rich:
                return +500.0;
            default:
                spdlog::error("This is an unexpected result in calculating character initial expenditure, program is shutting down...");
                std::exit(EXIT_FAILURE);
        }
    }

    static CharacterIdentity create_character_identity_pure_randomly(std::mt19937_64 *randomizer)
    {
        //TODO: Currently, this character creation is pure random; but in the future we want it to be affected by city,country,party states and these states must be moddable
        std::uniform_int_distribution<int> identity_level_interval(-10,10);
        CharacterIdentity new_character_identity;
        new_character_identity.charisma = (float)identity_level_interval(*randomizer);
        new_character_identity.harmony = (float)identity_level_interval(*randomizer);
        new_character_identity.intelligence = (float)identity_level_interval(*randomizer);
        new_character_identity.health = (float)identity_level_interval(*randomizer);
        return new_character_identity;
    }

    static const IdeologyCoordinate party_unused_ideology_coord;
    // This global variable is just placeholder to create default variables in the static function named initial_character_creator

    static Character initial_character_creator(std::mt19937_64 *randomizer,
                                               const std::string& character_stringId,
                                               const std::string& city_stringId,
                                               PopulationIdentityTemplate* city_population_identity_template,
                                               const IdeologyCoordinate& city_ideology_tendency,
                                               const std::string& country_stringId,
                                               const Character_Name_Base& character_names,
                                               std::vector<IdeologyAxis> ideology_axis_objects,
                                               const std::string& party_stringId = "neutral",
                                               PopulationIdentityTemplate* party_population_identity_template = nullptr,
                                               const IdeologyCoordinate& party_ideology_tendency = party_unused_ideology_coord
                                               )
    {
        Character new_character;
        new_character.set_stringId(character_stringId);
        new_character.set_city_stringId(city_stringId);
        new_character.set_party_stringId(party_stringId);
        new_character.set_country_stringId(country_stringId);

        // choosing population identity of characters
        PopulationIdentityTemplate character_population_identity_template = *city_population_identity_template;
        if(party_population_identity_template != nullptr)
        {
            character_population_identity_template = merge_population_identity_templates(*city_population_identity_template, *party_population_identity_template);
        }
        PopulationIdentity character_population_identity = population_identity_creator(randomizer,character_population_identity_template,1);
        new_character.set_population_identity(character_population_identity);

        //generating name for character
        new_character.set_name(generate_character_name(randomizer,
                                                       new_character.get_population_identity().get_gender(),
                                                       new_character.get_country_stringId(),
                                                       character_names
                                                       )
                              );

        //calculating character initial ideology
        IdeologyCoordinate character_ideology_tendency = city_ideology_tendency;
        if(party_population_identity_template != nullptr)
        {
            character_ideology_tendency = merge_ideology_levels(city_ideology_tendency, party_ideology_tendency, ideology_axis_objects);
        }
        new_character.set_character_ideology(ideology_level_randomizer(randomizer,
                                                                       character_ideology_tendency,
                                                                       3.0,
                                                                       ideology_axis_objects
                                                                       )
                              );

        //calculating character initial expenditure
        new_character.set_expenditure(find_initial_character_expediture(new_character.get_population_identity().get_economical_group()));
        //choosing character initial identity
        new_character.set_character_identity(create_character_identity_pure_randomly(randomizer));
        return new_character;

        //TODO: Choice character initial traits
    }

    void initial_player_party_character_overloader()
    {
        //TODO: Overload character traits and  character identities given diffuculty
    }


}

namespace Leader
// header part of this cpp file
{
    Character_Name_Base load_character_name_base(const std::string& name_base_file_path)
    {
        Character_Name_Base name_base;
        json name_base_data = load_json_file(name_base_file_path);
        return name_base_data;
    }
}