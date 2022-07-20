//
// Created by tacoe on 27.04.2022.
//

#include "Randomizer.h"

namespace Leader
{
    Randomizer::Randomizer()
    {
        this->current_seed = 0;
        this->generator = std::mt19937_64(this->current_seed);
    }

    void Randomizer::renew_seed() {
        this->current_seed++; // incrementing the seed for protecting predictable randomness !!Must call manually, when needed!!!
        this->generator.seed(this->current_seed);
    }

    void Randomizer::set_seed(const int &_seed)
    {
        this->current_seed = _seed;
        this->generator.seed(this->current_seed);
    }


}