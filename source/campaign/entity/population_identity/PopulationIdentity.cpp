//
// Created by tacoe on 26.04.2022.
//

#include "PopulationIdentity.h"
#include "source/preference/constants.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace Leader
{
    PopulationIdentity::PopulationIdentity(const GenderGroup& _g, const AgeGroup& _a, const JobGroup& _j,
                                           const EconomicalGroup& _ec, const EducationalGroup& _edu,
                                           const unsigned long& p)
    {
        this->gender = _g;
        this->age_group = _a;
        this->age = this->set_age_initially();
        this->job_group = _j;
        this->economical_group = _ec;
        this->educational_group = _edu;
        this->corresponding_population = p;
    }

    /*
     * This member function sets the age of population identity externally given random number generator object and age group.
     */
    void PopulationIdentity::set_age_externally(std::mt19937_64 *generator, const AgeGroup &_a)
    {
        this->age_group = _a;
        std::uniform_int_distribution<unsigned short> child_age_interval(1,CHILD_AGE);
        std::uniform_int_distribution<unsigned short> teen_age_interval(CHILD_AGE,29);
        std::uniform_int_distribution<unsigned short> adult_age_interval(30,65);
        std::uniform_int_distribution<unsigned short> old_age_interval(65,MAXIMUM_AGE);

        switch (age_group) {
            case AgeGroup::Child:
                this->age = child_age_interval(*generator);
                return;
            case AgeGroup::Teen:
                this->age = teen_age_interval(*generator);
                return;
            case AgeGroup::Adult:
                this->age = adult_age_interval(*generator);
                return;
            case AgeGroup::Old:
                this->age = old_age_interval(*generator);
                return;
            default:
                spdlog::error("Never ever should hit here!(while externally selecting the age for population identities");
                std::exit(-1);
        }
    }

    unsigned short PopulationIdentity::set_age_initially() {
        // Setting age defaultly by given age group
        switch (this->age_group)
        {
            case AgeGroup::Child:
                return 5;
            case AgeGroup::Teen:
                return 25;
            case AgeGroup::Adult:
                return 40;
            case AgeGroup::Old:
                return 70;
            default:
                spdlog::error("Never ever should hit here!(while selecting the age for population identities initially)");
                std::exit(-1);
        }
    }

    void PopulationIdentity::log_population_identity(const std::string& party_str) const
    {
        std::string s1 = "\nIdentity Party: " + party_str + "\n";
        std::string s2 = "Gender Group: " + get_gender_s() + "\n";
        std::string s3 = "Age Group: " + get_age_group_s() + "\n";
        std::string s4 = "Job Group: " + get_job_group_s() + "\n";
        std::string s5 = "Economical Group: " + get_economical_group_s() + "\n";
        std::string s6 = "Educational Group: " + get_educational_group_s() + "\n";

        std::string result = s1 + s2 + s3 + s4 + s5 + s6;
        spdlog::trace(result);
    }

    std::string PopulationIdentity::get_gender_s() const
    {

        std::string result;
        switch(gender)
        {
            case Male:
                result = "Male";
                break;
            case Female:
                result = "Female";
                break;
            case GenderGroup_Count:
                //never ever should hit here
                break;
        }
        return result;
    }

    std::string PopulationIdentity::get_age_group_s() const
    {
        std::string result;
        switch(age_group)
        {
            case Child:
                result = "Child";
                break;
            case Teen:
                result = "Teen";
                break;
            case Adult:
                result = "Adult";
                break;
            case Old:
                result = "Old";
                break;
            case AgeGroup_Count:
                //never ever should hit here
                break;
        }
        return result;
    }

    std::string PopulationIdentity::get_job_group_s() const
    {
        std::string result;
        switch(job_group)
        {
            case Student:
                result = "Student";
                break;
            case Service:
                result = "Service";
                break;
            case Mechanic:
                result = "Mechanic";
                break;
            case Agriculture:
                result = "Agriculture";
                break;
            case Workless:
                result = "Workless";
                break;
            case JobGroup_Count:
                //never ever should hit here
                break;
        }
        return result;
    }

    std::string PopulationIdentity::get_economical_group_s() const
    {
        std::string result;
        switch(economical_group)
        {
            case Poor:
                result = "Poor";
                break;
            case Middle:
                result = "Middle";
                break;
            case Rich:
                result = "Rich";
                break;
            case EconomicalGroup_Count:
                //never ever should hit here
                break;
        }
        return result;
    }

    std::string PopulationIdentity::get_educational_group_s() const {
        std::string result;
        switch(educational_group)
        {
            case Illiterate:
                result = "Illiterate";
                break;
            case Elementary:
                result = "Elementary";
                break;
            case Highschool:
                result = "Highschool";
                break;
            case University:
                result = "University";
                break;
            case EducationalGroup_Count:
                //never ever should hit here
                break;
        }
        return result;
    }

    PopulationIdentity population_identity_creator(std::mt19937_64 *generator,const PopulationIdentityTemplate &atemplate,
                                                   const unsigned long &corresponding_population)
    {
        PopulationIdentity new_population_identity;

        new_population_identity.set_corresponding_population(corresponding_population);

        GenderGroup choicen_gender = weighted_enum_choicer(generator, atemplate.gender_groups_weights, GenderGroup::GenderGroup_Count);
        new_population_identity.set_gender(choicen_gender);

        AgeGroup choicen_age_group = weighted_enum_choicer(generator, atemplate.age_groups_weights, AgeGroup::AgeGroup_Count);
        new_population_identity.set_age_externally(generator,choicen_age_group);

        JobGroup choicen_job_group = weighted_enum_choicer(generator, atemplate.job_groups_weights, JobGroup::JobGroup_Count);
        new_population_identity.set_job_group(choicen_job_group);

        EconomicalGroup choicen_economical_group = weighted_enum_choicer(generator, atemplate.economical_groups_weights,
                                                                         EconomicalGroup::EconomicalGroup_Count);
        new_population_identity.set_economical_group(choicen_economical_group);

        EducationalGroup choicen_educational_group = weighted_enum_choicer(generator, atemplate.educational_groups_weights,
                                                                           EducationalGroup::EducationalGroup_Count);
        new_population_identity.set_educational_group(choicen_educational_group);

        return new_population_identity;
    }
}

