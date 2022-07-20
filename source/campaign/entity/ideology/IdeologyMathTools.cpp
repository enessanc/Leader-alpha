//
// Created by tacoe on 29.04.2022.
//

#include "IdeologyMathTools.h"
#include "spdlog/include/spdlog/spdlog.h"

namespace Leader
// static part of these transaction units
{
   static std::vector<float> _ideology_level_randomizer(std::mt19937_64 *generator, const std::vector<float> &center, const float &border)
    {
        std::vector<float> result;
        for (const auto &level: center)
        {
            std::uniform_real_distribution<float> distribution(level - border, level + border);
            result.push_back(distribution(*generator));
        }
        return result;
    }

   static  std::vector<float> _merge_ideology_levels(const std::vector<float>& first, const std::vector<float>& second)
    {
        if(first.size() != second.size())
        {
            spdlog::error("The ideology levels must be same! This is an critical error, program is shutting down...");
            std::exit(EXIT_FAILURE);
        }
        std::vector<float> result;
        for(int i = 0; i < first.size(); ++i)
        {
            float new_level = (first.at(i) + second.at(i)) / 2;
            result.push_back(new_level);
        }
        return result;
    }

}

namespace Leader

{
    IdeologyCoordinate ideology_level_randomizer(std::mt19937_64 *generator,
                                                 const IdeologyCoordinate &center,
                                                 const float &border,
                                                 std::vector<IdeologyAxis> &ideology_axis_objects)
    {

        std::vector<float> center_levels = center.get_ideology_coordinate_levels();
        std::vector<float> new_levels = _ideology_level_randomizer(generator,center_levels,border);
        IdeologyCoordinate new_ideology_coordinate(new_levels, ideology_axis_objects);
        return new_ideology_coordinate;
    }


    IdeologyCoordinate merge_ideology_levels(const IdeologyCoordinate& first,
                                             const IdeologyCoordinate& second,
                                             std::vector<IdeologyAxis> &ideology_axis_objects)
    {

        std::vector <float> new_levels = _merge_ideology_levels(first.get_ideology_coordinate_levels(),
                                                                second.get_ideology_coordinate_levels());
        IdeologyCoordinate new_ideology_coordinate(new_levels, ideology_axis_objects);
        return new_ideology_coordinate;
    }


    float ideology_distance_calculator(const IdeologyCoordinate& first_coord, const IdeologyCoordinate& second_coord)
    {
        float result = 0;
        std::vector <float> first = first_coord.get_ideology_coordinate_levels();
        std::vector <float> second = second_coord.get_ideology_coordinate_levels();

        if(first.size() != second.size())
        {
            spdlog::error("The ideology levels must be same! This is an critical error, program is shutting down...");
            std::exit(EXIT_FAILURE);
        }
        for(int i = 0; i < first.size();++i)
        {
            float intermediate_result = std::abs(first.at(i)*first.at(i) - second.at(i)*second.at(i));
            result += intermediate_result;
        }
        return result;
    }
}