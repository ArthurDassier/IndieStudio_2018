/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Fire.hpp
*/

#pragma once

#include <chrono>

#include "Game/Explosion.hpp"

namespace game
{
    class Fire : public Explosion
    {
    public :
        // Fire() = default;
        Fire(float x, float y);
        ~Fire() = default;

        Fire operator = (Fire const &);
    };
}; // namespace game
