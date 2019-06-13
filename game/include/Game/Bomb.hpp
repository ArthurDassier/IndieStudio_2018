/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bomb.hpp
*/

#pragma once

#include "Game/Entity.hpp"
#include <chrono>

namespace game
{
    class Bomb : public Entity
    {
        public:
            Bomb() = default;
            Bomb(float x, float y, size_t _power);
            ~Bomb() = default;
            
            Bomb & operator = (Bomb const &);
            
            bool getAlive();
            size_t checkTimeExplosion();
            void destroyMap();
            void RefreshBomb();
            float getPosX() const noexcept;
            float getPosZ() const noexcept;

        private:
            size_t _power = 2;
            float _posX = 0;
            float _posY = 0;
            bool _alive = true;
            std::chrono::time_point<std::chrono::high_resolution_clock> _cooldownExplose;

    };
}; // namespace game
