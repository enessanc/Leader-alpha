//
// Created by tacoe on 26.04.2022.
//

#ifndef LEADER_POPULATIONIDENTITY_H
#define LEADER_POPULATIONIDENTITY_H
#include "source/campaign/entity/population_identity/PopulationIdentityEnums.h"
#include "source/campaign/entity/population_identity/PopulationIdentityTemplate.h"
#include "source/tools/Randomizer.h"
#include <random>
namespace Leader
{
    class PopulationIdentity
    /*
     * This class has two main mission in the game. Firstly, it represents the information of corresponding
     * population units in the cities. Second, this class is contained from each character in the game.
     */
    {
    private:
        GenderGroup gender{}; // The gender of population identity Default Enums = (Male, Female)
        AgeGroup age_group{}; // The age group of population identity Default Enums  = (Child, Teen, Adult, Old)
        unsigned short age{}; // The age of population identity which is initially determined by given age group
        JobGroup job_group{}; // The job group of population identity Default Enums = (Student, Service, Mechanic, Agriculture, Workless)
        EconomicalGroup economical_group{}; // The economical group of population identity Default Enums  = (Poor, Middle, Rich)
        EducationalGroup educational_group{}; // The economical group of population identity Default Enums  = (Poor, Middle, Rich)
        unsigned long corresponding_population{}; // The corresponding population of population identity, default value is 1
        unsigned short set_age_initially();
    public:
        PopulationIdentity() = default;
        PopulationIdentity(const GenderGroup& _g, const AgeGroup& _a, const JobGroup& _j,
                           const EconomicalGroup& _ec, const EducationalGroup& _edu,
                           const unsigned long &p = 1);

        //setters
        void set_gender(const GenderGroup& _g) {this->gender = _g;}
        void set_age_externally(std::mt19937_64 *generator, const AgeGroup& _a);
        void set_job_group(const JobGroup& _j) {this->job_group = _j;}
        void set_economical_group(const EconomicalGroup& _ec) {this->economical_group = _ec;}
        void set_educational_group(const EducationalGroup& _edu) {this->educational_group = _edu;}
        void set_corresponding_population(const unsigned long &p = 1) {this->corresponding_population = p;}

        void log_population_identity(const std::string& party_str) const;

        //getters
        [[nodiscard]] GenderGroup get_gender() const {return this->gender;}
        [[nodiscard]] std::string get_gender_s() const;
        [[nodiscard]] unsigned short get_age() const {return this->age;}
        [[nodiscard]] AgeGroup get_age_group() const {return this->age_group;}
        [[nodiscard]] std::string get_age_group_s() const;
        [[nodiscard]] JobGroup get_job_group() const {return this->job_group;}
        [[nodiscard]] std::string get_job_group_s() const;
        [[nodiscard]] EconomicalGroup get_economical_group() const {return this->economical_group;}
        [[nodiscard]] std::string get_economical_group_s() const;
        [[nodiscard]] EducationalGroup get_educational_group() const {return this->educational_group;}
        [[nodiscard]] std::string get_educational_group_s() const;
        [[nodiscard]] unsigned long get_corresponding_population() const {return this->corresponding_population;}
    };

    PopulationIdentity population_identity_creator(std::mt19937_64 *generator, const PopulationIdentityTemplate& atemplate,
                                                   const unsigned long &corresponding_population);

}
#endif //LEADER_POPULATIONIDENTITY_H
