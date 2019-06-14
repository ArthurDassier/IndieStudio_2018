/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Explosion.hpp
*/

#pragma once

#include <chrono>

#include "Game/Entity.hpp"

namespace game
{
    class Explosion : public Entity
    {
        public:
            // Explosion() = default;
            Explosion(const EntityType &, float x, float y);
            ~Explosion() = default;

            // Members
            // Explosion & operator = (Explosion const &);
            bool getAlive();
            size_t checkTime();
            void refresh();
            float getPosX() const noexcept;
            float getPosZ() const noexcept;

        protected:
            float _posX;
            float _posY;
            bool _alive;
            std::chrono::time_point<std::chrono::high_resolution_clock> _cooldownExplose;

    };
}; // namespace game
