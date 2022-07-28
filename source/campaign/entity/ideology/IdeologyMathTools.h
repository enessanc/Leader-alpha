//
// Created by tacoe on 29.04.2022.
//

#ifndef LEADER_IDEOLOGYMATHTOOLS_H
#define LEADER_IDEOLOGYMATHTOOLS_H

#include <vector>
#include "source/campaign/entity/ideology/IdeologyCoordinate.h"
#include <random>

namespace Leader
{
    IdeologyCoordinate ideology_level_randomizer(std::mt19937_64* generator,
                                                 const IdeologyCoordinate& center,
                                                 const float& border,
                                                 std::vector<IdeologyAxis> &ideology_axis_objects);

    IdeologyCoordinate merge_ideology_levels(const IdeologyCoordinate& first,
                                             const IdeologyCoordinate& second,
                                             std::vector<IdeologyAxis> &ideology_axis_objects);

    float ideology_distance_calculator(const IdeologyCoordinate& first, const IdeologyCoordinate& second);
}





#endif //LEADER_IDEOLOGYMATHTOOLS_H
