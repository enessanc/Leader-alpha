//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_COUNTRY_H
#define LEADER_COUNTRY_H
#include "source/campaign/entity/base/Entity.h"
#include "source/campaign/entity/city/City.h"
#include <filesystem>
#include <vector>

namespace Leader
{

    class Country : public Entity
    {
    private:
        std::vector <City> city_objects;
    public:
        Country() = default;
        void set_city_objects(std::vector <City> _city_objects)
        {
            city_objects = std::move(_city_objects);
        }
        std::vector <City>& get_city_objects();

        void create_country_population_identities(Randomizer& randomizer);
    };

    std::vector <Country> load_country_objects(const std::string& country_file,
                                               const std::string& city_file,
                                               std::unordered_map<std::string,
                                               PopulationIdentityTemplate>& city_population_identity_objects,
                                               std::vector<IdeologyAxis>& ideology_axis_object);

}
#endif //LEADER_COUNTRY_H
