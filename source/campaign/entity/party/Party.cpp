//
// Created by tacoe on 27.04.2022.
//

#include "source/tools/JsonTools.h"
#include "spdlog/spdlog.h"
#include "Party.h"

namespace Leader
{
    void Party::set_ideology_initially(const std::vector<float> &ideology_levels, std::vector<IdeologyAxis> &ideology_axis_objects)
    {
        ideology = IdeologyCoordinate(ideology_levels,ideology_axis_objects);
    }

    void Party::set_abbreviation(const std::string &_abbr)
    {
        abbreviation = _abbr;
    }

    void Party::set_country_stringId(const std::string &_id)
    {
        country_stringId = _id;
    }

    void Party::set_ideology(const std::vector<float> &_levels)
    {
        ideology.set_ideology_points_externally(_levels);
    }

    std::string Party::get_abbreviation() const
    {
        return abbreviation;
    }

    std::string Party::get_country_stringId() const
    {
        return country_stringId;
    }

    IdeologyCoordinate &Party::get_ideology() {
        return ideology;
    }

    PopulationIdentityTemplate *Party::get_population_identity_template()
    {
        return population_identity_template;
    }

    void Party::set_population_identity_template(PopulationIdentityTemplate *_template)
    {
        population_identity_template = _template;
    }

    void Party::set_party_ideology_initially(const std::vector<float>& ideology_tendency_levels, std::vector<IdeologyAxis> &ideology_axis_objects)
    {
        ideology = IdeologyCoordinate(ideology_tendency_levels, ideology_axis_objects);
    }

    void Party::log_party() const
    {
        std::string result = "\nThe party : " +abbreviation + "is created in " + country_stringId + "\n";
        spdlog::trace(result);
    }

    std::vector<Party> load_party_objects(const std::string &party_file,
                                        std::unordered_map<std::string, PopulationIdentityTemplate>& party_population_identity_objects,
                                        std::vector<IdeologyAxis>& ideology_axis_objects,
                                        const std::string& country_stringId
    )
    {
        std::vector<Party> city_objects;
        json data = load_json_file(party_file);
        for(const auto& party: data)
        {
            if(country_stringId == party.at("country_stringId"))
            {
                Party new_party;
                new_party.set_stringId(party.at("stringId"));
                new_party.set_country_stringId(country_stringId);
                new_party.set_abbreviation(party.at("abbreviation"));
                new_party.set_population_identity_template(&party_population_identity_objects[party.at("party_character_template_stringId")]);
                new_party.set_party_ideology_initially(party.at("ideology"), ideology_axis_objects);
                city_objects.push_back(new_party);
                new_party.log_party();
            }
        }
        return city_objects;
    }

}


