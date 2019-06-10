/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Entity.hpp
*/

#pragma once

#include <iostream>
#include "Game/IEntity.hpp"

using t_id = std::size_t;

namespace game
{
    class Entity : public IEntity
    {
        public:
            Entity(const EntityType &);

            void setPosition(const s_pos &);
            s_pos getPosition() const noexcept;

            EntityType getType() const noexcept;

            virtual void deliver(std::string message) = 0;
            virtual player &get_playerdata() = 0;
            virtual t_id getId() = 0;

            const t_id id;

        private:
            s_pos _pos;
            EntityType _type;

            t_id generateID() const noexcept;
    };
}; // namespace game
