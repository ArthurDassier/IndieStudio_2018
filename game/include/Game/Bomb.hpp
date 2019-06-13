/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bomb.hpp
*/

#pragma once

#include <chrono>

#include "Game/Explosion.hpp"

namespace game
{
    class Bomb : public Explosion
    {
        public:
            Bomb() = default;
            Bomb(float x, float y, size_t _power);
            ~Bomb() = default;
            Bomb & operator = (Bomb const &);
            size_t getPower() const noexcept;
        private:
            size_t _power = 2;
    };
}; // namespace game
