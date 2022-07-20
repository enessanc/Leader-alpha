//
// Created by tacoe on 1.05.2022.
//

#ifndef LEADER_IDEOLOGYCOORDINATE_H
#define LEADER_IDEOLOGYCOORDINATE_H
#include "source/campaign/entity/ideology/Ideology.h"



namespace Leader
{

    class IdeologyPoint
    {
    private:
        IdeologyAxis* axis{};
        float ideology_level{};
        Ideology current_ideology;
    public:
        IdeologyPoint() = default;
        IdeologyPoint(IdeologyAxis* _axis, const float& _level);
        void set_level(const float& _level);

        IdeologyAxis* get_ideology_axis() {return axis;}
        [[nodiscard]] float get_ideology_level() const {return ideology_level;}
        Ideology& get_current_ideology() {return current_ideology;}
    };

    class IdeologyCoordinate
    {
    private:
        std::vector <IdeologyPoint> ideology_coordinate;
    public:
        IdeologyCoordinate() = default;
        IdeologyCoordinate(const std::vector <float>& levels, std::vector<IdeologyAxis> &ideology_axis_objects);
        void add_ideology_point(IdeologyAxis* _axis, const float& _level = 0.0);
        void set_ideology_points_externally(const std::vector <float>& _levels);
        void set_ideology_level(const unsigned short& _axis_index, const float& _level);
        std::vector<IdeologyPoint>& get_ideology_coordinate() {return ideology_coordinate;}
        [[nodiscard]] std::vector<float> get_ideology_coordinate_levels() const;

    };

}

#endif //LEADER_IDEOLOGYCOORDINATE_H
