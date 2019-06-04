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

#include "participant.hpp"

class Room
{
public:
    void join(boost::shared_ptr<Participant>);
    void updatePosition(const std::string, std::string);
    void startPosi(boost::shared_ptr<Participant>);

private:
    void update_participants();
    std::vector<boost::shared_ptr<Participant>> _participants;
};
