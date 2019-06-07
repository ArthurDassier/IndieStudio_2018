/*
** EPITECH PROJECT, 2019
** room.hpp
** File description:
** header for room
*/

#pragma once

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../../../game/include/Character.hpp"

class Room
{
public:
    void join(boost::shared_ptr<game::Character>);
    void updateJson(boost::property_tree::ptree &, boost::shared_ptr<game::Character>);
    void updatePosition(const t_id, std::string);
    void startPosi(boost::shared_ptr<game::Character>);
    int nbParticipants();

private:
    void update_participants();
    std::vector<boost::shared_ptr<game::Character>> _participants;
};
