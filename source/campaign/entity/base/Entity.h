//
// Created by tacoe on 26.04.2022.
//

#ifndef LEADER_ENTITY_H
#define LEADER_ENTITY_H
#include <string>
#include <utility>
namespace Leader
{
    class Entity
    {
    /*
     This class is base class for all the entities in game. Anything related to campaign is
     can be considered Entity.
    */
    protected:
        std::string stringId;
    public:
        explicit Entity(std::string _id) : stringId(std::move(_id)) {}
        Entity() = default;
        void set_stringId(const std::string& _id) {this->stringId = _id;}
        std::string get_stringId() {return this->stringId;}
    };
};


#endif //LEADER_ENTITY_H
