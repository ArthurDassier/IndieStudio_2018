/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bomb.hpp
*/

#pragma once

#include "Entity.hpp"

namespace game
{
    class Bomb : public Entity
    {
        public:
            Bomb();
            Bomb(const s_pos &);
    };
}; // namespace game