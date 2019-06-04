/*
** EPITECH PROJECT, 2019
** participant.hpp
** File description:
** participant interface
*/

#pragma once

#include <string>

struct position {
    float x = 0;
    float y = 0;
    float z = 0;
};


struct player
{
    std::string sens;
    std::string name;

    position pos;

    player(std::string name) :
        name(name)
    {
    }
};

class Participant
{
public: 
    virtual ~Participant() {}
    virtual void deliver(std::string message) = 0;
    virtual std::string get_id() = 0;
    virtual player &get_playerdata() = 0;
};
