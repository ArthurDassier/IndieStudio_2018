/*
** EPITECH PROJECT, 2019
** participant.hpp
** File description:
** participant interface
*/

#pragma once

#include <string>

#include "../../../game/include/Lib.hpp"

// struct position {
//     float x = 0;
//     float y = 0;
//     float z = 0;
// };

// using t_id = std::size_t;

// struct player
// {
//     int skin;
// };

// class Participant
// {
//     public:
//         ~Participant() {}
//         virtual void deliver(const std::string message) = 0;
//         virtual t_id getId() = 0;
//         virtual player &get_playerdata() = 0;

//         void setPosition(const game::s_pos pos) { _pos = pos; }
//         game::s_pos &getPosition() noexcept { return _pos; }

//         void setSkin(const int skin) { _skin = skin; }
//         int getSkin() noexcept { return _skin; }

//         void setDirection(const std::string direction) { _direction = direction; }
//         std::string getDirection() noexcept { return _direction; }

//     private:
//         game::s_pos _pos;
//         int _skin;
//         std::string _direction;
// };