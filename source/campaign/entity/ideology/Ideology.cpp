//
// Created by tacoe on 26.04.2022.
//

#include "Ideology.h"
#include <utility>
#include <fstream>
#include "source/tools/JsonTools.h"

namespace Leader
{

    Ideology::Ideology(std::string _id, std::string _name, std::string _color, std::string  _axis) :
            Entity(std::move(_id)), name(std::move(_name)), color(std::move(_color)),
            ideology_axis_stringId(std::move(_axis)) {}

    static std::unordered_map<std::string, Ideology> load_ideology_objects(const std::string &file_path)
    {
        std::unordered_map<std::string, Ideology> ideology_objects_map;
        json data = load_json_file(file_path);
        for(const auto& ideology_data:data)
        {
            Ideology new_ideology(ideology_data.at("stringId"),
                                  ideology_data.at("name"),
                                  ideology_data.at("color"),
                                  ideology_data.at("ideology_axis_stringId"));
            ideology_objects_map[new_ideology.get_stringId()] = new_ideology;
        }

        return ideology_objects_map;
    }

    std::vector<IdeologyAxis> load_ideology_axis_objects(const std::string &axis_file_path, const std::string &ideology_file_path)
    {
        std::vector<IdeologyAxis> ideology_axis_objects;
        std::unordered_map<std::string, Ideology> ideology_objects_map = load_ideology_objects(ideology_file_path);

        json data = load_json_file(axis_file_path);

        for(const auto& ideology_axis_data:data)
        {
            IdeologyAxis new_ideology_axis {ideology_axis_data.at("stringId"),
                                            ideology_axis_data.at("axis_name"),
                                            ideology_axis_data.at("axis_index"),
                                            ideology_objects_map.at(ideology_axis_data.at("left_ideology_stringId")),
                                            ideology_objects_map.at(ideology_axis_data.at("right_ideology_stringId"))
                                            };

            ideology_axis_objects.push_back(new_ideology_axis);

        }

        return ideology_axis_objects;
    }
}