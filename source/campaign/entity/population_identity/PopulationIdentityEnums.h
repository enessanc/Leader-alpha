//
// Created by tacoe on 26.04.2022.
//


#ifndef LEADER_POPULATIONIDENTITYENUMS_H
#define LEADER_POPULATIONIDENTITYENUMS_H

#include <random>


namespace Leader
{

    enum GenderGroup
    {
        Male = 0,
        Female,
        GenderGroup_Count // must be last and its value must be equal to the number of possible enums
    };

    enum AgeGroup
    {
        Child = 0,
        Teen,
        Adult,
        Old,
        AgeGroup_Count // must be last and its value must be equal to the number of possible enums
    };

    enum JobGroup
    {
        Student = 0,
        Service,
        Mechanic,
        Agriculture,
        Workless,
        JobGroup_Count // must be last and its value must be equal to the number of possible enums
    };

    enum EconomicalGroup
    {
        Poor = 0,
        Middle,
        Rich,
        EconomicalGroup_Count // must be last and its value must be equal to the number of possible enums
    };

    enum EducationalGroup
    {
        Illiterate = 0,
        Elementary,
        Highschool,
        University,
        EducationalGroup_Count // must be last and its value must be equal to the number of possible enums
    };

    template<typename ENUM>
    ENUM weighted_enum_choicer(std::mt19937_64* randomizer, const std::vector<float>& weights,const ENUM& last_enum)
    {
        if(last_enum != weights.size())
        {
            // TODO: should be logged the critical error: The length of weights and the number of choices must be same!
            exit(-1);
        }
        std::discrete_distribution<int> distribution(std::begin(weights),std::end(weights));
        ENUM result = static_cast<ENUM>(distribution(*randomizer));
        return result;
    }

}

#endif //LEADER_POPULATIONIDENTITYENUMS_H
