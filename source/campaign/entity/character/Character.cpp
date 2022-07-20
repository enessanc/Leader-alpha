//
// Created by tacoe on 27.04.2022.
//

#include "Character.h"
#include "source/tools/JsonTools.h"
#include "spdlog/spdlog.h"

namespace Leader
{
    void CharacterTrait::set_name(const std::string &_n)
    {
        name = _n;
    }

    void CharacterTrait::set_status(const std::string &_s)
    {
        status = _s;
    }

    std::string CharacterTrait::get_name() const
    {
        return name;
    }

    std::string CharacterTrait::get_status() const
    {
        return status;
    }

    void CharacterTrait::set_country_stringId(const std::string &_s)
    {
        country_stringId = _s;
    }

    void CharacterTrait::set_is_rare(const bool &_b)
    {
        _is_rare = _b;
    }

    std::string CharacterTrait::get_country_stringId() const
    {
        return country_stringId;
    }

    bool CharacterTrait::is_rare() const
    {
        return _is_rare;
    }

    Character_Trait_Map load_character_traits(const std::string &character_trait_file)
    {
        Character_Trait_Map character_traits;
        json trait_data = load_json_file(character_trait_file);
        for (auto trait: trait_data) {
            CharacterTrait new_trait;
            new_trait.set_stringId(trait.at("stringId"));
            new_trait.set_name(trait.at("name"));
            new_trait.set_status(trait.at("status"));
            new_trait.set_country_stringId(trait.at("country_stringId"));
            new_trait.set_is_rare(trait.at("is_rare"));
            // TODO: Add other attributes of character traits from json file, when filled.
            spdlog::info("The character trait named {} are loaded.", new_trait.get_name());
            character_traits[new_trait.get_status()][new_trait.get_stringId()] = new_trait;
        }
        return character_traits;
    }
}

namespace Leader
{
    void Character::set_name(const std::wstring &_name)
    {
        name = _name;
    }

    void Character::set_country_stringId(const std::string &_id)
    {
        country_stringId = _id;
    }

    void Character::set_city_stringId(const std::string &_id)
    {
        city_stringId = _id;
    }

    void Character::set_party_stringId(const std::string &_id)
    {
        party_stringId = _id;
    }

    void Character::set_population_identity(const PopulationIdentity &_identity)
    {
        population_identity = _identity;
        switch(population_identity.get_economical_group())
        {
            case Poor:
                expenditure = -500.0;
                break;
            case Middle:
                expenditure = 0;
                break;
            case Rich:
                expenditure = 500.0;
                break;
            case EconomicalGroup_Count:
                //never ever should hit here!
                break;
        }
    }

    void Character::set_character_ideology_initially(const std::vector<float> &ideology_levels, std::vector<IdeologyAxis> &ideology_axis_objects)
    {
        ideology = IdeologyCoordinate(ideology_levels, ideology_axis_objects);
    }

    void Character::set_character_ideology(const std::vector<float> &ideology_levels)
    {
        ideology.set_ideology_points_externally(ideology_levels);
    }

    void Character::add_visible_trait(const CharacterTrait &_trait)
    {
        // TODO: May be, filtering the traits here might be better idea.
        visible_traits.push_back(_trait);
    }

    void Character::add_invisible_trait(const CharacterTrait &_trait)
    {
        // TODO: May be, filtering the traits in here might be better idea.
        invisible_traits.push_back(_trait);
    }

    void Character::set_character_identity(const CharacterIdentity &_identity)
    {
        character_identity = _identity;
    }

    void Character::set_character_ideology(const IdeologyCoordinate &_coord)
    {
        ideology = _coord;
    }

    std::wstring Character::get_name() const
    {
        return name;
    }

    std::string Character::get_country_stringId() const
    {
        return country_stringId;
    }

    std::string Character::get_city_stringId() const
    {
        return city_stringId;
    }

    std::string Character::get_party_stringId() const
    {
        return party_stringId;
    }

    PopulationIdentity &Character::get_population_identity()
    {
        return population_identity;
    }

    CharacterIdentity &Character::get_character_identity()
    {
        return character_identity;
    }

    IdeologyCoordinate &Character::get_ideology()
    {
        return ideology;
    }

    std::vector<CharacterTrait> &Character::get_visible_traits()
    {
        return visible_traits;
    }

    std::vector<CharacterTrait> &Character::get_invisible_traits()
    {
        return invisible_traits;
    }

    void Character::set_expenditure(const float& ex)
    {
        expenditure = ex;
    }

    float Character::get_expenditure() const
    {
        return expenditure;
    }


}

