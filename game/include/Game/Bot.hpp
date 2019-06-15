/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bot.hpp
*/

#pragma once

#include <chrono>

#include "Game/Character.hpp"

namespace game
{
    class Bot : public Character
    {
        public:
            Bot();
            ~Bot() = default;
         private:
            t_id _id;
    };
}; // namespace game
