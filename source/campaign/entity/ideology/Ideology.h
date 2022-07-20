//
// Created by tacoe on 26.04.2022.
//

#ifndef LEADER_IDEOLOGY_H
#define LEADER_IDEOLOGY_H
#include "source/campaign/entity/base/Entity.h"
#include <filesystem>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

namespace Leader
{


    class Ideology : public Entity
    {
    private:
        std::string name;
        std::string color;
        std::string ideology_axis_stringId;
        // TODO: Add advantages and disadvantages using collection pattern
    public:
        Ideology() = default;
        Ideology(std::string _id, std::string _name, std::string _color, std::string  _axis);
        [[nodiscard]] std::string get_name() const {return this->name;}
        [[nodiscard]] std::string get_color() const {return this->color;}
        [[nodiscard]] std::string get_ideology_axis_stringId() const {return this->ideology_axis_stringId;}

    };

    static std::unordered_map<std::string, Ideology> load_ideology_objects(const std::string &file_path);

    const Ideology NEUTRAL_IDEOLOGY("ideology_neutral","neutral","TODO","TODO");

    struct IdeologyAxis
    {
        std::string stringId;
        std::string axis_name;
        unsigned short axis_index;
        Ideology left_ideology;
        Ideology right_ideology;
    };




    std::vector<IdeologyAxis> load_ideology_axis_objects(const std::string &axis_file_path, const std::string &ideology_file_path);

}

#endif //LEADER_IDEOLOGY_H
