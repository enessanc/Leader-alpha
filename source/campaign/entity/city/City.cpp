//
// Created by tacoe on 26.04.2022.
//

#include "City.h"
#include "source/preference/constants.h"
#include "source/tools/JsonTools.h"
#include "spdlog/spdlog.h"

namespace Leader {

    std::vector<City> load_city_objects(const std::string &city_file,
                                        std::unordered_map<std::string, PopulationIdentityTemplate>& city_population_identity_objects,
                                        std::vector<IdeologyAxis>& ideology_axis_objects,
                                        const std::string& country_stringId
                                        )
    {
        std::vector<City> city_objects;
        json data = load_json_file(city_file);
        for(const auto& city: data)
        {
            if(country_stringId == city.at("country_stringId"))
            {
                City new_city;
                new_city.set_stringId(city.at("stringId"));
                new_city.set_name(utf8_to_wstring(city.at("name"))); // we should cast string to wstring to avoid custom character problem of city names
                new_city.set_country(country_stringId);
                new_city.set_population(city.at("population"), true);
                new_city.set_stability(city.at("stability"));
                new_city.set_prosperity(city.at("prosperity"));
                new_city.set_moral(city.at("moral"));
                new_city.set_population_identity_template(&city_population_identity_objects[city.at("population_identity_template_stringId")]);
                new_city.set_city_ideology_initially(city.at("initial_ideology_levels"), ideology_axis_objects);
                city_objects.push_back(new_city);
                new_city.log_city();
            }
        }
        return city_objects;
    }

    void City::set_city_ideology_initially(const std::vector<float>& ideology_tendency_levels,
                                           std::vector<IdeologyAxis> &ideology_axis_objects
                                            )
    {
        ideology_tendency = IdeologyCoordinate(ideology_tendency_levels, ideology_axis_objects);
    }

    void City::set_population(const unsigned long &_p, const bool &initial)
    {
        population = _p;
        if(initial)
        {
            current_population_identity_number = (int)population / POPULATION_IDENTITY_TOLERANCE;
        }

        if(population<100000)
        {
            neutral_character_organization_limit = 5;
        }
        else if(population>=100000 && population< 500000)
        {
            neutral_character_organization_limit = 10;
        }
        else if(population>=500000 && population<1000000)
        {
            neutral_character_organization_limit = 15;
        }
        else if(population>=1000000 && population < 5000000)
        {
            neutral_character_organization_limit = 20;
        }
        else if(population>=5000000)
        {
            neutral_character_organization_limit = 25;
        }
    }

    void City::create_city_population_identities(Randomizer& randomizer)
    {
        for(int i = 0; i < current_population_identity_number; i++)
        {
            PopulationIdentity new_population_identity = population_identity_creator(&randomizer.generator,*population_identity_template,
                                                                                     POPULATION_IDENTITY_TOLERANCE);
            city_population_identity_vector.push_back(new_population_identity);
            new_population_identity.log_population_identity("city-population-identity");
            randomizer.renew_seed();
        }
        spdlog::trace("In the city with id {}, the creation of population identities are completed.",stringId);
    }

    void City::log_city() const
    {
        std::string s1 = "\nThe city with id: " + stringId + "is created in " + country_stringId + "\n";
        std::string s2 = "Population: " + std::to_string(population) + "\n";
        std::string s3 = "Prosperity: " + std::to_string(prosperity) + "\n";
        std::string s4 = "Stability: " + std::to_string(stability) + "\n";
        std::string s5 = "Moral: " + std::to_string(moral) + "\n";

        std::string result = s1+s2+s3+s4+s5;
        spdlog::trace(result);
    }

    void City::set_name(const std::wstring &_n)
    {
        name = _n;
    }

    void City::set_country(const std::string &_id)
    {
        country_stringId = _id;
    }

    void City::set_stability(const float &_s)
    {
        stability = _s;
    }

    void City::set_population_identity_template(PopulationIdentityTemplate *_template)
    {
        population_identity_template = _template;
    }

    void City::set_city_ideology_tendency(const std::vector<float> &_levels)
    {
        ideology_tendency.set_ideology_points_externally(_levels);
    }

    std::wstring City::get_name() const
    {
        return name;
    }

    std::string City::get_country()
    {
        return country_stringId;
    }

    float City::get_stability() const
    {
        return stability;
    }

    unsigned long City::get_population() const
    {
        return population;
    }

    float City::get_prosperity() const
    {
        return prosperity;
    }

    float City::get_moral() const
    {
        return moral;
    }

    PopulationIdentityTemplate *City::get_population_identity_template() const
    {
        return population_identity_template;
    }

    std::vector<PopulationIdentity> &City::get_population_identity_vector()
    {
        return city_population_identity_vector;
    }

    IdeologyCoordinate &City::get_ideology_tendency()
    {
        return ideology_tendency;
    }
}