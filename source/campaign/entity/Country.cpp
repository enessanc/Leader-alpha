//
// Created by tacoe on 27.04.2022.
//

#include "Country.h"
#include "source/tools/JsonTools.h"
#include <spdlog/spdlog.h>


namespace Leader
{
    std::vector<Country> load_country_objects(const std::string &country_file,
                                              const std::string &city_file,
                                              std::unordered_map<std::string,
                                              PopulationIdentityTemplate> &city_population_identity_objects,
                                              std::vector<IdeologyAxis> &ideology_axis_object)
    {
        std::vector<Country> country_objects;
        json country_data = load_json_file(country_file);
        for(auto country: country_data)
        {
            Country new_country;
            new_country.set_stringId(country.at("stringId"));
            std::vector<City> city_objects = load_city_objects(city_file,
                                                               city_population_identity_objects,
                                                               ideology_axis_object,
                                                               new_country.get_stringId());
            spdlog::info("The cities in country {} are loaded.", new_country.get_stringId());
            new_country.set_city_objects(city_objects);
            country_objects.push_back(new_country);
        }
        return country_objects;
    }

    void Country::create_country_population_identities(Randomizer &randomizer)
    {
        for(auto& city: city_objects)
        {
            city.create_city_population_identities(randomizer);
        }
        spdlog::info("The creation of city population identities is completed in {}.",stringId);
    }

    std::vector<City>& Country::get_city_objects()
    {
        return city_objects;
    }
}