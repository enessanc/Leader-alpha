//
// Created by tacoe on 27.04.2022.
//

#ifndef LEADER_RANDOMIZER_H
#define LEADER_RANDOMIZER_H
#include <random>

namespace Leader
{
    class Randomizer
    {
    private:
        int current_seed;
    public:
        Randomizer();
        std::mt19937_64 generator;
        void renew_seed();
        void set_seed(const int& _seed);
    };
}

#endif //LEADER_RANDOMIZER_H
