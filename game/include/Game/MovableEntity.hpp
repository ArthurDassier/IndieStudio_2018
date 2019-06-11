/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** MovableEntity.hpp
*/

#pragma once

#include "Game/Entity.hpp"

namespace game
{
    class MovableEntity : public Entity
    {
        public:
            MovableEntity(const EntityType &type): Entity(type) {}
            ~MovableEntity() = default;

            virtual void deliver(std::string message) = 0;
            virtual player &get_playerdata() = 0;
            virtual t_id getId() = 0;
    };
}; // namespace game