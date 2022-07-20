//
// Created by tacoe on 1.05.2022.
//

#include "IdeologyCoordinate.h"


namespace Leader
{
    IdeologyPoint::IdeologyPoint(Leader::IdeologyAxis *_axis, const float &_level)
    {
        axis = _axis;
        set_level(_level);
    }

    void IdeologyPoint::set_level(const float &_level)
    {
        ideology_level = _level;
        if(ideology_level < 0)
        {
            current_ideology = axis->left_ideology;
        }
        else if(ideology_level == 0)
        {
            current_ideology = NEUTRAL_IDEOLOGY;
        } else
        {
            current_ideology = axis->right_ideology;
        }
    }

    IdeologyCoordinate::IdeologyCoordinate(const std::vector<float> &levels, std::vector<IdeologyAxis> &ideology_axis_objects)
    {
        for (auto& ideology_axis:ideology_axis_objects)
        {
            for(int index = 0; index < levels.size(); ++index)
            {
                if(index == ideology_axis.axis_index)
                {
                    this->add_ideology_point(&ideology_axis,levels.at(index));
                }
            }
        }
    }

    void IdeologyCoordinate::add_ideology_point(IdeologyAxis *_axis, const float &_level)
    {
        IdeologyPoint new_ideology_point(_axis,_level);
        ideology_coordinate.push_back(new_ideology_point);
    }

    void IdeologyCoordinate::set_ideology_points_externally(const std::vector<float> &_levels)
    {
        for (int index = 0;index < _levels.size(); ++index)
        {
            // TODO: Question that initially these vectors are fulfilled?
            ideology_coordinate.at(index).set_level(_levels.at(index));
        }
    }

    void IdeologyCoordinate::set_ideology_level(const unsigned short &_axis_index, const float &_level)
    {
        ideology_coordinate.at(_axis_index).set_level(_level);
    }

    std::vector<float> IdeologyCoordinate::get_ideology_coordinate_levels() const
    {
        std::vector<float> levels;
        for(auto& ideology_point: ideology_coordinate)
        {
            levels.push_back(ideology_point.get_ideology_level());
        }
        return levels;
    }
}