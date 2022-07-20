//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_CHARACTER_H
#define LEADER_CHARACTER_H
#include "source/campaign/entity/base/Entity.h"
#include "source/campaign/entity/ideology/IdeologyCoordinate.h"
#include "source/campaign/entity/population_identity/PopulationIdentity.h"
#include <string>
#include <vector>

namespace Leader

{
    class CharacterTrait: public Entity
    {
    private:
        std::string name;
        std::string status;
        std::string country_stringId;
        bool _is_rare{};
    public:
        CharacterTrait() = default;
        void set_name(const std::string& _n);
        void set_status(const std::string& _s);
        void set_country_stringId(const std::string& _s);
        void set_is_rare(const bool& _b);
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] std::string get_status() const;
        [[nodiscard]] std::string get_country_stringId() const;
        [[nodiscard]] bool is_rare() const;
    };

    typedef std::unordered_map <std::string , std::unordered_map< std::string, CharacterTrait> > Character_Trait_Map;
    Character_Trait_Map load_character_traits(const std::string& character_trait_file);


    struct CharacterIdentity
    {
        float intelligence{};
        float charisma{};
        float harmony{};
        float health{};
    };


    class Character : public Entity
    {
    private:
        std::wstring name;
        std::string country_stringId;
        std::string city_stringId;
        std::string party_stringId;
        PopulationIdentity population_identity;
        CharacterIdentity character_identity;
        IdeologyCoordinate ideology;
        std::vector <CharacterTrait> visible_traits;
        std::vector <CharacterTrait> invisible_traits;
        float expenditure{};

    public:
        Character() = default;
        //setters
        void set_name(const std::wstring& _name);
        void set_country_stringId(const std::string& _id);
        void set_city_stringId(const std::string& _id);
        void set_party_stringId(const std::string& _id);
        void set_population_identity(const PopulationIdentity& _identity);
        void set_character_ideology_initially(const std::vector<float>& ideology_levels, std::vector<IdeologyAxis> &ideology_axis_objects);
        void set_character_ideology(const std::vector<float>& ideology_levels);
        void set_character_ideology(const IdeologyCoordinate& _coord);
        void add_visible_trait(const CharacterTrait& _trait);
        void add_invisible_trait(const CharacterTrait& _trait);
        void set_character_identity(const CharacterIdentity& _identity);
        void set_expenditure(const float& ex);
        //getters
        [[nodiscard]] std::wstring get_name() const;
        [[nodiscard]] std::string get_country_stringId() const;
        [[nodiscard]] std::string get_city_stringId() const;
        [[nodiscard]] std::string get_party_stringId() const;
        [[nodiscard]] float get_expenditure() const;
        PopulationIdentity& get_population_identity();
        CharacterIdentity& get_character_identity();
        IdeologyCoordinate& get_ideology();
        std::vector<CharacterTrait>& get_visible_traits();
        std::vector<CharacterTrait>& get_invisible_traits();
    };
}



#endif //LEADER_CHARACTER_H
