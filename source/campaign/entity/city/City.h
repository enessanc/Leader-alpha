//
// Created by tacoe on 26.04.2022.
//

#ifndef LEADER_CITY_H
#define LEADER_CITY_H
#include "source/campaign/entity/base/Entity.h"
#include "source/campaign/entity/population_identity/PopulationIdentity.h"
#include "source/campaign/entity/population_identity/PopulationIdentityTemplate.h"
#include "source/campaign/entity/ideology/IdeologyCoordinate.h"
#include "source/campaign/entity/character/Character.h"
#include "source/tools/JsonTools.h"
#include <string>
#include <unordered_map>
#include <filesystem>


namespace Leader
{
    class Country;

    class City : public Entity
    {

    private:

        std::wstring name; // the original name of city
        std::string country_stringId; // the unique string id of country of this city
        unsigned long population{}; // the current population of city
        unsigned int current_population_identity_number{}; // current population identity number of this city
        unsigned int neutral_character_organization_limit{}; // the number limit for neutral characters in this city
        std::vector<Character> city_neutral_characters; // city neutral characters
        float stability{}; // the current stability of this city
        float prosperity{}; // the current prosperity of this city
        float moral{}; // the current model of this city
        PopulationIdentityTemplate* population_identity_template{}; // corresponding population identity template for city population identities and characters
        std::vector <PopulationIdentity> city_population_identity_vector; // population identities of this city
        IdeologyCoordinate ideology_tendency; // the ideology tendency of this city



    public:

        City() = default;
        void create_city_population_identities(Randomizer& randomizer);
        void log_city() const;
        //setters
        void set_name(const std::wstring& _n);
        void set_country(const std::string& _id);
        void set_population(const unsigned long& _p, const bool& initial = false);
        void set_stability(const float& _s);
        void set_prosperity(const float& _pr) {prosperity = _pr;}
        void set_moral(const float& _m) {moral=_m;}
        void set_population_identity_template(PopulationIdentityTemplate* _template);
        void set_city_ideology_initially(const std::vector<float> &ideology_tendency_levels,
                                         std::vector<IdeologyAxis> &ideology_axis_objects); // must be used for initialization
        void set_city_ideology_tendency(const std::vector<float>& _levels);
        void set_neutral_characters_externally(std::vector<Character> &neutral_characters) {city_neutral_characters = neutral_characters;}
        void add_neutral_character(Character &neutral_character) {city_neutral_characters.push_back(neutral_character);}


        //getters
        [[nodiscard]] std::wstring get_name() const;
        [[nodiscard]] std::string get_country();
        [[nodiscard]] unsigned long get_population() const;
        [[nodiscard]] float get_stability() const;
        [[nodiscard]] float get_prosperity() const;
        [[nodiscard]] float get_moral() const;
        [[nodiscard]] PopulationIdentityTemplate* get_population_identity_template() const;
        std::vector <PopulationIdentity>& get_population_identity_vector();
        IdeologyCoordinate& get_ideology_tendency();
        std::vector<Character>& get_neutral_characters() {return city_neutral_characters;}
    };

    std::vector <City> load_city_objects(const std::string& city_file,
                                         std::unordered_map<std::string, PopulationIdentityTemplate>& city_population_identity_objects,
                                         std::vector<IdeologyAxis>& ideology_axis_object,
                                         const std::string& country_stringId);



}
#endif //LEADER_CITY_H
