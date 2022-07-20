//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_PARTY_H
#define LEADER_PARTY_H
#include "source/campaign/entity/base/Entity.h"
#include "source/campaign/entity/ideology/IdeologyCoordinate.h"
#include "source/campaign/entity/population_identity/PopulationIdentityTemplate.h"

namespace Leader
{
    class Party : public Entity
    {
    private:
        std::string abbreviation;
        std::string country_stringId;
        IdeologyCoordinate ideology;
        PopulationIdentityTemplate* population_identity_template{};

    public:
        Party() = default;
        void set_abbreviation(const std::string& _abbr);
        void set_country_stringId(const std::string& _id);
        void set_ideology_initially(const std::vector<float>& ideology_levels, std::vector<IdeologyAxis> &ideology_axis_objects);
        void set_ideology(const std::vector<float>& _levels);
        void set_population_identity_template(PopulationIdentityTemplate* _template);
        void set_party_ideology_initially(const std::vector<float>& ideology_tendency_levels, std::vector<IdeologyAxis> &ideology_axis_objects);

        [[nodiscard]] std::string get_abbreviation() const;
        [[nodiscard]] std::string get_country_stringId() const;
        IdeologyCoordinate& get_ideology();
        PopulationIdentityTemplate* get_population_identity_template();

        void log_party() const;


    };
}


#endif //LEADER_PARTY_H
